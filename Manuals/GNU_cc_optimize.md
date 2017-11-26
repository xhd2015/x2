# 此文件
此文件主要对g++编译器的优化作讨论
# g++ -O优化做了什么
-O0  关闭掉任何优化
g++的表现有时候也许不尽人意。比如mbr扇区代码应当在512字节内，但是如果代码超出范围,-O0会报错，但是-O1会将这些代码放置到其他地方以避免错误。
从其他角度来看，这是很正常的，但却不透明。

对MBR启动代码而言，为了使-O1 -O2 -O3优化对代码区不重新安排，将所有定义的数据放到函数内部，如下面的片段：
``` c++
  extern "C" __attribute__((section("textmbr"))) void readLaterSectors()
  {
     /*..
     ..
     ..*/
      __asm__( //在这里定义数据
      "// .section textmbr,\"x\" \n\t"
      ".org CONFIG_MBR_PARTITION_START \n\t" // 保证代码不会覆盖分区表,463?//注意：如果这里报错，就是前面代码区尺寸太大，需要优化
      "_mbrtable: \n\t" //定义扇区位置
      ".org 512 - 2 \n\t"
      ".byte 0x55\n\t"
      ".byte 0xaa\n\t"
      ".org CONFIG_REAL_INIT_STACK_SIZE \n\t"
  );
  }
```
-O1 是折中的选项
-O2 可能产生错误

# 涉及const的-O2优化可靠吗？
答案是：可靠
首先说明什么是涉及const的优化。C++中如果声明一个类的成员为const类型，那么就可以在类中直接定义该const域的值，如下
```c++

class HasConst{
    public:
        const int a=4;
        int b;
};
```
如果有一个函数专门检测该const域是否就是指定值：
```c++
bool checkHasConst(HasConst *p)
{
    return p->a==4;
}
```
显然，如果p是从类HasConst构造的，那么此函数永远返回真。所以，如果g++使用这种假设，它就可能把对这个函数的调用变成恒真表达式
但是如果我们特意构造一个该域不一定是给定值的结构：
```c++

int main()
{
    //space用于分配空间，并特意构造一个随机值的结构，可能是4，也可能是9,
    char space[sizeof(HasConst)]={time(NULL)%2==0?4:9};
    //该结构的值可能是4，也可能是9
    HasConst *p=(HasConst*)space;


    cout << "check:"<<checkHasConst(p)<<endl;

    return 0;
}
```
如上面的代码，该代码如果编译正确，则一定能够随机打印出check:0 和 check:1两种结果，否则优化就是错误的。

结果：使用-O2优化，依然生成了checkHasConst的函数并且在该种情况下调用了该函数。这就意味着g++的优化对const是可信的。
g++不对const域作假定。

源文件：const_optimize.cpp可在Others文件夹下找到