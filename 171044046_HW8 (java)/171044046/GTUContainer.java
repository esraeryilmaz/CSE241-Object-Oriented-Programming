/**
 * GTUContainer abstract class
 *
 * @author Esra Eryılmaz
 * @version 1.0
 * @since 2020-01-16
 */

import java.lang.IllegalArgumentException;


public abstract class GTUContainer<T>
{
	/**
	 *Java array to keep data
	 */
	protected T[] data;

	/**
	 *size of the container
	 */
	protected int size;

	/**
	 *returns true if the container is empty
	 *@return true or false according to the container size
	 */
	public abstract boolean empty();

	/**
	 *@return size of the container
	 */
	public abstract int size();

	/**
	 *@return maximum size of the container
	 */
	public abstract int max_size();

	/**
	 *inserts element there is no problem
	 *@param val value for insertion
	 *@throws IllegalArgumentException if there is a problem with insertion
	 */
	public abstract void insert(T val) throws IllegalArgumentException;

	/**
	 *deletes element from the container
	 *@param val value for deletion
	 */
	public abstract void erase(T val);

	/**
	 *clear all content
	 */
	public abstract void clear();

	/**
	 *returns iterator to beginning
	 */
	public abstract GTUIterator iterator();

	/**
	 *returns true if the container contains the specified element
	 *@return true or false according to the container contains
	 */
	public abstract boolean contains(Object o);



	/**
	 *	GTUIterator class to keep one element of the container
	 */
	public class GTUIterator
	{
		/**
		 *iterator position
		 */
		private int pos = 0 ;

		/**
		 *returns true if the iteration has more elements
		 */
		public boolean hasNext()
		{
			if(pos < size-1)
				return true;
			else
				return false;
		}

		/**
		 *returns the next element in the iteration.
		 */
		public T next()
		{
			if(hasNext())
				return data[pos++];

			else
			{
				pos = size-1;
				return data[pos];
			}
		}
	}

}
