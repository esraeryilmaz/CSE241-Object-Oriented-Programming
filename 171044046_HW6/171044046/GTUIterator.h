// GTUIterator.h

#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include <iostream>
#include <memory>
#include <exception>


namespace eryilmaz
{
	template <typename T>
	class GTUIterator
	{
	public:
		GTUIterator();			//no parameter constructor
		GTUIterator(T * inputIter);		//one parameter constructor
		GTUIterator(const GTUIterator& other);	//copy constructor
		~GTUIterator() = default;

		T& operator*();
		T* operator->();
		GTUIterator<T>& operator++();
		GTUIterator<T>& operator--();
		GTUIterator<T>& operator=(const GTUIterator& other);
		bool operator==(const GTUIterator& other)const;
		bool operator!=(const GTUIterator& other)const;

	private:
		T *iter;

	};


	template <typename T, typename F>
 	F for_each(T first, T last, F func)
	{
		while(first != last)
		{
			func(*first);
			++first;
		}
		return func;
	}

	template <typename T, typename F>
	T find(T first, T last, const F& val)
	{
		while(first!=last)
		{
			if(*first == val)
				return first;
			else
				++first;
		}
		return last;
	}

	template <typename T, typename F>
	T find_if(T first, T last, F predicate)
	{
		while(first != last)
		{
			if(predicate(*first))
				return first;
			else
				++first;
		}
		return last;
	}

}

#endif //GTUIterator.h