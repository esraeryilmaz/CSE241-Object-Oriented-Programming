// GTUVector.h

#ifndef GTUVECTOR_H
#define GTUVECTOR_H

#include "GTUContainer.h"

namespace eryilmaz
{
	template <typename T>
	class GTUVector : public GTUContainer<T>
	{
	public:
		GTUVector();			//no parameter constructor
		GTUVector(int inputSize);//one parameter constructor
		GTUVector(const GTUVector& other);	//copy constructor

		bool empty()const override;
		int size()const override;
		int max_size()const override;
		void insert(const T& val) override;
		void erase(const T& val) override;
		void clear() override;
		GTUIterator<T> begin()const override;
		GTUIterator<T> end()const override;
		T& operator[](const T& index);

	};

}

#endif //GTUVector.h