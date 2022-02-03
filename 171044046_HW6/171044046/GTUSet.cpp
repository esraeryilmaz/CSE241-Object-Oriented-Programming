// GTUSet.cpp

#include "GTUSet.h"

namespace eryilmaz
{
	template<typename T>
	GTUSet<T>::GTUSet() : GTUContainer<T>::GTUContainer()
	{
		//deliberately empty
	}

	template<typename T>
	GTUSet<T>::GTUSet(int inputSize) : GTUContainer<T>::GTUContainer(inputSize)
	{
		//deliberately empty
	}

	template<typename T>
	GTUSet<T>::GTUSet(const GTUSet& other) : GTUContainer<T>::GTUContainer(other)
	{
		//deliberately empty
	}

	template<typename T>
	bool GTUSet<T>::empty()const
	{
		if(this->_size == 0)
			return true;
		else
			return false;
	}

	template<typename T>
	int GTUSet<T>::size()const
	{
		return (this->_size);
	}

	template<typename T>
	int GTUSet<T>::max_size()const
	{
		return (this->_size);	//for size I keep just one data and I return that size;
	}

	template<typename T>
	void GTUSet<T>::insert(const T& val)
	{
		int exist = 0;

		T* temp = this->data.get();
		for(int i=0 ; i<this->_size ; ++i)
		{
			if(*temp == val)
			{
				exist = 1;
				cout<<"You cannot insert "<< val <<endl;
				break;
			}
			++temp;
		}

		if(exist == 1)		//if value is already exist in the set than throws exception
		{
			throw std::invalid_argument("That value already in the set!");
		}
		else
		{
			shared_ptr<T> temp = this->data;

			shared_ptr<T> temp2(new T[this->_size+1], default_delete<T[]>());
			this->data = temp2;

			for(int i=0 ; i<this->_size ; ++i)
				this->data.get()[i] = temp.get()[i];

			this->data.get()[this->_size] = val;		//inserting new value at the end of the set
			this->_size +=1;		//increment size by one
		}
	}

	template<typename T>
	void GTUSet<T>::erase(const T& val)
	{
		int j=0;
		T* tmp = new T[this->_size];

		//I put all data ​​into the temporary variable except the value which will be deleted.
		for(int i=0 ; i<this->_size ; ++i)
		{
			if(val != this->data.get()[i])
			{
				tmp[j] = this->data.get()[i];
				++j;
			}
		}

		this->_size -= 1;		//decrement size by one
		shared_ptr<T> temp(new T[this->_size], default_delete<T[]>());
		this->data = temp;		//extended new shared pointer

		for(int i=0 ; i<this->_size ; ++i)
			this->data.get()[i] = tmp[i];		//assign values ​​from the temporary variable to the actual variable.

		cout<< "Erase -> "<< val <<endl;
	}

	template<typename T>
	void GTUSet<T>::clear()
	{
		this->data = nullptr;
		this->_size = 0;
	}

	template<typename T>
	GTUIterator<T> GTUSet<T>::begin()const
	{
		return (this->data).get();
	}

	template<typename T>
	GTUIterator<T> GTUSet<T>::end()const
	{
		return (this->data).get() + (this->_size);
	}

}