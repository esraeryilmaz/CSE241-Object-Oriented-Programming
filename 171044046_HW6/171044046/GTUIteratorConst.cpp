// GTUIteratorConst.cpp

#include "GTUIteratorConst.h"

namespace eryilmaz
{
	template<typename T>
	GTUIteratorConst<T>::GTUIteratorConst() : iter(nullptr)
	{
		//deliberately empty
	}

	template<typename T>
	GTUIteratorConst<T>::GTUIteratorConst(T * inputIter) : iter(inputIter)
	{
		//deliberately empty
	}

	template<typename T>
	GTUIteratorConst<T>::GTUIteratorConst(const GTUIteratorConst& other) : iter(other.iter)
	{
		//deliberately empty
	}

	template<typename T>
	T& GTUIteratorConst<T>::operator*()const
	{
		return *iter;
	}

	template<typename T>
	T* GTUIteratorConst<T>::operator->()const
	{
		return iter;
	}

	template<typename T>
	GTUIteratorConst<T>& GTUIteratorConst<T>::operator++()
	{
		++iter;
		return *this;
	}

	template<typename T>
	GTUIteratorConst<T>& GTUIteratorConst<T>::operator--()
	{
		--iter;
		return *this;
	}

	template<typename T>
	GTUIteratorConst<T>& GTUIteratorConst<T>::operator=(const GTUIteratorConst& other)
	{
		iter = other.iter;
		return *this;
	}

	template<typename T>
	bool GTUIteratorConst<T>::operator==(const GTUIteratorConst& other)const
	{
		return (iter == other.iter);
	}

	template<typename T>
	bool GTUIteratorConst<T>::operator!=(const GTUIteratorConst& other)const
	{
		return (this->iter != other.iter);
	}

}