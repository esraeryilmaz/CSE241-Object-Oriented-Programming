// GTUVector.cpp

#include "GTUVector.h"

namespace eryilmaz
{
	template<typename T>
	GTUVector<T>::GTUVector() :  GTUContainer<T>::GTUContainer()
	{
		//deliberately empty
	}

	template<typename T>
	GTUVector<T>::GTUVector(int inputSize) :  GTUContainer<T>::GTUContainer(inputSize)
	{
		//deliberately empty
	}

	template<typename T>
	GTUVector<T>::GTUVector(const GTUVector& other) :  GTUContainer<T>::GTUContainer(other)
	{
		//deliberately empty
	}

	template<typename T>
	bool GTUVector<T>::empty()const
	{
		if(this->_size == 0)
			return true;
		else
			return false;
	}

	template<typename T>
	int GTUVector<T>::size()const
	{
		return (this->_size);
	}

	template<typename T>
	int GTUVector<T>::max_size()const
	{
		return (this->_size);	//for size I keep just one data and I return that size;
	}

	template<typename T>
	void GTUVector<T>::insert(const T& val)
	{
		shared_ptr<T> temp = this->data;

		shared_ptr<T> temp2(new T[this->_size+1], default_delete<T[]>());
		this->data = temp2;

		for(int i=0 ; i<this->_size ; ++i)
			this->data.get()[i] = temp.get()[i];

		this->data.get()[this->_size] = val;
		this->_size +=1;
	}

	template<typename T>
	void GTUVector<T>::erase(const T& val)
	{
		int j=0;
		T* tmp = new T[this->_size];

		for(int i=0 ; i<this->_size ; ++i)
		{
			if(val != this->data.get()[i])
			{
				tmp[j] = this->data.get()[i];
				++j;
			}
		}

		this->_size -= 1;
		shared_ptr<T> temp(new T[this->_size], default_delete<T[]>());
		this->data = temp;

		for(int i=0 ; i<this->_size ; ++i)
			this->data.get()[i] = tmp[i];
		cout<< "Erase -> "<< val <<endl;
	}

	template<typename T>
	void GTUVector<T>::clear()
	{
		this->data = nullptr;
		this->_size = 0;
	}

	template<typename T>
	GTUIterator<T> GTUVector<T>::begin()const
	{
		return (this->data).get();
	}

	template<typename T>
	GTUIterator<T> GTUVector<T>::end()const
	{
		return (this->data).get() + (this->_size);
	}

	template<typename T>
	T& GTUVector<T>::operator[](const T& index)
	{
		return this->data.get()[index];
	}

}