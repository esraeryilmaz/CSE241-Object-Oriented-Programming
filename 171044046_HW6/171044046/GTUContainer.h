// GTUContainer.h

#ifndef GTUCONTAINER_H
#define GTUCONTAINER_H

#include "GTUIterator.h"
#include "GTUIteratorConst.h"
#include <iostream>
#include <memory>		//shared_ptr
#include <exception>

using namespace std;

namespace eryilmaz
{
	template <typename T>
	class GTUContainer
	{
	public:
		GTUContainer();			//no parameter constructor
		GTUContainer(int inputSize);		//one parameter constructor
		GTUContainer(const GTUContainer& other);	//copy constructor
		virtual ~GTUContainer() = default;		//default destructor

		virtual bool empty()const = 0;		//test whether container is empty
		virtual int size()const = 0;		//return container size
		virtual int max_size()const = 0;	//return maximum size
		virtual void insert(const T& val) = 0;	//insert element, throws exception if there is a problem
		virtual void erase(const T& val) = 0;	//erase element
		virtual void clear() = 0;			//clear all content
		virtual GTUIterator<T> begin()const = 0;	//return iterator to beginning
		virtual GTUIterator<T> end()const = 0;		//return iterator to end

		inline int getSize()const { return _size; }
		inline shared_ptr<T> getData()const { return data; }

	protected:
		shared_ptr<T> data;		//keeping data using shared_ptr
		int _size;

	};

}


#endif //GTUContainer.h