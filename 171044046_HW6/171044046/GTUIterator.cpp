// GTUIterator.cpp

#include "GTUIterator.h"

namespace eryilmaz
{
	template<typename T>
	GTUIterator<T>::GTUIterator() : iter(nullptr)
	{
		//deliberately empty
	}

	template<typename T>
	GTUIterator<T>::GTUIterator(T * inputIter) : iter(inputIter)
	{
		//deliberately empty
	}

	template<typename T>
	GTUIterator<T>::GTUIterator(const GTUIterator& other) : iter(other.iter)
	{
		//deliberately empty
	}

	template<typename T>
	T& GTUIterator<T>::operator*()
	{
		return *iter;
	}

	template<typename T>
	T* GTUIterator<T>::operator->()
	{
		return iter;
	}

	template<typename T>
	GTUIterator<T>& GTUIterator<T>::operator++()
	{
		++iter;
		return *this;
	}

	template<typename T>
	GTUIterator<T>& GTUIterator<T>::operator--()
	{
		--iter;
		return *this;
	}

	template<typename T>
	GTUIterator<T>& GTUIterator<T>::operator=(const GTUIterator& other)
	{
		iter = other.iter;
		return *this;
	}

	template<typename T>
	bool GTUIterator<T>::operator==(const GTUIterator& other)const
	{
		return (iter == other.iter);
	}

	template<typename T>
	bool GTUIterator<T>::operator!=(const GTUIterator& other)const
	{
		return (this->iter != other.iter);
	}

}