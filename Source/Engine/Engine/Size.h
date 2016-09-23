#pragma once
#include <ostream>

template <typename TUnit>
struct Size
{
public:
	Size();
	Size(TUnit aWidth, TUnit aHeight);
	~Size();
	
	TUnit width;
	TUnit height;
};

template<typename TUnit>
Size<TUnit>::Size(TUnit aWidth, TUnit aHeight)
{
	width = aWidth;
	height = aHeight;
}

template<typename TUnit>
Size<TUnit>::Size()
{
	width = static_cast<TUnit>(0);
	height = static_cast<TUnit>(0);
}

template<typename TUnit>
Size<TUnit>::~Size()
{
}

template<typename TUnit>
std::ostream & operator<<(std::ostream & os, const Size<TUnit> & aSize)
{
	os << "[Size<" << typeid(TUnit).name() << ">] (" << aSize.width << "; " << aSize.height << ")";
	return os;
}
