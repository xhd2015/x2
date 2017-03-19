
#ifndef Int2Type_h__
#define Int2Type_h__

template <int V>
class Int2Type{
public:
	enum{value = V};
};


template <class T>
class NullType;

class EmptyType{};

#endif //Int2Type_h__
