# 此文件
boost库的mpl库手册

# 基本概念
原始类型：c++的内置类型，int,long等
基本类型：指的是通过包装原始类型，提供type,value,value_type等信息的结构体，如
值包装类型：即通过一个结构体将常数值转换成value.可以视为一个接受常数作为参数，返回常数的函数。

函数：这里的函数是指接受类型名或者常数作为参数，并返回多个值的结构体。
所有的函数F,对同一个参数V，对任意返回值R，任何调用F<V>::R都是相同的。
这就是函数的纯函数性质。（因为实际上c++编译器只实例化一次）
如果将begin<l>::type分解，则begin是函数名，<l>是实参列表,::type是返回值。
可以返回多个值，比如::value等。
分类： 接受常数，返回常数；
    接受原始类型，返回原始类型；
    接受函数，返回原始类型；
    接受函数，返回函数。
所有的vector实际上都可以视为函数。
因此实际上mpl库是一个高阶编程库
函数名的_c后缀一般接受一系列的常数类型，没有后缀则是接受函数类型。

函数的阶：指的是通过多少次返回能够返回原始类型或者常数。
如 using t = int_<0>;  是一阶的,因为t::value一次
using t = type2type< type2type< int_<0> > > 是3阶的，因为t::type::type::value即可返回常数，但是注意，有的类型是递归的（比如::type返回自身,::value返回值）
可以找到一个T的返回值P，order<T::P> less that order<P>.

通常一个函数会增加其参数的阶，比如insert< vector,int>,但是通过其返回值，它又回到相同的阶 insert< vector,int>::type.

序列（Sequence）：指的是编译期的数据结构，vector,list,deque,set,map,range_c,vector_c,list_c,set_c

序列通用函数：(都是+1阶函数)
size,begin,end,empty,
front,back,at,insert,clear,push_back,pop_back,push_front,pop_front
empty::type返回的是一个函数，该函数可返回一个常数。（也就是说没有直接通过value返回函数本身）empty没有直接返回值类型，因为一个函数调用最好+1阶，而函数返回值-1阶，这样一次函数过程就同阶无变化。
再如at,typedef set< int const,long*,double > s;
BOOST_MPL_ASSERT(( is_same< at< s,char>::type, void_ > ))
void_是1阶函数，set也是1阶函数。一次函数过程没有改变其阶。要是at< s,char>::type = void,那么它将无法用于其他同阶函数。比如sizeof_,而只能是sizeof.

迭代器：迭代器是一阶的
迭代器操作函数是同阶函数，譬如deref< iter> 得到一个一阶的，而iter本身也是一阶的。deref< iter>::type降阶。
```c++
typedef vector< unsigned char,unsigned short,
unsigned int,unsigned long > unsigned_types;
typedef begin<unsigned_types>::type iter;
BOOST_MPL_ASSERT(( is_same< deref<iter>::type, unsigned char > ));
```

# lambda表达式
包括占位符表达式和元函数

占位符表达式包括：
    占位符
    包含占位符的函数

元函数：
    内部有一个apply函数的函数/能够返回apply函数的函数叫做元函数
```c++
struct my_make_unsigned2{
    template <typename T>
    struct apply{
        using type = typename std::make_unsigned<T>::type;
    };
};
```

# transfer_view
```c++
template <typename T>
struct my_make_unsigned{
    using type =typename std::make_unsigned<T>::type;
};
struct my_make_unsigned2{
    template <typename T>
    struct apply{
        using type = typename std::make_unsigned<T>::type;
    };
};
int main() {
    using unsignedType =  mpl::transform_view<signedType,my_make_unsigned<_>>::type;
    using unsignedType2 =  mpl::transform_view<signedType,my_make_unsigned2>::type;
        using unsignedInt = deref<mpl::begin<unsignedType2>::type>::type;

    BOOST_MPL_ASSERT_RELATION( (boost::is_same<unsignedInt,unsigned int>::value),==,true);
}
```