// GTUSet.h

#ifndef GTUSET_H
#define GTUSET_H

#include "GTUContainer.h"

namespace eryilmaz
{
	template <typename T>
	class GTUSet : public GTUContainer<T>
	{
	public:
		GTUSet();			//no parameter constructor
		GTUSet(int inputSize);		//one parameter constructor
		GTUSet(const GTUSet& other);	//copy constructor

		bool empty()const override;
		int size()const override;
		int max_size()const override;
		void insert(const T& val) override;
		void erase(const T& val) override;
		void clear() override;
		GTUIterator<T> begin()const override;
		GTUIterator<T> end()const override;

	};

}

#endif	//GTUSet.h