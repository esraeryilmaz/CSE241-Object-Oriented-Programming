/*
 *	main.cpp	(Driver file)
 *
 *	CSE241_HW6 - Inheritance, Templates, STL
 *
 *	Date:	23.12.2019
 *	Author:	Esra ERYILMAZ	171044046
 *
 *
 *	NOTES !!
 *	Global functions are in the "GTUIterator.h" file
 *	I print the containers, iterating the containers OR using for_each() function
 *	I used lambda functions to test find_if() and for_each() functions
 *
 */

#include "GTUContainer.h"
#include "GTUContainer.cpp"
#include "GTUSet.h"
#include "GTUSet.cpp"
#include "GTUVector.h"
#include "GTUVector.cpp"
#include "GTUIterator.cpp"
#include "GTUIteratorConst.cpp"

#include <iostream>
#include <string>

using namespace eryilmaz;
using namespace std;


int main()
{
	GTUSet<int> int_set;
	GTUSet<string> string_set;

	cout<< "\n\t\tTEST STARTING...\n"<<endl;
	cout <<"-----------------------------------------------"<<endl;

	cout<< "\tTEST -SET CLASS- STARTING...\n"<<endl;

	cout<<"Integer set : "<<endl;
	try
	{
		int_set.insert(2);
		int_set.insert(7);
		int_set.insert(4);
		int_set.insert(5);
		int_set.insert(9);
		int_set.insert(2);		//exception
	}
	catch(invalid_argument& e)
	{
		cout<<"Error : "<<e.what()<<endl;
	}

	cout<< "Integer set contains: \n";
	for(auto it=int_set.begin() ; it != int_set.end() ; ++it)
		cout<< *it << " ";
	cout<<"\n\n";


	int_set.erase(4);
	cout<< "Integer set contains: \n";
	for(auto it=int_set.begin() ; it != int_set.end() ; ++it)
		cout<< *it << " ";
	cout<<"\n\n";

	/*	I use a lambda function to test find_if functions	*/
	auto firstOdd = [](int n){ return (n%2 != 0); };

	auto iterater = find_if(int_set.begin(), int_set.end(), firstOdd);
	cout << "find_if() test -> First odd number is = " << *iterater <<endl;

	cout <<"Integer set size is -> "
		<< int_set.size() <<endl;
	cout <<"Integer set max_size is -> "
		<< int_set.max_size() <<endl;
	cout <<"Clear the set "<<endl;
	int_set.clear();
	cout <<"Integer set size is -> "
		<< int_set.size() <<endl;
	cout <<"Is integer set empty? -> "
		<< int_set.empty() <<endl;

	cout<<"\n------\n\n";

	cout<<"String set : "<<endl;
	try
	{
		string_set.insert("Esra");
		string_set.insert("Fatma");
		string_set.insert("Ahmet");
		string_set.insert("Mehmet");
		string_set.insert("Esra");		//exception
	}
	catch(invalid_argument& e)
	{
		cout<<"Error : "<<e.what()<<endl;
	}

	cout<< "String set contains: \n";

	/*	I use a lambda function to test for_each functions	*/
	auto print = [](string n) {cout << n << " "; };
	for_each(string_set.begin(), string_set.end(), print);
	cout << endl<<endl;

	auto it = find(string_set.begin(), string_set.end(), "Esra");
	if(it != string_set.end())
		cout << "Element found in string_set: " << *it << '\n';
	else
		cout << "Element not found in string_set: Esra\n";

	it = find(string_set.begin(), string_set.end(), "Melis");
	if(it != string_set.end())
		cout << "Element found in string_set: " << *it << '\n';
	else
		cout << "Element not found in string_set: Melis\n";
	cout<<endl;

	string_set.erase("Fatma");
	cout<< "String set contains: \n";
	for(auto it=string_set.begin() ; it != string_set.end() ; ++it)
		cout<< *it << " ";
	cout<<"\n\n";

	cout <<"String set size is -> "
		<< string_set.size() <<endl;
	cout <<"String set max_size is -> "
		<< string_set.max_size() <<endl;
	cout <<"Is string set empty? -> "
		<< string_set.empty() <<endl;
	cout <<"Clear the set "<<endl;
	string_set.clear();
	cout <<"String set size is -> "
		<< string_set.size() <<endl;

	cout <<"-----------------------------------------------"<<endl;

	cout<< "\tTEST -VECTOR CLASS- STARTING...\n"<<endl;

	GTUVector<int> int_vector;
	GTUVector<string> string_vector;

	cout<<"Integer vector : "<<endl;
	int_vector.insert(0);
	int_vector.insert(6);
	int_vector.insert(7);
	int_vector.insert(1);
	int_vector.insert(8);
	int_vector.insert(1);

	cout<< "Integer vector contains: \n";
	for(auto it=int_vector.begin() ; it != int_vector.end() ; ++it)
		cout<< *it << " ";
	cout<<"\n\n";

	cout<<"int_vector[1] = " << int_vector[1] << endl;
	cout<<"int_vector[4] = " << int_vector[4] << endl << endl ;

	auto iter = find_if(int_vector.begin(), int_vector.end(), firstOdd);
	cout << "find_if() test -> First odd number is = " << *iter <<endl;

	int_vector.erase(8);

	cout<< "Integer vector contains: \n";

	auto print2 = [](int n) {cout << n << " "; };
	for_each(int_vector.begin(), int_vector.end(), print2);
	cout << endl<<endl;

	cout <<"Integer vector size is -> "
		<< int_vector.size() <<endl;
	cout <<"Integer vector max_size is -> "
		<< int_vector.max_size() <<endl;
	cout <<"Clear the vector "<<endl;
	int_vector.clear();
	cout <<"Integer vector size is -> "
		<< int_vector.size() <<endl;
	cout <<"Is integer vector empty? -> "
		<< int_vector.empty() <<endl;

	cout<<"\n------\n\n";

	cout<<"String vector : "<<endl;

	string_vector.insert("Esra");
	string_vector.insert("Fatma");
	string_vector.insert("Ahmet");
	string_vector.insert("Mehmet");
	string_vector.insert("Esra");

	cout<< "String vector contains: \n";

	for_each(string_vector.begin(), string_vector.end(), print);
	cout << endl << endl;

	auto i = find(string_vector.begin(), string_vector.end(), "Ahmet");
	if(i != string_vector.end())
		cout << "Element found in string_vector: " << *i << '\n';
	else
		cout << "Element not found in string_vector : Ahmet\n";

	i = find(string_vector.begin(), string_vector.end(), "Zehra");
	if(i != string_vector.end())
		cout << "Element found in string_vector: " << *i << '\n';
	else
		cout << "Element not found in string_vector : Zehra\n";
	cout<<endl;

	string_vector.erase("Mehmet");

	cout<< "String vector contains: \n";
	for(auto it=string_vector.begin() ; it != string_vector.end() ; ++it)
		cout<< *it << " ";
	cout<<"\n\n";

	cout <<"String vector size is -> "
		<< string_vector.size() <<endl;
	cout <<"String vector max_size is -> "
		<< string_vector.max_size() <<endl;
	cout <<"Is string vector empty? -> "
		<< string_vector.empty() <<endl;
	cout <<"Clear the vector "<<endl;
	string_vector.clear();
	cout <<"String vector size is -> "
		<< string_vector.size() <<endl;

	cout <<"\n-----------------------------------------------\n"<<endl;
	cout<< "\t\tTEST FINISHED...\n\n"<<endl;

	return 0;
}
