/**
 * GTUVector class
 *
 * @author Esra Eryılmaz
 * @version 1.0
 * @since 2020-01-16
 */

import java.lang.IllegalArgumentException;


public class GTUVector<T> extends GTUContainer<T>
{
	/**
	 *returns true if the vector is empty
	 */
	@Override
	public boolean empty()
	{
		if(size == 0)
			return true;
		else
			return false;
	}

	/**
	 *@return size of the vector
	 */
	@Override
	public int size()
	{
		return size;
	}

	/**
	 *@return maximum size of the vector
	 */
	@Override
	public int max_size()
	{
		return size;	//for size I keep just one data and I return that size;
	}

	/**
	 *@param val value for insertion
	 */
	@Override
	public void insert(T val) throws IllegalArgumentException
	{
		@SuppressWarnings("unchecked")
		T[] temp = (T[])new Object[size+1]; 

		for(int i=0 ; i<size ; ++i) // copy the previous.
			temp[i] = data[i];

		size=size+1;
		temp[size-1] = val; // add the new.
		data = temp;
	}

	/**
	 *deletes element from the vector
	 *@param val value for deletion
	 */
	@Override
	public void erase(T val)
	{
		int new_size=0;
		T [] temp = data;

		for(int i=0,j=0; i<size ; ++i, ++j)
		{
			if(data[i] != val)
			{
				temp[j] = data[i];
				++new_size;
			}
			else
				--j;
		}

		size = new_size;

		for(int i=0; i<size; ++i)
			data[i] = temp[i];
	}

	/**
	 *clear all content
	 */
	@Override
	public void clear()
	{
		data = null;
		size = 0;
	}

	/**
	 *returns iterator to beginning
	 */
	@Override
	public GTUIterator iterator()
	{
		GTUIterator it = new GTUIterator ();
		return it;
	}

	/**
	 *returns true if the vector contains the specified element
	 *@return true or false according to the vector contains
	 */
	@Override
	public boolean contains(Object o)
	{
		boolean exist = false;

		if(empty())
		{
			exist = false;
		}
		else
		{
			for(int i=0 ; i<size ; ++i)
			{
				if(data[i] == o)
					exist = true;
			}
		}

		return exist;
	}

}