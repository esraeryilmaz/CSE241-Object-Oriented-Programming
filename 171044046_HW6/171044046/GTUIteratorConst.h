// GTUIteratorConst.h

#ifndef GTUITERATORCONST_H
#define GTUITERATORCONST_H

#include <memory>
#include <exception>

namespace eryilmaz
{
	template <typename T>
	class GTUIteratorConst
	{
	public:
		GTUIteratorConst();			//no parameter constructor
		GTUIteratorConst(T * inputIter);		//one parameter constructor
		GTUIteratorConst(const GTUIteratorConst& other);	//copy constructor
		~GTUIteratorConst() = default;

		T& operator*()const;
		T* operator->()const;
		GTUIteratorConst<T>& operator++();
		GTUIteratorConst<T>& operator--();
		GTUIteratorConst<T>& operator=(const GTUIteratorConst& other);
		bool operator==(const GTUIteratorConst& other)const;
		bool operator!=(const GTUIteratorConst& other)const;

	private:
		T *iter;

	};

}

#endif //GTUIteratorConst.h