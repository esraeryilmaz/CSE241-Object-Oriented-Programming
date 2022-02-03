/**
 * Main class  (Driver file)
 *
 * @author Esra Eryılmaz
 * @version 1.0
 * @since 2020-01-16
 */


//I implement GTUIterator inside GTUContainer.java file
public class Main
{
	public static void main(String[] args) 
	{
		GTUSet<Integer> int_set = new GTUSet<Integer>();
		GTUSet<String> string_set = new GTUSet<String>();
		GTUSet<Integer>.GTUIterator int_iter = int_set.new GTUIterator();
		GTUSet<String>.GTUIterator string_iter = string_set.new GTUIterator();

		GTUVector<Integer> int_vector = new GTUVector<Integer>();
		GTUVector<String> string_vector = new GTUVector<String>();
		GTUVector<Integer>.GTUIterator int_iter2 = int_vector.new GTUIterator();
		GTUVector<String>.GTUIterator string_iter2 = string_vector.new GTUIterator();


		System.out.printf("\n\t\tTEST STARTING...\n\n");
		System.out.printf("-----------------------------------------------\n");
		System.out.printf("\tTEST -SET CLASS- STARTING...\n\n");
		System.out.printf("(Integer set)\n");
		try
		{
			int_set.insert(2);
			int_set.insert(7);
			int_set.insert(4);
			int_set.insert(5);
			int_set.insert(9);
			int_set.insert(2);		//exception
		}
		catch(IllegalArgumentException e)
		{
			System.out.println("(insert)Exception : 2 is already in the set\n");
		}

		// I print container using iterator
		System.out.printf("Integer set contains: \n");
		for(int i=0; i<int_set.size(); ++i)
			System.out.printf("%d ",int_iter.next());
		System.out.printf("\n\n");

		int_iter = int_set.new GTUIterator();
		System.out.printf("Erase -> 4\n");
		int_set.erase(4);
		System.out.printf("Integer set contains: \n");
		for(int i=0; i<int_set.size(); ++i)
			System.out.printf("%d ",int_iter.next());
		System.out.printf("\n\n");

		System.out.printf("Is integer set contains 7 ? -> %b\n",int_set.contains(7));
		System.out.printf("Integer set size is -> %d\n",int_set.size());
		System.out.printf("Integer set max_size is -> %d\n",int_set.max_size());
		System.out.printf("Clear() the set \n");
		int_set.clear();
		System.out.printf("Integer set size is -> %d\n",int_set.size());
		System.out.printf("Is integer set empty? -> %b\n",int_set.empty());

		System.out.printf("\n------\n\n");
		System.out.printf("(String set)\n");
		try
		{
			string_set.insert("Esra");
			string_set.insert("Fatma");
			string_set.insert("Ahmet");
			string_set.insert("Mehmet");
			string_set.insert("Esra");		//exception
		}
		catch(IllegalArgumentException e)
		{
			System.out.println("(insert)Exception : Esra is already in the set\n");
		}

		System.out.printf("String set contains: \n");
		for(int i=0; i<string_set.size(); ++i)
			System.out.printf("%s ",string_iter.next());
		System.out.printf("\n\n");

		string_iter = string_set.new GTUIterator();
		System.out.printf("Erase -> Fatma\n");
		string_set.erase("Fatma");
		System.out.printf("String set contains: \n");
		for(int i=0; i<string_set.size(); ++i)
			System.out.printf("%s ",string_iter.next());
		System.out.printf("\n\n");

		System.out.printf("Is string set contains Melis ? -> %b\n",int_set.contains("Melis"));
		System.out.printf("String set size is -> %d\n",string_set.size());
		System.out.printf("String set max_size is -> %d\n",string_set.max_size());
		System.out.printf("Is string set empty? -> %b\n",string_set.empty());
		System.out.printf("Clear() the set \n");
		string_set.clear();
		System.out.printf("String set size is -> %d\n\n",string_set.size());

		System.out.printf("-----------------------------------------------\n");
		System.out.printf("\tTEST -VECTOR CLASS- STARTING...\n\n");

		System.out.printf("(Integer vector)\n");
		try
		{
			int_vector.insert(0);
			int_vector.insert(6);
			int_vector.insert(7);
			int_vector.insert(1);
			int_vector.insert(8);
			int_vector.insert(1);
		}
		catch(IllegalArgumentException e)
		{
			System.out.println("exception catch");
		}

		System.out.printf("Integer vector contains: \n");
		for(int i=0; i<int_vector.size(); ++i)
			System.out.printf("%d ",int_iter2.next());
		System.out.printf("\n\n");

		int_iter2 = int_vector.new GTUIterator();

		System.out.printf("Erase -> 8\n");
		int_vector.erase(8);

		System.out.printf("Integer vector contains: \n");
		for(int i=0; i<int_vector.size(); ++i)
			System.out.printf("%d ",int_iter2.next());
		System.out.printf("\n\n");

		System.out.printf("Is integer vector contains 2 ? -> %b\n",int_set.contains(2));
		System.out.printf("Integer vector size is -> %d\n",int_vector.size());
		System.out.printf("Integer vector max_size is -> %d\n",int_vector.max_size());
		System.out.printf("Clear() the vector \n");
		int_vector.clear();
		System.out.printf("Integer vector size is -> %d\n",int_vector.size());
		System.out.printf("Is integer set empty? -> %b\n",int_vector.empty());

		System.out.printf("\n------\n\n");
		System.out.printf("(String vector)\n");
		try
		{
			string_vector.insert("Esra");
			string_vector.insert("Fatma");
			string_vector.insert("Ahmet");
			string_vector.insert("Mehmet");
			string_vector.insert("Esra");
		}
		catch(IllegalArgumentException e)
		{
			System.out.println("exception catch");
		}

		System.out.printf("String vector contains: \n");
		for(int i=0; i<string_vector.size(); ++i)
			System.out.printf("%s ",string_iter2.next());
		System.out.printf("\n\n");

		string_iter2 = string_vector.new GTUIterator();

		System.out.printf("Erase -> Mehmet\n");
		string_vector.erase("Mehmet");

		System.out.printf("String vector contains: \n");
		for(int i=0; i<string_vector.size(); ++i)
			System.out.printf("%s ",string_iter2.next());
		System.out.printf("\n\n");

		System.out.printf("String vector size is -> %d\n",string_vector.size());
		System.out.printf("String vector max_size is -> %d\n",string_vector.max_size());
		System.out.printf("Is string vector empty? -> %b\n",string_vector.empty());
		System.out.printf("Clear() the vector \n");
		string_vector.clear();
		System.out.printf("String vector size is -> %d\n",string_vector.size());

		System.out.printf("-----------------------------------------------\n");
		System.out.printf("\t\tTEST FINISHED...\n\n\n");
	}

}
