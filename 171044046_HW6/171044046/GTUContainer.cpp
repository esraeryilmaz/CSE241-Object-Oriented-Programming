// GTUContainer.cpp

#include "GTUContainer.h"
#include "GTUSet.h"
#include <iostream>

namespace eryilmaz
{
	template<typename T>
	GTUContainer<T>::GTUContainer()
	{
		data = nullptr;
		_size = 0;
	}

	template<typename T>
	GTUContainer<T>::GTUContainer(int inputSize)
	{
		_size = inputSize;
		shared_ptr<T> temp(new T[_size], default_delete<T[]>());
		data = temp;
	}

	template<typename T>
	GTUContainer<T>::GTUContainer(const GTUContainer& other)
	{
		_size = other.getSize();
		shared_ptr<T> temp(new T[_size], default_delete<T[]>());
		data = temp;

		for(int i=0 ; i<_size ; ++i)
			data.get()[i] = other.data.get()[i];
	}


}