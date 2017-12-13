
#ifndef Int2Type_h__
#define Int2Type_h__

namespace {
	template <int...V>
	struct __Int2Type{
		static constexpr int values[]={V...};
	};
}
template <int...V>
struct Int2Type:public __Int2Type<V...>{
	enum {value = __Int2Type<V...>::values[0] };
};
template <int V>
struct Int2Type<V>{
	enum{value = V};
};


template <class T>
class NullType;

class EmptyType{};

#endif //Int2Type_h__
