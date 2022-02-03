// BoardArray1D.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "BoardArray1D.h"

using namespace std;

namespace eryilmazGame
{
	BoardArray1D::BoardArray1D() : AbstractBoard()
	{
		board = NULL;
		ordered_board = NULL;
	}

	BoardArray1D::BoardArray1D(const BoardArray1D& other) : AbstractBoard()
	{
		board = new int[other.size];
		ordered_board = new int[other.size];

		for(int i=0 ; i<other.size ; ++i){
			board[i] = other.board[i];
			ordered_board[i] = other.ordered_board[i];
		} 
	}

	BoardArray1D & BoardArray1D::operator=(const BoardArray1D& other)
	{
		if(other.size == size)
		{
			for(int i=0 ; i<size ; ++i)
			{
				board[i] = other.board[i];
				ordered_board[i] = other.ordered_board[i];
			}
		}
		else
		{
			delete[] board;
			delete[] ordered_board;
			setSize(other.size, other.input_line);
			board = new int[size];
			ordered_board = new int[size];
			for(int i=0 ; i<size ; ++i)
			{
				board[i] = other.board[i];
				ordered_board[i] = other.ordered_board[i];
			}
		}
		return *this;
	}

	BoardArray1D::~BoardArray1D()
	{
		delete [] board;
		delete [] ordered_board;
	}

	void BoardArray1D::print()const
	{
		int k=0;
		for(int i=0 ; i<row ; ++i)
		{
			for(int j=0 ; j<column ; ++j)
			{
				if (board[k] == -10)		// -10 is a blank space for my implementation
				{
					cout << "\t";
				}
				else if(board[k] == 0)
				{
					cout << "00\t";
				}
				else if(board[k] == 1 || board[k] == 2 || board[k] == 3 || board[k] == 4 || board[k] == 5 || board[k] == 6 || board[k] == 7 || board[k] == 8 || board[k] == 9 )
				{
					cout << "0"<<board[k]<<"\t";
				}
				else
				{
					cout << board[k] << "\t";
				}
				k++;
			}
			cout<<endl;
		}
		cout<<endl;
	}

	void BoardArray1D::readFromFile()
	{
		string l;
		fstream f;

		f.open(input_line);		//open file

		if(!f.is_open())
		{
			cout << "FAILED" << endl;
		}
		else
		{
			cout<<"You write file name on command line and your initial board is:\n";
			while(getline(f, l, ' '))
			{
				if(l.find("00")==1 || l.find("00") == 0)
				{
					numb_of_zeros++;
				}
				else
				{
					size++;
				}
			}
		}
		f.close();		//close file

		board = new int[size];
		ordered_board = new int[size];
		cout<<size<<endl;
		for(int i=0 ;i<size ;++i)
			cout<<board[i]<<" "<<ordered_board[i]<<endl;


		int i=0;
		fstream file;
		file.open(input_line);		//open file
		string line;
		if(!file.is_open())
		{
			cout << "FAILED" << endl;
		}
		else
		{
			while(getline(file, line, ' '))
			{
				if (line.find("bb") == 0 || line.find("bb") == 1)
				{
					board[i] = -10;			//I take bb as a -10
					bb = i;
					i++;
				}
				else
				{
					board[i] = std::atoi(line.c_str());		//I'm casting to an integer
					cout<<board[i]<<"*";
					i++;
				}
				total_element++;
			}
		}
		file.close();		//close file


		fstream file2;
		string line2;
		file2.open(input_line);		//to find the number of row and column I've read the file again
		if(!file2.is_open())
		{
			cout << "FAILED" << endl;
		}
		else
		{
			while(getline(file2, line2))
			{
				row++;
			}
		}
		column = total_element/row;

		for(int k=0 ; k<row*column ; ++k)
		{
			ordered_board[k] = board[k];
		}

		int counter=0;		//it holds number of "00"

		for (int i=0 ; i<column*row ; ++i)
		{
			if(ordered_board[i] == 0)
			{
				counter++;
			}
		}

		int total_number = row*column -counter;
		int num = 1;
		i=0;
		while(num <= total_number)
		{
			if(ordered_board[i] != 0)
			{
				if(i == row*column-1)
				{
					ordered_board[i] = -10;
					i++;
				}
				else
				{
					ordered_board[i] = num;
					num++;
					i++;
				}
			}
			else
			{
				i++;
			}
		}

		file2.close();
	}

	void BoardArray1D::writeToFile()
	{
		cout << "Please enter file name for saving the current board configuration : ";
		string name = "newfile1.txt";
		int k=0;

		ofstream file;		//writing mode
		file.open(name);

		for(int i=0 ; i<row ; ++i){
			for(int j=0 ; j<column ; ++j){

				if (board[k] == -10)
				{
					file<<"bb ";
					k++;
				}
				else
				{
					file<<board[k]<<" ";
					k++;
				}
			}
			file<<endl;
		}
		file.close();
	}

	void BoardArray1D::reset()
	{
		for(int i=0 ; i<size*size-1 ; ++i)		// It takes the ordered_board to the final solution
		{
			board[i] = i+1;
		}

		bb = row*column-1;
		board[bb] = -10;
	}

	void BoardArray1D::setSize(const int user_size, string argv)
	{
		size = user_size;
		input_line = argv;

		if(argv == "NULL")
		{
			row = size;
			column = size;
			board = new int[size*size-1];
			ordered_board = new int[size*size-1];
		}
		numb_of_board_obj++;
	}
	void BoardArray1D::move(char action)
	{
		last_move = action;
		int move_left=0, move_right=0, move_up=0, move_down=0;

		if ( !((bb%column == 0 || board[bb-1] == 0))){
			move_left = 1;
		}
		if ( !((bb+1)%column == 0 || board[bb+1] == 0)){
			move_right = 1;
		}
		if ( !(bb < column || board[bb-column] == 0)){
			move_up = 1;
		}
		if ( !((row*column-(column+1)) < bb || board[bb+column] == 0)){
			move_down = 1;
		}

		cout << "Your action(L, R, U, D, I, S, T, E, O or Q): ";
		cout << action<< endl;

		if(action == 'L' || action == 'l')
		{
			if (move_left == 1){
				total_move++;
				swap(board[bb], board[bb-1]);
				--bb;
			}
			else{
				cout << "There is no space!!\n";
			}
		}

		else if(action == 'R' || action == 'r')
		{
			if (move_right == 1){
				total_move++;
				swap(board[bb], board[bb+1]);
				++bb;
			}
			else{
				cout << "There is no space!!\n";
			}
		}

		else if(action == 'U' || action == 'u')
		{
			if (move_up == 1){
				total_move++;
				swap(board[bb], board[bb-column]);
				bb = bb - column;
			}
			else{
				cout << "There is no space!!\n";
			}
		}

		else if(action == 'D' || action == 'd')
		{
			if (move_down == 1){
				total_move++;
				swap(board[bb], board[bb+column]);
				bb = bb + column;
			}
			else{
				cout << "There is no space!!\n";
			}
		}

		else if(action == 'I' || action == 'i')
		{
			int left=-1,right=-1,up=-1,down=-1;		//I initialize them -1 because then I can understand they are changed or not

		/*	If there is space on the left ,right ,up or down then I find the differences between the number should be in the blank space 
			and the numbers around the blank space. */
			if (move_left == 1)
			{
				left = abs(board[bb-1] - (bb+1));
			}
			if (move_right == 1)
			{
				right = abs(board[bb+1] - (bb+1));
			}
			if (move_up == 1)
			{
				up = abs(board[bb-size] - (bb+1));
			}
			if (move_down == 1)
			{
				down = abs(board[bb+size] - (bb+1));
			}

		/*	I swap the number on the side closest to the number that should be in the space	*/
			if(left>=0 && right>=0 && up>=0 && down>=0)		// Only if there is space on the left ,right ,up and down
			{
				if (left<=right && left<=up && left<=down)
				{
					cout << "Intelligent move chooses L" << endl;
					swap(board[bb], board[bb-1]);
				}
				else if (right<=left && right<=up && right<=down)
				{
					cout << "Intelligent move chooses R" << endl;
					swap(board[bb], board[bb+1]);
				}
				else if (up<=left && up<=right && up<=down)
				{
					cout << "Intelligent move chooses U" << endl;
					swap(board[bb], board[bb-size]);
				}
				else if(down<=left && down<=right && down<=up)
				{
					cout << "Intelligent move chooses D" << endl;
					swap(board[bb], board[bb+size]);
				}
			}

			else if(left>=0 && right>=0 && down>=0)		// Only if there is space on the left ,right and down
			{
				if (left<=right && left<=down)
				{
					cout << "Intelligent move chooses L" << endl;
					swap(board[bb], board[bb-1]);
				}
				else if (right<=left && right<=down)
				{
					cout << "Intelligent move chooses R" << endl;
					swap(board[bb], board[bb+1]);
				}
				else if(down<=left && down<=right)
				{
					cout << "Intelligent move chooses D" << endl;
					swap(board[bb], board[bb+size]);
				}
			}

			else if(right>=0 && up>=0 && down>=0)		// Only if there is space on the right ,up and down
			{
				if (right<=up && right<=down)
				{
					cout << "Intelligent move chooses R" << endl;
					swap(board[bb], board[bb+1]);
				}
				else if (up<=right && up<=down)
				{
					cout << "Intelligent move chooses U" << endl;
					swap(board[bb], board[bb-size]);
				}
				else if(down<=right && down<=up)
				{
					cout << "Intelligent move chooses D" << endl;
					swap(board[bb], board[bb+size]);
				}
			}

			else if(left>=0 && up>=0 && down>=0)		// Only if there is space on the left ,up and down
			{
				if (left<=up && left<=down)
				{
					cout << "Intelligent move chooses L" << endl;
					swap(board[bb], board[bb-1]);
				}
				else if (up<=left && up<=down)
				{
					cout << "Intelligent move chooses U" << endl;
					swap(board[bb], board[bb-size]);
				}
				else if(down<=left && down<=up)
				{
					cout << "Intelligent move chooses D" << endl;
					swap(board[bb], board[bb+size]);
				}
			}

			else if(left>=0 && right>=0 && up>=0)		// Only if there is space on the left ,right and up
			{
				if (left<=right && left<=up)
				{
					cout << "Intelligent move chooses L" << endl;
					swap(board[bb], board[bb-1]);
				}
				else if (right<=left && right<=up)
				{
					cout << "Intelligent move chooses R" << endl;
					swap(board[bb], board[bb+1]);
				}
				else if (up<=left && up<=right)
				{
					cout << "Intelligent move chooses U" << endl;
					
				}
			}

			else if(right>=0 && down>=0)		// Only if there is space on the right and down
			{
				if(right<=down)
				{
					cout << "Intelligent move chooses R" << endl;
					swap(board[bb], board[bb+1]);
				}
				else
				{
					cout << "Intelligent move chooses D" << endl;
					swap(board[bb], board[bb+size]);
				}
			}

			else if(left>=0 && down>=0)		// Only if there is space on the left and down
			{
				if(left<=down)
				{
					cout << "Intelligent move chooses L" << endl;
					swap(board[bb], board[bb-1]);
				}
				else
				{
					cout << "Intelligent move chooses D" << endl;
					swap(board[bb], board[bb+size]);
				}
			}

			else if(right>=0 && up>=0)		// Only if there is space on the right and up
			{
				if(right<=up)
				{
					cout << "Intelligent move chooses R" << endl;
					swap(board[bb], board[bb+1]);
				}
				else
				{
					cout << "Intelligent move chooses U" << endl;
					swap(board[bb], board[bb-size]);
				}
			}

			else if(left>=0 && up>=0)		// Only if there is space on the left and up
			{
				if(left<=up)
				{
					cout << "Intelligent move chooses L" << endl;
					swap(board[bb], board[bb-1]);
				}
				else
				{
					cout << "Intelligent move chooses U" << endl;
					swap(board[bb], board[bb-size]);
				}
			}

		}

		else if(action == 'S' || action == 's')
		{
			shuffle();
		}

		else if(action == 'Q' || action == 'q')
		{
			cout << "Exiting..." << endl << endl;
			_Exit(0);
		}


		else if(action == 'T' || action == 't')
		{
			numberOfMoves();
		}

		else if(action == 'E' || action == 'e')
		{
			writeToFile();
		}

		else if(action == 'O' || action == 'o')
		{
			readFromFile();
		}

		else
		{
			cout << "\nYou entered wrong action!!\n\n";
		}

	}

	bool BoardArray1D::isSolved()const
	{
		int zero_count = 0;
		int numb = 1;

		for(int i=0 ; i<size*size-1 ; ++i)
		{
			if(board[i] == 0)
			{
				zero_count++;
				continue;
			}
			else if(board[i] != 0)
			{
				if(board[i] == numb)
				{
					numb++;
				}
				else
				{
					if(board[i] != -10)
					{
						cout<<"NOT SOLVED\n";
						return false;
					}
				}
			}
		}
		if(board[size*size-1] == -10)
		{
			cout<<"SOLVED\n";
			return true;
		}
	}

	int BoardArray1D::operator()(int a ,int b)
	{
		return board[a*column+b];
	}

	bool operator==(const BoardArray1D & b1, const BoardArray1D & b2)
	{
		if(b1.get_size() == b2.get_size())
		{
			for (int i=0 ; i<b1.size ; ++i)
			{
				if(b1.board[i] != b2.board[i])
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	int BoardArray1D::NumberOfBoards()
	{
		AbstractBoard::NumberOfBoards();
	}

	char BoardArray1D::lastMove()
	{
		AbstractBoard::lastMove();
	}

	int BoardArray1D::numberOfMoves()
	{
		AbstractBoard::numberOfMoves();
	}

	void BoardArray1D::swap(int & a, int & b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	void BoardArray1D::shuffle()
	{
		int count = 0;			// it holds the number of random moves
		reset();

		while(count < size*size)	// It makes size*size random moves to shuffle the board
		{
			moveRandom();
			count++;
		}
		cout << "Your initial random board is:\n";
	}

	void BoardArray1D::moveRandom()
	{
		int temp = 0;
		int counter = 0;

		while(counter == 0)
		{
			temp = rand() % 4;

			if (temp==0)
			{
				if (!(bb%column == 0 || board[bb-1] == 0))
				{
					swap(board[bb], board[bb-1]);
					--bb;
					counter++;
				}
			}
			else if(temp==1)
			{
				if (!((bb+1)%column == 0 || board[bb+1] == 0))
				{
					swap(board[bb], board[bb+1]);
					++bb;
					counter++;
				}
			}
			else if(temp==2)
			{
				if ( !(bb < column || board[bb-column] == 0))
				{
					swap(board[bb], board[bb-column]);
					bb = bb - column;
					counter++;
				}
			}
			else if(temp==3)
			{
				if (!((row*column-(column+1)) < bb || board[bb+column] == 0))
				{
					swap(board[bb], board[bb+column]);
					bb = bb + column;
					counter++;
				}
			}
		}
	}

	bool BoardArray1D::validMoves()
	{
		int move_left=0, move_right=0, move_up=0, move_down=0;

		if ( !((bb%column == 0 || board[bb-1] == 0))){
			move_left = 1;
		}
		if ( !((bb+1)%column == 0 || board[bb+1] == 0)){
			move_right = 1;
		}
		if ( !(bb < column || board[bb-column] == 0)){
			move_up = 1;
		}
		if ( !((row*column-(column+1)) < bb || board[bb+column] == 0)){
			move_down = 1;
		}

		if(last_move == 'L' || last_move == 'l')
		{
			if (move_left == 1){
				return true;
			}
			else{
				return false;
			}
		}

		else if(last_move == 'R' || last_move == 'r')
		{
			if (move_right == 1){
				return true;
			}
			else{
				return false;
			}
		}

		else if(last_move == 'U' || last_move == 'u')
		{
			if (move_up == 1){
				return true;
			}
			else{
				return false;
			}
		}

		else if(last_move == 'D' || last_move == 'd')
		{
			if (move_down == 1){
				return true;
			}
			else{
				return false;
			}
		}
	}

}//eryilmazGame