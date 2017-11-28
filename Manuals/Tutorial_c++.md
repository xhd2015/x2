# 此文件
c++常用功能代码片段

# 读取一行
```c++
string line;
while(getline(cin,line))
{
        cout <<line << endl;
}
```
说明：输入一个换行时，就完成一次读取，但是换行不存在line中。敲击回车时，得到空字符串。

# 读写文件
```c++
    fstream in("a.s",fstream::out|fstream::in);
    string line;
    while(getline(in,line))
        cout << line << endl;
    in.close();
```
in和out两种模式同时使用，表示读写,加上binary表示读写二进制，不对特殊字符进行多余处理。
# 定义初始化列表的函数
```c++
#include <initializer_list>

class Foo{
    public:
        Foo(std::initializer_list<int> il);
};
```

# 正则表达式

```c++
#include <regex> //提供regex_search(比regex_match通用)搜索string中出现的第一个正则模式,sregex_iterator用于搜索出现的每一个
//除了sregex_iterator,还有cregex_XXX，表示对C字符串操作

int main()
{
    {
    //使用regex_search
    regex re("(.*)d");
    smatch sm;
    if(regex_search(string("whatd"),sm,re))
    {
        cout << sm << endl;
        cout << sm.str(1)<<endl;//取出第一个捕获组,str(),str(0)表示整个匹配
    }
    }
    {
    // 使用sregex_iterator迭代
    string s("wddwdwdddwd");
    regex re("wd{1,2}",regex::icase);
    for(sregex_iterator it(s.begin(), s.end(), re), itend;it!=itendl++it)
    {
        cout << it->str() << endl;
        // it的内容： [prefix][it][suffix]=整个字符,it表示正在匹配的部分
    }


    }

    { //replace,format
        cout << regex_replace("55.66",regex("(\\d{2})\\.(\\d{2})"),"$2.$1") << endl;
        // $表示组引用，regex_replace替换所有的出现。

    }

}

```
# 时间处理和格式化输出


# 处理命令行选项参数

# 随机数
<random>库，区分engine和distribution两种类型
```c++
    #include <random>
    #include <ctime>
    using namespace std;
    int main()
    {
        default_random_engine e(time(0));
        normal_distribution<> n(4,1.5);//均值为4，标准差为5
        vector<unsigned> vals(9);
        for(size_t i=0;i!=200;++i)
        {
            unsigned v=lround(n(e));//舍入到最接近的整数
            if(v < vals.size())
                ++valss[v];//统计
        }
        for(size_t j=0;j!=vals.size();++j)
        cout << j << ":"<<string(vals[j],'*')<<endl;//打印出正态分布。

    }
```


# 字符串处理：搜索，分割，匹配

# 异常处理
```c++
    

```