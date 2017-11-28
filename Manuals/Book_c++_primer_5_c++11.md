# 此文件
此文件是对书籍C++ primer(第五版，C++11)的介绍以及相关的笔记。

# C++11新标准参考页
XXIII~XXV页

# 基础部分（29页~178页）
变量，const，迭代器，using，表达式，类型转换，迭代语句，try语句块

# 中级部分（181~397）
函数，分离式编译，类，友元，拷贝、赋值和析构函数，初始化列表，委托构造函数，字面量常量类
标准库：IO库，顺序容器，泛型算法，lambda表达式，关联容器

# 高级部分 I（399~630)
动态内存
类设计的精细化，右值引用
重载和类型转换，虚函数

模板与泛型编程，模板实参推断，std::move

# 高级部分 II (633~864)
标准库特殊设施 tuple, bitset, 正则表达式，随机数，流
异常处理，命名空间，多重继承，虚继承
特殊工具与技术：重载new，delete，定位new表达式，dynamic_cast运算符，typeid运算符,type_info类，枚举类型，union类
不可移植特性：位域，volatile，extern "C"

余下部分是附录：标准库名字和头文件，算法概览，随机数
C++11的新特性：long long类型，nullptr常量，constexpr常量,auto,decltype,initializer_list类,=default,=delete,string的数值转换函数,explicit，虚函数,final阻止继承,noexcept,allocator::construct,static_cast,forward函数, sizeof...,可变参数模板



##############################
### 笔记部分##################
####基础部分：
    endl是一个特殊的操作符。程序员调试时，总是应当进行刷新，否则可能输出的信息不能对应到实际的问题。

    cerr关联到标准错误，写入到该对象的输出不缓冲。

    c++类型：空类型，算术类型:{bool(未定义),char(8位),wchar_t(16位),char16_t(16位),char32_t(16位),short(16位),int(16位),long(32位),long long(64位),float(至少包含6位有效数字),double(至少10位有效数字),long double(至少10位)}
    注：类型括号中的位数是指最小长度,通常long double是12或16字节实现
    c++除了bool和扩展的字符类型外，其他整型都可划分为signed和unsigned, 默认为signed，除了字符型，它被分成了三种：char,signed char,unsigned char，char的具体类型由编译器指定。
    建议：在算术表达式中，包括数值比较，不要使用bool和char，char在一些机器上是有符号的，在另一些机器上又是无符号的。如果需要实现不大的整数，明确使用[un]signed char.
    建议：float和double的代价差不多，因此如果要进行浮点运算，double是首选。

    数值转换：类型所能表示的值决定了转换的过程。bool型转换时，0:false 其他:true 
    浮点数->整数：保留整数部分
    超范围数->无符号:取模
    超范围数->有符号：结果未定义（不可移植）
    负数-->无符号类型：等于这个负数+无符号数的模，也就是0xffffffff-|负数|， 如果表达式出出现无符号数，则所有的有符号数都会转成无符号数,比如 -1*1u
    无符号数相减：两个无符号数相减，如果在数学上来说应该是负数的，则会将这个负数转换成无符号类型。所以一定要保证两个无符号数之差不为负数。下面的循环是一个死循环：
    for(unsigned u=10;u>=0;--u)cout<<u<<endl;

    字面量，默认情况下，十进制字面量是带符号数，类型是int,long,long long中最小的那个。
    十六进制字面量的类型是能容纳其数值的int,u_int,long,u_long,long long,u_ long long中的最小的一个，如果超出范围，报错。
    short没有字面量。
    例子：
    cout << sizeof(0xffffffff) <<endl; // 4
    cout << sizeof(0xfffffffff) << endl; //8
    十六进制字面量的类型首先是signed，然后才是unsigned。 当我们在计算字面量的绝对值时，总是以无符号数来计算，也就是说假设我们拥有无限的位数来计算我们所写下的字面量，然后将这个计算得来的值和某个类型的范围比较，就可以发现是否超过。
    cout << (signed)0xffffffff << endl; //-1
    很明显，0x80和char类型的比较就能得到阐明：以无限位数来计算0x80，是128,而[signed]char类型的范围是-128~127
    注意，负号不能算作字面量的一部分。所有的字面量都是无符号正数或0。负号只是一个取反操作。
    09字面量错误，9不在八进制的数字范围内
    浮点型默认值是double类型
    转义自变量：（由编译器完成）\xXX 表示一个字符
    前缀: L'a' 宽字符  u8"hi"utf8存储的字面值   u'a' Unicode 16类型  U'a'  Unicode32类
    后缀:u或U  无符号
        l或L   long
        ll或LL long long
        f或F   float
        l或L   double
        1e-3f float类型  2.1L用long  double
    nullptr是指针字面值，false,true是bool类型字面值
    3.14e1L 是long double类型,应当这样看：(3.14e1)L

    初始化变量，int a=0,int a={0},int a(0),int a{0}
    如果使用{}来列表初始化，则编译器对可能产生的信息丢失报错。内置类型变量的初始值如果没有指定，在函数外是0，函数内部随机值。

    separate compilation，分离式编译。将程序分割成若干个文件，每个文件被独立编译。支持该方式的机制是，函数的声明和定义区分。声明使得名字为程序所知，定义关联名字和其实体。
    如果仅仅想声明一个变量而不是定义，使用extern,如果该extern赋值，则被认为是初始化。

    c++关键字：alignas alignof asm constexpr const_cast dynamic_cast explicit export friend mutable noexcept nullptr reinterpret_cast static_assert static_cast thread_local typeid typename volatile
    c++操作符替代名：and and_eq bitand compl not_eq or_eq xor_eq xor or not bitor
    _是一个有效的标识符。标准库保留名称：YY__XXX, _UXXX, 也就是用户最好不要定义两个下划线的标识符，会儿以下划线，大写字母开头的标识符。

    作用域规则：内层的作用域覆盖外层的同名变量，除非通过::明确指定作用域。

    两种复合类型：引用就是别名，只是给一个内存位置起了一个别名。指针本身是一个对象，其值指向对象的内存。
    对空指针的定义有三种： p1=nullptr,p1=0,p1=NULL(值就是0，cstdlib中定义)
    现代c++程序应当使用nullptr，避免使用NULL
    void *指针用于存放任意对象的地址。不能用于访问。

    const限定符，const对象不能改变其修饰为const的内容，必须指定const的初始值。如果const对象的初值可以在编译期知道，则每个引用该对象的值都换成引用值。
    注意，extern声明对const对象必须使用extern const.
    注意：实际上你也可以用extern不用extern const，但是如果你对该变量使用了写操作，由于这个变量被放在只读区域，所以会导致写错误。const和非const生成的编译器符号是相同的。
    引用本身就是const类型的，const int & const r1=c;而且int const &r1=c和const int &r1=c是相同的。
    XXX const YY，修饰的是XXX不可变，因此int & const r1=c是错误的，这就意味int &不可变，但是本身r1就是不可变的。
    const XXX YY 修饰的XXX，最近的一部分。
    const int &r1=2;// 可以是立即数

    double dval=3.14;
    const int &ri=dval;这种引用也能成功，但是只是因为编译器创建了一个临时变量temp，将dval转到temp中，然后ri来保存这个临时变量。
    但是int &ri=dval是错误的，编译器不允许修改临时变量。
    把const放到指针的*后面，一位指针不变，放到*之前，意味着指针指向的对象不变。用“顶层const”来表示指针本身是常量，“底层const”表示指针所指对象是常量，更一般地，称变量本身不变的叫顶层const，变量所指变得叫底层const 

    c++11新标准，允许变量声明为constexpr类型，以便由编译器验证该值是否是一个常量表达式。如果你认为一个变量是常量表达式，将其声明成constexpr类型。
    constexpr int mf = 30;
    constexpr int sz = size();//size本身也是constexpr的
    constexpr对指针只是对指针本身的限制，而不是指针的内容。

    auto如果定义多个变量，这些变量必须具有相同的类型。auto sz = 0, pi =3.14;//错误
    如果r是引用，auto a = r；a不是引用，a是r所指的类型。记住，引用只是别名。auto不会创造任何引用类型。auto忽略顶层const，保留底层const。 const int ci=i;则auto d = &i；d是一个普通整型指针，auto e = &ci；e是一个常量指针。
    auto只是用于推断类型，所以可以加上const,&等修饰：const auto &j=42;
    当然，auto还有很智能的一面：
    auto p1=&i;
    auto *p2=&i;
    p1和p2的值是相同的。注意，对于推断，总可以将auto换成某个基本类型来验证，*,&不能够加在auto里面。如
    auto k =ci,&l=i;  auto替换成int。

    decltype是一个类型推断占位符。decltype和auto不一样，会保留const和引用。另外，如果decltype加上了括号（双层括号），就一定是引用类型。
    decltype((var))--- int &
    decltype((var))--- 只有当var为引用时才是引用。

    头文件不应当包含using声明。
    直接初始化(参数)和拷贝初始化(=)

    string::size_type类型体现了与机器无关的特性，其他多数标准库也定义了这些类型。
    string对象的比较可以用 <,==,!=,<=,>,>=来比较，依照字典序。
    string对象可以相加，+=则是append的意思。
    cctype头文件用于处理一般字符。
    处理string中的每个字符串，使用
    for(dec:exp)stat,string是可以迭代的对象。
    将每个字符转换为大写字符：
    for(auto &c:s)c=toupper(c);
    s可用下标s[0]

    迭代器运算符： *it,it->mem,++iter,--iter,iter1==iter2,iter1!=iter2
    迭代器的for循环应当使用'!='来作为条件判断。
    迭代器失效：任何可能改变vector对象容量的操作，如push_back都会使现存的迭代器失效。

    对于容器类型的迭代，必须注意，是否在迭代过程中改变了容器的容量。现在必须指出：for循环不能用于项vector添加元素。

    c++的设计基本上都是为了让使用复杂类型像使用基本类型那样简单。

    数组初始化可以使用constexpr。数组复杂的声明：
    int *ptrs[10]; //10个指针
    int (*parray)[10];//parray指向一个含有10个元素的数组。
    int (&arrref)[10];//引用
    可以这样理解：*parry是一个int[10]，所以parry自然是一个指向数组的指针。
    使用标准库begin，end来迭代数组，
    int *beg=begin(arr),*pend=end(arr);
    ...

    在c++程序中尽量避免使用C风格字符串。

    左值和右值，左值可以赋值，右值不可以。
    取地址需要一个左值对象,返回一个右值；迭代器的前置递增递减得到左值对象。
    decltype(左值)得到的是引用，比如decltype(*p)对应的类型是int&;decltype(&p)得到int **.

    非布尔值的测试：if(val),if(!val)
    if(val==true) 错误，仅当val=1时为真。所有类型应当有明确的转换。

    位运算用于有符号数，符号位是未定义的；因此建议仅仅将位运算符用于
    !不是位运算符，请不要使用。~是取反操作符。

    sizeof char 永远返回1
    sizeof  引用 计算被引用对象的大小

    隐式转换：当几种不同的类型在一起运算时，c++不是直接将它们相加，而是转换到某一类型，再执行操作。隐式转换不需要程序员介入。
    隐式转换的设计是尽可能避免精度损失。所有 2.3+3将会转换3为double型。
    隐式转换发生的时机：大多数表达式中，比int小的类型首先转换成int；条件表达式中，非布尔值转换成布尔值
    自动转换还有下面的情况：数组自动转换成指针：int arr[10];int *p=arr;
    nullptr,0可以转换成任意指针类型；任意非常量指针可以转换成void*；

    强制转换：命名的强制转换如下：
    cast-name<type>(expr), 如果type是引用类型，得到左值。
    cast-name有 static_cast,dynamic_cast,const_cast,reinterpret_cast
    static_cast用于所有能够接受的类型转换，使用此语句可以让编译器不再发出警告。
    void *p;double *pd=static_cast<double*>(p).  static_cast的地址值与原地址相同。
    const_cast只能改变底层const: const char *pc;char *p=const_cast<char*>(pc); 也就是去掉const修饰。static_cast不能作用与此。
    reinterpret_cast依赖于机器上的实现，
    建议：尽量避免使用static_cast,dynamic_cast,reinterpret_cast,在有重载的情况下使用const_cast.

    旧式强制转换：  type(expr), (type)expr.自动与命名转换匹配。

    在存在关联的类型之间进行转换时，指针会加减相应的偏移。
    【命名转换这一部分并不是很清楚】

    switch语句的作用域是交叉的，但是如果初始化仅在一个域中，另一个域中就可能没有该变量的初始化。使用case时，最后使用{}包围，以便安全使用局部变量。
    case true:{
        int fval=0;
        break;
    }case false:{
        int fval=2;
        break;
    }

    c++提供了一种新的for范围循环:
    for(decl;container)state
    名称叫做范围循环。在范围循环中不能改变vector的容量。

    try语句块和异常处理
    异常机制：throw表达式，try catch,异常类
    catch的形式是正常的变量定义语句：
    ..catch(runtime_error err)...
    异常抛出查找catch的过程：逐层查找，本函数没有，则回到调用函数；一直到顶部开始的函数，如果都没有，则转到terminate标准库函数，该函数行为与系统有关。
    标准异常： exception头文件通用异常exception,只报告异常发生，不提供额外信息
    stdexcept提供了几种常用的异常类:exception,runtime_error,range_error,overflow_error,logic_error,out_of_range,length_error,invalid_argument
    new提供了bad_alloc异常
    type_info提供了bad_cast

#### 中级部分
    尽量使用const作为参数传递
    传递数组作为参数时，以下三种形式是等价的：
    void print(const int *);
    void print(const int []);
    void print(const int [10]);
    使用标准库begin，end规范传递数组
    void print(const int *beg,const int *end);
    传递二维数组时，必须指明每一维的长度：
    int matrix[][10]

    initializer_list<T>类型默认存储的都是const类型，方法：size(),begin(),end()
    void error_msg(initializer_list<string> li)...

    可以返回临时对象的拷贝，但是不要反悔指针或者引用。可以返回初始化列表
    std::vector<int> getData()
    {
        return {1,2,3};
    }

    main函数的隐式规则：这是仅仅针对main的，如果main没有return语句结束，则隐式地插入一个返回0的return语句。
    main函数不能重载
    this形参的const形式不同，可以重载函数。

    constexpr函数用于返回常量表达式，限制：函数的返回类型和所有形参的类型都是字面量类型，函数体有且仅有一条return语句，可以包含其他语句，但不执行操作（空语句，using，以及typedef）：
    constexpr int new_sz(size_t cnt) {return cnt*42;}
    constexpr函数默认内联。调用：
    new_sz(43);//正确
    new_sz(i);//错误，不能有变量

    assert是预处理宏，在cassert头文件中。
    assert依赖于NDEBUG变量是否定义，如果定义，则assert什么也不做。

    编译器预定义变量：__func__ __FILE__ __LINE__ __TIME__ __DATE__
    使用宏可以帮助我们正确地打印这些信息。 

    当有两个仅仅是const修饰不同的函数候选调用时，总是优先选择精确匹配的，也就是说非const调用非const，const调用const；如果没有，则类型转换。

    函数指针：把函数名作为字面量传递时，自动转成函数指针。使用decltype必须加上指针
    decltype(main) *pmain=main;
    auto pmain2=main;

    合成默认构造函数：如果我们没有定义任何一个构造函数，则编译器会自动生成一个：如果类中定义了初始值，则使用初始值；否则，默认初始化（基本类型是随机值）
    注意，如果要对类中的复杂结构使用初始值，使用语法： Foo foo=Foo(...);
    初始化时保证调用的是Foo(...)而不调用operator=；但是在定义之外，则需要调用operator=。这个默认值可以被覆盖，如果在类的初始化列表中(也就是:之后,{之前)调用了其他该类的初始化函数，则默认值不被使用。
    因此不必担心性能开销，没有多余的性能开销。
    可以使用=，也可以使用{}：
    Foo foo=Foo(...);
    Foo foo{...};

    =default可以用在声明处，也可以用在定义处。用在定义处将不能被内联。

    编译器默认生成拷贝，赋值和销毁函数。

    友元可以允许其他类或者函数访问该类的非公有成员。在class中的任何部分添加：friend XXX func(XXX..);来声明友元函数，参数必须匹配。友元仅仅是指明了特殊的访问权限。
    它的含义是：这些函数可以访问本类的所有私有成员，私有静态函数等
```c++
    class V{
        friend void foo();
        private:
            static void bar()
            {
                cout << __func__<<endl;
            }
    };

    void foo()
    {
        V::bar();//调用
    }
```
    类和类之间也可以有友元关系，通过friend class Foo即可。每个类负责控制自己的友元类或者友元函数。

    可变数据成员：即使在const中也能修改该数据。
    mutable声明。常见：统计某个函数的调用次数，做一些与函数状态无关的操作。

    注意，定义时调用=并非operator=,而是对应的初始化函数。
    也就是说:Foo foo=Foo(...);和
            foo=Foo(...)执行过程不一样。

    委托构造函数，我们已经知道。

    隐式的构造函数转换，编译器只允许一步类类型转换。比如
    Foo foo=99;
    有构造函数： Foo(int i){}
    除非声明为explicity,否则就会执行类型转换。
    如果调用static_cast<Foo>(int)则强制从int转换到Foo。这相当于我们为编译器增加了一条强制转换规则。

    聚合类：能够使用{}直接初始化的，要求：原始c struct。

    constexpr构造函数将得到一个constexpr意义上的复合类型。
    想象以下一些类只有几个特殊的取值，那就可以将其函数定义成constexpr的。
    class Foo{
        public:
            constexpr Foo()=default;
    };
    int main()
    {
        constexpr Foo foo;
        /*...*/
    }

    标准库
    iostream还提供了istream,wistream,ostream,wostream,iostream,wiostream等类
    fstream提供了面向对象的文件IO，同样有w前缀的版本，sstream则是面向字符串的库
    对应于宽字符版本的还有wcin,wcout等

    io流对象不支持拷贝和赋值函数。
    io对象的状态：eof() fail() bad() good() clear() rdstate()
    当IO流处于错误状态时，就不能正常使用。此时if(io_obj)... 可用于判断IO是否可算。使用iostate类型来记录状态
    badbit=1  不可恢复的错误
    failbit=1  可恢复的错误
    eofbit=1   已经结束
    goodbit=0   表示流未发生错误。上面三个任何一个被置位，io状态就属于失败。
    auto oldState=cin.rdstate();
    cin.clear();
    cin.setstate(oldState);

    缓冲。每个输出流都有一个缓冲区。std::flush操作符用于刷新缓冲区。std::ends插入空字符，然后刷新缓冲区。
    std::unitbuf是一个改变流状态的操作符，对应于std::nounitbuf,用于设置当前流的状态是否立即刷新。
    cout << unitbuf << "hello"<<nounitbuf;

    输入流和输出流关联：tie函数。将输出刷新在读取操作之前。系统关联cin和cout。
    cin.tie(&cout);
    ostream* old_tie=cin.tie(nullptr);//不再关联，取得当前的关联

    文件输入与输出：初始化方式
    f(s), f(s,mode),f f.open(s);
    f.close(),f.is_open()
    注意，当进入析构函数时，打开的文件会自动关闭。模式取值：in,out,app,ate,trunc,binary
    trunc必须和out联用，默认就是trunc。为了保留打开文件的内容，使用out,app模式或者out,in模式，保留文件原来的内容。
    binary表示二进制模式，ate表示立刻将指针定位到后面，但不限制指针的偏移范围。
    流是可以重用的对象，意味着在open,close之后还可以open。

    string流用于向内存字符串读写数据
    初始化有strm(s),strm.str(s).该对象同样可以重用。

    顺序容器:vector  deque  list(双向链表) forward_list(单向链表)  array(固定大小的数组) string

    容器共有的属性和操作
    类型：iterator, const_iterator  size_type difference_type  value_type(元素类型) reference(即value_type&) const_reference
    构造函数：C c;C c(cfrom);C c(begin,end)拷贝; C c{a,b,c,..}初始化列表。
    赋值和swap:a.swap(b),swap(a,b)
    大小：size() max_size() empty()
    添加/删除： insert(e) erase(e)删除；clear()清空
    迭代器：begin()/end() cbegin()/cend()
    反向容器（不支持forward_list):reverse_iterator,const_reverse_iterator, rbegin()/rend(), crbegin()/crend()

    seq.assign(b,e) 就是seq=<b,e>表示设置为b到e的值
    swap(c1,c2)交换c1,c2的元素

    array的使用：array<int,42>

    emplace,emplace_back,emplace_front的语义是使用给定的参数直接在容器中构造对象，而不是复制外来的对象。
    c.emplace_back("123",'g',24);

    访问元素：back() front()  c[n]n超限则未定义 c.at(n)n超限则抛出异常

    forward_list支持一系列push_[after,before]操作

    resize用于调整大小，如果减少，则元素被抛弃。

    list,forward_list的迭代器不会失效；但是使用数组实现的容器会实现。

    可以使用insert的返回值来确定改变之后的迭代器，原来的迭代器可能失效了。
    iter=vi.insert(iter,4);
    iter=vi.erase(iter);
    由此实现for循环中改变vector的大小
    不要保存end迭代器，因为改变元素后，vector的end变化。总是使用动态的end。

    vector和string用于管理内存的函数：
    shrink_to_fit()  将预留容量改到与size()相同
    capacity()   容量
    reserve(n)   分配至少n个空间，注意，resize,reserve都不会改变实际占用的空间。
    shrink_to_fit请求也可能不被响应，但是也可能减少实际占用的空间。

    string::npos初始化为-1，从结果上来看，就是最大的size_type值。
    操作：compare,find,rfind,find_first_of

    数值转换：std::to_string(int),std::stod(string),stoi(s,p,b),stol,stoul stoll stof stod stold


    容器适配器：在已有的容器上提供专门的功能
    包括：stack,queue,priority_queue
    适配器是使一种东西看起来更像另一种东西的机制。所有适配器的属性和操作：size_type value_type container_type(底层容器的类型)
    A a;空适配器  A a(c)；以c为容器的适配器

    适配器有两个参数：size_type container_type, stack,queue的第二个参数默认值是deque,priority_queue是vector
    stack<string,vector<string>> str_stk(vec);//将会拷贝vec
    所有适配器都要求底层容器支持添加，删除操作。


    泛型算法algorithm
    容器只定义了很少的操作，其他操作在泛型算法中提供。
    find操作需要元素定义==操作符，但是可以使用自定义的操作符。
    accumulate求和
    equal对比两个序列，看它们是否相等

    算法分类：只读算法，写容器的算法(fill)

    back_inserter是用于向容器中添加元素的迭代器：先创建一个对已有容器的引用，然后调用赋值操作
    vector<int> vec;
    auto it=back_inserter(vec);
    *it=5;//直接添加到尾部
    fill_n(back_inserter(vec),10,0);// 添加10个元素到位部。 实际上是将插入和定位分开。

    copy算法用于复制,sort用于排序,unique用于去重（unique的返回值指向经过移动后的垃圾区域，也就存放那些重复的元素，因此可以调用erase来删除它们）
    sort(w.begin(),w.end());
    auto end=unique(w.begin(),w.end());
    words.erase(end,words.end());

    sort默认使用<或者==来完成比较,sort接受第三个参数作为unary，即谓词函数/bool表达式函数
    sort(w.begin(),w.end(),isShorter);

    lambda表达式：[环境](参数)->返回值类型 {函数体}
    auto f=[]{return 3;}

    find_if

    for_each遍历算法：for_each(vec,begin,lambda) ；每个lambda被执行一遍。

    隐式捕获：[=]表示根据引用的变量自动值捕获
            [&]表示引用捕获
            [&,=pos]表示对pos使用值捕获。

    默认情况下，传递到lambda的值不可以变化，通过mutable来声明可变
    [v] () mutable{return ++v;};

    返回值：如果一个lambda包含除return外的其他语句，则推断返回为void。必须通过声明改写。即->int

    标准库bind函数（functional）
    auto newCall = bind(call,arg_list);arg_list包含_n的变量名，表示下一个参数绑定第n个，_n只是一个占位符
    auto check4=bind(check_size,_1,4);//绑定第一个参数

    placeholders名字：名字_n都位于placeholders的namespace中，即using std::placeholders::_1.
    auto g=bind(f,a,b,_2,c,_1);
    g(a1,a2);
    对g的调用变成f(a,b,a1,c,a2);

    更多迭代器：insert，stream,reverse,move
    插入迭代器，用于修改操作的插入位置选择。相当于说，findPos.负责定位。有三种：back_inserter,front_inserter,inserter随机位置
    对插入迭代器的赋值操作就是插入操作：*it=val

    istream_iterator,ostream_iterator
    istream_iterator<int> in_iter(cin),eof//默认初始化为eof;
    while(in_iter!=eof)
        vec.push_back(*in_iter++);//读取流中的下一个
    其他操作：*in,读取，in->mem,++in,in++下一个
    accumulate(in,eof,0)--计算流中的数据。

    算法的形参模式：
    alg(beg,end,other args);
    alg(beg,end,dest,other args);
    alg(beg,end,beg2,other args);
    alg(beg,end,beg2,end2,other args);

    算法的if版本：find(beg,end,val),find_if(beg,end,pred),pred是一个函数


    关联容器：map,set
    8种容器类型：multi_, unordered_,map or set,三者的组合。
    map,multimap定义在<map>中，set,multiset定义在<set>中,无序容器定义在<unordered_map>,>unordered_set>，无序版本使用hash实现。
    默认使用'<'来定义顺序，自定义函数如下：
    multiset<int,decltype(my_fun)*> intset(my_fun); 

    pair类型，在<utility>中


高级部分I
    每个程序运行时都有一个内存池，称作堆，用于动态分配对象。动态内存的管理通过new/delete完成

    智能指针<memory>：行为类似常规指针，但是能够自动释放所指向的对象。
    shared_ptr运行多个指针指向同一个对象
    unique_ptr独占所指向的对象
    weak_ptr引用，指向shared_ptr所管理的对象

    shared_ptr<string> p1;//初始为空
    if(p1)
        p1->empty();//调用string的empty

    共有操作：shared_ptr<T> sp;unique_ptr<T> up; p 条件判断；*p解引用,p->mem,p.get()获取原始指针;swap(p,q)交换p,q中存储的指针;p.swap(q)
    shared_ptr独有：make_shared<T>(args),shared_ptr<T>p(q);p=q减少p，增加q;p.unique()返回p.use_count==1;p.use_count() 返回p共享指针的智能智能指针数量，很慢，用于调试

    make_shared<int>() 会初始化一个随机值。
    make_shared<vector<string>>(); 一开始指向一个空的vector。 也就是说，make_shared实际上包括：new分配内存，返回指针。
    make_shared<T>(args..)和shared_ptr<T> p(new T(args...))作用相同
    注：内置指针不能隐式转换到智能指针
    不要通过get来初始化另一个智能指针，这样不会改变智能指针的状态
    其他操作：reset(T*) 
    发生异常时，shared_ptr析构函数自动调用。
    自定义析构操作：void my_delete(T *p){...}
    可以将这个自定义的函数传递给shared_ptr:shared_ptr<T> pt(&t,my_delete);这样将会自动调用my_delete替代delete &t的使用。这种情况下，shared_ptr可以指向局部变量。

    shared_ptr析构函数如果发现引用计数为0，就会销毁对象。
    使用动态内存（new）的三种情况：1.对象数目未知 2.对象的准确类型不能确定 3.跨代码块共享数据(原容器可能已经销毁，但是数据由其他容器持有)

    直接内存管理：new,delete
    classs类型的两种初始化形式结果相同，但内置类型的两种初始化形式有差别：
    new int;//默认初始化，初始值未定
    new int();//值初始化，初始值为0

    分配const对象：new const int(1);

    内存耗尽,new抛出bad_alloc异常；通过关键字nothrow来使其返回指针：
    new (nothrow) int;//如果分配失败，不抛出异常，只是返回指针
    new允许传递额外的参数来控制其行为。在文件<new>中
    delete必须指向空指针或者已经分配的内存，否则其行为就是未定义的。
    const对象语法同普通一致

    unique_ptr全权拥有它所指向的对象,某个时刻只能有一个unique_ptr指向给定的对象。unique_ptr不支持operator=(赋值)以及拷贝

    注：拷贝是指 p1(p), 赋值是指p1=p.

    老式的库有auto_ptr，具有unique_ptr的特性。但是应当避免使用auto_ptr

    weak_ptr不控制所指对象生存期，指向一个shared_ptr管理的对象，但不改变shared_ptr的引用计数 。也就是说,weak_ptr不改变原来的智能指针状态

    动态分配数组：
    new int[10];//10个未初始化
    new int[10]();//10个初始化为0
    new int[10]{0,1,23,...};//可以使用列表
    new string[10];
    new string[10]();//相同

    alloctor类 <memory>
    new的局限性：将内存分配和对象构造组合在了一起。alloctor用于将内存分配和对象构造分离开来。使用：
    allocator<string> alloc;
    auto const p=alloc.allocate(n);//分配n个string空间
    方法：allocate(n),deallocate(p,n)(释放n个类型位T的对象，但是不调用destroy，程序自己调用析构函数，p是指针),construct(p,args)构造对象，destroy(p)执行T的析构函数

    一个小型程序：查询文本中单词的出现次数。
    1.分析要求限制：每一行只出现一次

    拷贝控制
    一个类有5个特殊的成员函数：拷贝构造函数Foo(const Foo&)，拷贝赋值运算符，移动构造函数，移动赋值运算符，析构函数
    一个类如果没有定义这些函数，则编译器自动生成一个。
    数组的拷贝构造是逐个拷贝赋值。
    以下情况属于拷贝初始化：
    string nines=string(100,'9');
    拷贝初始化过程中编译器可以跳过拷贝/移动构造函数，直接创建对象，但是拷贝/移动函数必须是存在且可访问，否则就不能使用拷贝初始化。
    例如，Foo(const Foo&)= delete;则Foo foo=Foo(1)将不能被调用

    拷贝赋值运算符：
    Foo foo,bar;
    foo=bar; // 拷贝赋值运算符，operator=
    标准形式： Foo & Foo::operator=(const Foo & foo);
    合成的拷贝赋值运算符递归地调用所有对象的operator=

    5法则：通常必须明确定义这5个函数，要么删除，要么自定义。

    析构函数不能使用=delete.

    一个附加函数：swap，管理资源的类通常定义这个函数。基本实现：Foo temp=bar;bar=foo;foo=temp;这个就是标准库swap的基本实现。

    std::move <utility>, 原来的对象不再需要，而新对象总是可以被析构的。
    右值引用指向一个临时对象。std::move将一个左值对象变成一个右值引用。移动构造函数原型如下：
    Foo(Foo &&foo);

    使用noexcept通知编译器不会抛出异常：
    Foo(Foo &&foo)noexcept;必须在定义和声明中都指定noexecpt
    移动构造函数和移动赋值操作符通常都是noexcept的。

    运算符重载：+,-,*,/,...->,->*,new,new[],delete,delete[],(),[]
    不能重载：::,.*,.,?:

    标准库函数运算子：<functional>
    plus<T>, minus<T>,...,logical_and<T>
    这些可被看成是命名的操作符。

    标准库function类型：
    function<T> f; T具有下面的形式： retType(args),也就是说，这里使用了一种新的模板。

    类型转换运算符：
    operator type() const;当使用(type)foo时这个调用发生，没有返回值，没有参数。
    最好是explicity的

    OOP设计：
    如果父类有virtual函数，则如果子类也有该函数（可以没有virtual），就调用子类的函数。子类的函数可以明确加上override来显示重写父类函数。
    如果子类没有覆盖基类虚函数，则使用基类的函数。

    final防止继承发生：
    class Foo final{/**/};
    final防止重写：
    void foo()final;
    回避虚函数机制： baseP->Foo::method();

    派生类可以重写访问规则，比如：
    public Foo:private Bar{
        public:
            using Bar::n;
        };
    }


    模板与泛型编程：
    非类函数模板可以根据调用的参数来实例化模板
    模板中可以含有非类型参数，而可以是一个具体的值
    template <unsigned N>
    ...

    类模板：编译器不能为类模板推断实参类型。
    这样，类中出现的目标就分为两类：类模板参数和类成员函数参数，静态函数模板参数3类。
    其中，类成员函数模板和静态函数模板是可以推断的，不必明确写出；其次，类的模板参数+函数的模板参数才能算是完整的模板参数

    模板类的静态成员并不是只有一个！每个实例化的类都有一个静态的成员。要记住：模板只是用于生成代码。对于模板的属性以及成员函数，都可以采用特化：
    template <class T> Foo<T>::s=0;
    template <> Foo<bool>::s=true;//特化bool类型

    friend也有其template形式。

    控制实例化：只有模板被使用时才会进行实例化。这就意味着相同的模板可能出现在多个源文件中，显式实例化：
    template class Foo<int>;//生成代码
    extern template class Foo<int>;//声明，阻止生成代码

    注意，实例化定义语句可以出现在函数体之前，这是编译器允许的，其含义是：稍后看到这个类的任何函数体，将其生成一份特例。
    也就是说，实例化定义允许出现在能够真正实例化之前，只要能在一次编译过程中（不管先后）得到定义体。
    auto可以用于返回值。

    std::move使用static_cast的一个特性：可以将左值强制转换为右值引用。

    可变参数模板
    参数包有两种：模板参数包和函数参数包。
    使用class...args来表示一个包。
    template <class T,class...Args>
    void foo(const T& t,const Args&...rest);
    编译器根据不同的参数实例化出不同参数的函数：
    void foo(const int &,const int &i,const double &b);
    void foo(const int&,const int &d,const int &c,const float &i);

    sizeof...运算符可用于确定参数的个数。
    可变参数通常是递归实现的：
    template <class T>
    void print(const T& t){
        cout << t << endl;
    }
    template <class T,typename...Args>
    void print(const T&t,const Args&...args)
    {
        print(t);
        print(args...);//注意这种调用方式
    }
    注意：上面代码能够终止的原因是：编译器总是优先匹配非可变参数版本，因此到调用print(2,3)时，分解为两个调用：print(2),print(3...)，由于3...没有多余参数了，因此匹配第一个。

```c++
void print(){cout << "void "<<endl;}

template <class T,typename...Args>
void print(const T&t,const Args&...args)
{
    cout << t << endl;
    if(sizeof...(args) >= 1)
        print(args...);//注意这种调用方式
}
```

    模板特例化：
    templatet <typename T> int compare(const T&,const T&);
    template <size_t N,size_t M>
    int compare(const char(&)[N],const char(&)[M]);
    允许调用compare("him","you");看起来很美好。
    如果不提供任何模板参数，应当使用<>.


高级部分II：
    异常，命名空间，多重继承在设计大型程序时有用。
    特定工具和技术：重新定义内存分配机制，C++对运行时类型识别(RTTI),定义指向类成员的指针
    不可以移植特性：volatile,位域,链接指令

    标准库：tuple,bitset,正则表达式,随机数

    tuple类：make_tuple,std::get<i>来使用。

    可以使用tuple来返回多个值。

    bitset类型：是一个常数模板类，可以声明所需要的位数。bitset可以从string初始化：
    bitset<32> bitvec4("1100");
    操作：any(),all(),none(),count(),size(),test(pos),set(pos,v),set(),flip(pos),flip(),b[pos](布尔型),to_string(zero,one)

    正则表达式工具箱：regex类,regex_match函数,regex_search函数,regex_replace函数,sregex_iterator迭代器,smatch容器类,ssub_match结果类，其中s前缀表示针对字符串string类型
    cmatch表示对c字符串操作。

    regex_search,regex_match都返回bool，参数格式：(s, match,regex,match_flag)
    表示在s上执行操作，中间结果放到match上。match可以被省略。
    例子: regex pattern("[[:alpha:]]*d");
    表示任何以d结尾的仅含字母的字符串

    regex的匹配标识：icase(忽略大小写)  nosubs(不保存子匹配)  optimize(优化)  ECMAScript(使用ECMA-262语法) basic,extended,awk,grep,egrep参见unixgrep。

    regex_rror 如果正则表达式运行错误，抛出此异常。

    regex_search只搜索出现的第一个匹配，要想得到所有匹配，使用sregex_iterator和sregex_search
    sregex_iterator(str.begin(),string.end(),re);
    单独:sregex_iterator it;//声明end迭代器位置
    it的内容： [prefix][it][suffix]=整个字符串,prefix,suffix就是具体的上下文,it还包括方法：str,length,下标由prefix().length()决定,size()表示字表达式ssub_match的数目，和length()不同。

    ssub_match类型：表示的是匹配中的()捕获的部分。

    regex_replace(dest,s,re,fmt,match_flag);
    dest表明写入迭代器的位置，可以省略

    smatch.format("$2.$1");//$表示组引用
    regex_replace("55.66",regex("(\\d{2})\\.(\\d{2})"),"$2.$1");


    随机数<random>
    简单c库：rand函数0~INT_MAX
    c++标准的随机数库组成： 
    引擎--生成随机数列，通常是default_random_engine 分布---使用引擎生成服从特定概率分布的数
    default_random_engine e;// e(种子)可选
    cout << e() << endl;//使用e()生成一个数。
    e.min(),e.max()


    分布：
    uniform_int_distribution<unsigned> u(0,9);
    cout << u(e) << endl;//e调用引擎生成符合分布的值


    IO库再探
    boolalpha:默认打印true1,false0,boolalpha改变这个行为。相应有noboolalpha
    其他：oct,hex,dec,
    showbase显示0x,0前导
    uppercase大写，默认小写
    对齐：setw(12)  left,right,setfill(' ')

    底层IO
    is.get(ch),os.put(ch),is.get(),is.pushback(),is.unget(),is.peek()
    getline(dest_arr,size,delim)
    gcount()
    seek|tell(g|p),表示读写版本的位置控制


    析构函数尽量不抛出异常，如果有异常，在其内部处理。

    异常可在被重新抛出，使用单独的throw语句：
    ...
    catch(...){
        // do some corrections
        throw;
    }
    也可以throw exception();构造函数

    可以初始化列表值try：
    Foo() try:
    ...{

        } catch(...){

        }
    这是处理构造函数初始化异常的唯一方法。

    noexcept说明有助于编译器生成优化的代码。当noexcept抛出异常时，程序直接调用terminate程序。
    noexcept(true|false),默认是true。
    noexcept实际上是一个运算符,noexcept(g())用于计算g是否抛出异常，但是并不真正调用g。

    异常层次：
    exception---|
                |
                |
                |-bad_cast
                |-bad_alloc
                |-runtime_error-|
                                |--overflow_error
                                |--underflow_error
                                |--range_error
                |-logic_error---|
                                |--domain_error
                                |--invalid_argument
                                |--out_of_range
                                |--length_error

    C++使用未命名的命名空间替代c语言的static，实现一个名称仅在本文件有效。
    namespace{//该空间的所有名称，仅在该文件有效

    }

    namespace alias=std;//起别名。

    控制内存分配：重载new和delete
    可重载形式：
    void *operator new(size_t);
    void *operator new[](size_t);
    void *operator delete(void*)noexcept;
    void *operator delete[](void*)noexcept;

    void *operator new(size_t,nothrow_t &)noexcept;
    void *operator new(size_t,nothrow_t &)noexcept;
    void *operator delete(void*,nothrow_t&)noexcept;
    void *operator delete[](void*,nothrow_t&)noexcept;
    
    nothrow_t是定义在new中的一个空struct，还有一个nothrow的const对象。

    不能重载的函数：void *operator new(size_t, void*);

    new是一个操作指示符，并不是一个函数调用。因此，当重载了operator new(size_t i);之后，如果使用new int,并不是直接调用operator new,而是先计算int的大小，然后将此大小传递给operator new,再执行构造。
```c++
void *operator new(size_t i)
{
    cout << "new ("<<i<<")"<<endl;
    return nullptr;
}
void *operator new(size_t i,int j)
{
    cout << "new ("<<i<<","<<j<<")"<<endl;
    return nullptr;
}

int main() noexcept {
    void *p=new int;//sizeof(int)
    void *p2=new (3)int;//打印4,3
    
    return 0;
}
```

    重载的基本要求：
    void *operator new(size_t size){
        if(void *mem=malloc(size))
            return mem;
        else
            throw bad_alloc();
    }
    void operator delete(void *mem)noexcept{free(mem);}

    运行时类型识别
    RTTI由两个运算符实现：typeid和dynamic_cast（将基指针安全第一地向子类转换）
    dynamic_cast支持的形式如下：
    dynamic_cast<type*>(p),dynamic_cast<type&>(lval),dynamic_cast<type&&>(rval)
    注意，dynamic_cast只能转换指针或者引用，并且用于向子类转换

    <typeinfo>
    typeid(e)，e可以是类型名称或者任意表达式，返回type_info类型,该对象有一个name()方法，用于获取可打印的名称。

    Base *pb=new Base;
    Son *ps=pb;
    if(typeid(*bp)==typeid(*dp))//检查运行时对象是否相同，也就是只有到运行时才能知道
    {
        /**/
    }

    注意，typeid的对象如果没有虚函数，则编译期就可以知道它的静态类型并且知道此类型不会改变。
```c++
class Base{
public:
    virtual ~Base()= default;//如果去掉此句，则下面打印0;因为编译期就可求值，否则等到运行期确定。
};

class Son:public  Base{
public:
};


int main() noexcept {
    Son *pson=new Son;
    Base *pbase=pson;
    cout << (typeid(*pson)== typeid(*pbase)) << endl;

    return 0;
}
```

    枚举类型：
    限定作用域：enum class [name]{...}, 该枚举类型作用域是限定的,意味着在该enum类之外成员被隐藏，必须通过类名来引用
    不限作用域：enum [name]{...}
    enum color{green};
    enum class peppers {red,yello,green};
    cout << green << endl;//使用的是color::green
    cout << peppers::green<<endl;//显示访问

    只要enum有名字，就可以被初始化为一个对象，且可以隐式转化为int。
    enum可以指定类型：
    enum ints:unsigned long long{
        i=255UL,
    };

    类成员指针
    使用const string Screen::*pdata;来声明pdata是一个指向Screen类string成员的指针。可以指向任何Screen对象。
    pdata=&Screen::contents;//指向其中的一个具体的域
    auto pdata=&Screen::contents;
    解引用： myScreen.*pdata,pmyScreen->*pdata.
    .*,->*是运算符。

    成员函数指针：auto pmf=&Screen::get_cursor;
    (myScreen.*pmf)(...);

    using别名：using Action=char (Screen::*)(Screen::pos,Screen::pos)const;
    Action get=&Screen::get;

    位域与机器相关。
    volatile表示拒绝编译器的优化。