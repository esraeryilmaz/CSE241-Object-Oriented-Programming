/*
 *	main.cpp	 (Driver file)
 *
 *	CSE241_HW5 - Inheritance (N-Puzzle Game)
 *
 *	Date:	10.12.2019
 *	Author:	Esra ERYILMAZ	171044046
 *
 *********************************************************************************************************************************************
 *	NOTE!!	# I CONSIDER THERE IS A SPACE AT THE END OF EACH LINE WHEN READING AND WRITING FILES	*********************************************
 *			# I sent 2 resolvable sample files: file1.txt and file2.txt		******************************************************************
 *********************************************************************************************************************************************
 *	NOTES : GLOBAL FUNCTION IS IN THE ABSTRACTBOARD CLASS HEADER
 *			READFROMFILE FUNCTION WORKS FOR VECTORS BUT DOESN'T WORK FOR OTHER DYNAMIC BOARDS (I DONT KNOW WHY SINCE THEIR CODE SAME ACTUALLY)
 *
 *
 */

#include "AbstractBoard.h"
#include "BoardVector.h"
#include "BoardArray1D.h"
#include "BoardArray2D.h"

#include <iostream>
#include <ostream>
#include <vector>

using std::cout;
using std::endl;
using namespace eryilmazGame;


int main()
{
	AbstractBoard *a[5];

	srand(time(NULL));
	string argv;
	argv = "file1.txt";

	cout<< "\t( HW5 ) The N-Puzzle Game"<< endl<<endl;
	cout<< "\t\tTEST STARTING...\n"<<endl;
	cout <<"-----------------------------------------------------------"<<endl;

	cout<< "\tBOARDVECTOR CLASS TEST STARTING...\n"<<endl;
	BoardVector vector1;
	vector1.setSize(0,argv);
	vector1.readFromFile();
	vector1.print();
	vector1.move('L');
	vector1.print();
	vector1.move('D');
	vector1.print();
	vector1.NumberOfBoards();
	vector1.lastMove();
	vector1.numberOfMoves();
	cout<<"\n-----\n";

	BoardVector vector2;
	vector2.setSize(5,"NULL");
	vector2.shuffle();
	vector2.print();
	vector2.move('R');
	vector2.print();
	cout<< "issolved: ";
	vector2.isSolved();
	cout <<"operator(2,2):"<<vector2(2,2)<<endl;
	int x= (vector1 == vector2);
	cout<<"Is vector1 and vector2 objects are equal? = "<< x <<endl<<endl;

	cout << "\tBOARDVECTOR CLASS TEST FINISHED!\n\n";
	cout <<"-----------------------------------------------------------"<<endl;

	cout<< "\tBOARDARRAY1D CLASS TEST STARTING...\n"<<endl;
	BoardArray1D array_1d, array_1d_;
	array_1d.setSize(4, "NULL");
	array_1d.shuffle();
	array_1d.print();
	array_1d.move('I');
	array_1d.print();
	array_1d.move('R');
	array_1d.print();
	cout<< "issolved: ";
	array_1d.isSolved();
	cout<<"\n-----\n";

	array_1d_.setSize(5,"NULL");
	array_1d_.shuffle();
	array_1d_.print();
	array_1d_.move('L');
	array_1d_.print();
	cout << "\tBOARDARRAY1D CLASS TEST FINISHED!\n\n";
	cout <<"-----------------------------------------------------------"<<endl;


	cout<< "\tBOARDARRAY2D CLASS TEST STARTING...\n"<<endl;
	BoardArray2D array_2d;
	array_2d.setSize(3, "NULL");
	array_2d.shuffle();
	array_2d.print();
	array_2d.move('R');
	array_2d.print();
	array_2d.move('D');
	array_2d.print();

	cout << "\tBOARDARRAY2D CLASS TEST FINISHED!\n\n";
	cout <<"-----------------------------------------------------------"<<endl;


	cout<< "\tGLOBAL FUNCTION TEST STARTING...\n"<<endl;
	a[0] = &vector1;
	a[1] = &vector2;
	a[2] = &array_1d;
	a[3] = &array_2d;
	a[4] = &array_1d_;
	validMoves(a);

	cout << "\tGLOBAL FUNCTION TEST FINISHED!\n\n";
	cout <<"-----------------------------------------------------------\n\n";

	return 0;
}