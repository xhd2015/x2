# 此文件
对侯捷的STL源码分析（2002年）书籍作读书记录

# 概述（3~43）
STL六大组件：容器 算法 迭代器 函数 空间配置器 适配器
容器通过空间配置器取得数据存储的空间
算法通过迭代器存取容器的内容
函数协助算法完成不同的策略
适配器修饰函数

# 空间配置器 allocator (43~)
allocator需要配置的type:
value_type pointer const_pointer reference const_reference size_type difference_type

rebind  一个类模板,拥有唯一的成员other
allocator() 默认构造函数
allocator(const allocator &)  拷贝构造函数
template <class U> allocator(const &allocator<U> &)   能够从任何其他分配器复制
~allocator()
pointer address(reference x)const; &x
const_pointer address(const_reference x)const;  &x
 pointer allocate(size_type n,const void *local=0);//local参数表明需要在附近分配
 void deallocate(pointer p,size_type n);//归还空间
 size_type max_size()const; 最大容量
 void construct(pointer p,const T& x);placement 构造
 void destroy(pointer p); 调用析构函数

 虽然STL标准使用std::allocator作为标准空间配置器，但是效率不佳，SGI自定义了一个新的配置器std::alloc,该类不使用泛型。
 其内部string,vector等使用的都是std::alloc
