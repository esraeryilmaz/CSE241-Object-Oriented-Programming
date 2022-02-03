// BoardArray2D.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "BoardArray2D.h"

using namespace std;

namespace eryilmazGame
{
	BoardArray2D::BoardArray2D() : AbstractBoard()
	{
		board = NULL;
		ordered_board = NULL;
	}

	BoardArray2D::BoardArray2D(const BoardArray2D& other) : AbstractBoard()
	{
		board = new int*[other.row];
		ordered_board = new int*[other.row];

		for(int i=0 ; i<row ; ++i)
		{
			board[i] = new int[other.column];
			ordered_board[i] = new int[other.column];
		}
	}

	BoardArray2D & BoardArray2D::operator=(const BoardArray2D& other)
	{
		for(int i=0 ; i<row ; i++)
		{
			delete[] board[i];	// delete the second dimension of the board
			delete[] ordered_board[i];
		}
		delete[] board;	 // delete the first
		delete[] ordered_board;

		board = new int*[other.row];
		ordered_board = new int*[other.row];
		setSize(other.size, other.input_line);

		for(int i=0 ; i<row ; ++i)
		{
			board[i] = new int[other.column];
			ordered_board[i] = new int[other.column];
		}
		for(int i=0 ; i<row ; i++)
		{
			for(int j=0 ; j<column ; j++)
			{
				board[i][j] = other.board[i][j];	 // add data to it
				ordered_board[i][j] = other.ordered_board[i][j];
			}
		}
		return *this;
	}

	BoardArray2D::~BoardArray2D()
	{
		for(int i=0 ; i<row ; i++)
		{
			delete[] board[i];	// delete the second dimension of the board
			delete[] ordered_board[i];
		}
		delete[] board;	 // delete the first
		delete[] ordered_board;
	}

	void BoardArray2D::print()const
	{
		for(int i=0 ; i<row ; ++i)
		{
			for(int j=0 ; j<column ; ++j)
			{
				if (board[i][j] == -10)		// -10 is a blank space for my implementation
				{
					cout << "\t";
				}
				else if(board[i][j] == 0)
				{
					cout << "00\t";
				}
				else if(board[i][j] == 1 || board[i][j] == 2 || board[i][j] == 3 || board[i][j] == 4 || board[i][j] == 5 || board[i][j] == 6 || board[i][j] == 7 || board[i][j] == 8 || board[i][j] == 9 )
				{
					cout << "0"<<board[i][j]<<"\t";
				}
				else
				{
					cout << board[i][j] << "\t";
				}
			}
			cout<<endl;
		}
		cout<<endl;
	}

	void BoardArray2D::readFromFile()
	{

	}

	void BoardArray2D::writeToFile()
	{
		cout << "Please enter file name for saving the current board configuration : ";
		string name;
		name = "newfile.txt";
		cout << name <<endl;
		ofstream file;		//writing mode
		file.open(name);

		for(int i=0 ; i<row ; ++i){
			for(int j=0 ; j<column ; ++j){

				if (board[i][j] == -10)
				{
					file<<"bb ";
				}
				else
				{
					if( board[i][j]==0 || board[i][j]==1 || board[i][j]==2 || board[i][j]==3 || board[i][j]==4 || board[i][j]==5 || board[i][j]==6 || board[i][j]==7 || board[i][j]==8 || board[i][j]==9 )
					{
						file<<"0"<<board[i][j]<<" ";
					}
					else
					{
						file<<board[i][j]<<" ";
					}
				}
			}
			file<<endl;
		}
		file.close();
	}

	void BoardArray2D::reset()
	{
		int k = 1;

		board = new int*[row];
		for(int i=0 ; i < row ; ++i){
			board[i] = new int[column];
		}

		ordered_board = new int*[row];
		for(int i=0 ; i < row ; ++i){
			ordered_board[i] = new int[column];
		}

		for(int i=0 ; i<row ; ++i)	// It takes the board to the final solution
		{
			for(int j=0 ; j<column ; ++j)
			{
				if(i==row-1 && j==column-1)
				{
					board[i][j] = -10;
					ordered_board[i][j] = -10;
					bb_row = i;
					bb_column = j;
				}
				else
				{
					board[i][j] = k;
					ordered_board[i][j] = k;
					k++;
				}
			}
		}

		bb = row*column-1;
	}

	void BoardArray2D::setSize(const int user_size, string argv)
	{
		size = user_size;
		input_line = argv;
		if(argv == "NULL")
		{
			row = size;
			column = size;
		}
		numb_of_board_obj++;
	}

	void BoardArray2D::move(char action)
	{
		last_move = action;
		int move_left=0, move_right=0, move_up=0, move_down=0;

		if ( !(bb%column == 0 || board[bb_row][bb_column-1] == 0)){
			move_left = 1;
		}
		if ( !((bb+1)%column == 0 || board[bb_row][bb_column+1] == 0)){
			move_right = 1;
		}
		if ( !(bb < column || board[bb_row-1][bb_column] == 0)){
			move_up = 1;
		}
		if ( !((row*column-(column+1)) < bb || board[bb_row+1][bb_column] == 0)){
			move_down = 1;
		}

		cout << "Your action(L, R, U, D, I, S, T, E, O or Q): ";
		cout << action<< endl;

		if(action == 'L' || action == 'l')
		{
			if (move_left == 1){
				swap(board[bb_row][bb_column], board[bb_row][bb_column-1]);
				--bb;
				--bb_column;
				total_move++;
			}
			else{
				cout << "There is no space!!\n";
			}
		}

		else if(action == 'R' || action == 'r')
		{
			if (move_right == 1){
				swap(board[bb_row][bb_column], board[bb_row][bb_column+1]);
				++bb;
				++bb_column;
				total_move++;
			}
			else{
				cout << "There is no space!!\n";
			}
		}

		else if(action == 'U' || action == 'u')
		{
			if (move_up == 1){
				swap(board[bb_row][bb_column], board[bb_row-1][bb_column]);
				bb = bb - column;
				--bb_row;
				total_move++;
			}
			else{
				cout << "There is no space!!\n";
			}
		}

		else if(action == 'D' || action == 'd')
		{
			if (move_down == 1){
				swap(board[bb_row][bb_column], board[bb_row+1][bb_column]);
				bb = bb + column;
				++bb_row;
				total_move++;
			}
			else{
				cout << "There is no space!!\n";
			}
		}

		else if(action == 'I' || action == 'i')
		{

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
			cout<< "Number of movement : "<< total_move << endl
				<< "The solution is not found\n\n";
		}

		else if(action == 'E' || action == 'e')
		{
			writeToFile();
		}

		else if(action == 'O' || action == 'o')
		{
	 		string name;
	 		cout << "Please enter file name for loading the current board configuration : ";
	 		name = "file2.txt";
	 		input_line = name;
	 		readFromFile();
		}

		else
		{
			cout << "\nYou entered wrong action!!\n\n";
		}


	}

	bool BoardArray2D::isSolved()const
	{
		int zero_count = 0;
		int numb = 1;

		for (int i=0 ; i<row ; ++i)
		{
			for(int j=0 ; j<column ; ++j)
			{
				if (board[i][j] == 0)
				{
					zero_count++;
					continue;
				}
				else if (board[i][j] != 0)
				{
					if (board[i][j] == numb)
					{
						numb++;
					}
					else
					{
						if (board[i][j] != -10)
						{
							cout<<"NOT SOLVED\n";
							return false;
						}
					}
				}
			}
		}
		if (board[row-1][column-1] == -10)
		{
			cout<<"SOLVED\n";
			return true;
		}
	}

	int BoardArray2D::operator()(int a ,int b)
	{
		return board[a][b];
	}

	bool operator==(const BoardArray2D & b1, const BoardArray2D & b2)
	{
		for(int i=0 ; i<b1.size ; ++i)
		{
			for(int j=0 ; j<b1.size ; ++j)
			{
				if(b1.get_board(i,j) != b2.get_board(i,j))
				{
					return false;
				}
			}
		}
		return true;
	}

	int BoardArray2D::NumberOfBoards()
	{
		AbstractBoard::NumberOfBoards();
	}

	char BoardArray2D::lastMove()
	{
		AbstractBoard::lastMove();
	}

	int BoardArray2D::numberOfMoves()
	{
		AbstractBoard::numberOfMoves();
	}

	void BoardArray2D::swap(int & a, int & b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	void BoardArray2D::shuffle()
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

	void BoardArray2D::moveRandom()
	{
		int temp = 0;
		int counter = 0;

		while(counter == 0)
		{
			temp = rand() % 4;

			if (temp==0)
			{
				if (!(bb%column == 0 || board[bb_row][bb_column-1] == 0))
				{
					swap(board[bb_row][bb_column], board[bb_row][bb_column-1]);
					--bb;
					--bb_column;
					counter++;
					last_move = 'L';
				}
			}
			else if(temp==1)
			{
				if (!((bb+1)%column == 0 || board[bb_row][bb_column+1] == 0))
				{
					swap(board[bb_row][bb_column], board[bb_row][bb_column+1]);
					++bb;
					++bb_column;
					counter++;
					last_move = 'R';
				}
			}
			else if(temp==2)
			{
				if ( !(bb < column || board[bb_row-1][bb_column] == 0))
				{
					swap(board[bb_row][bb_column], board[bb_row-1][bb_column]);
					bb = bb - column;
					--bb_row;
					counter++;
					last_move = 'U';
				}
			}
			else if(temp==3)
			{
				if (!((row*column-(column+1)) < bb || board[bb_row+1][bb_column] == 0))
				{
					swap(board[bb_row][bb_column], board[bb_row+1][bb_column]);
					bb = bb + column;
					++bb_row;
					counter++;
					last_move = 'D';
				}
			}
		}
	}

	bool BoardArray2D::validMoves()
	{
		int move_left=0, move_right=0, move_up=0, move_down=0;

		if ( !(bb%column == 0 || board[bb_row][bb_column-1] == 0)){
			move_left = 1;
		}
		if ( !((bb+1)%column == 0 || board[bb_row][bb_column+1] == 0)){
			move_right = 1;
		}
		if ( !(bb < column || board[bb_row-1][bb_column] == 0)){
			move_up = 1;
		}
		if ( !((row*column-(column+1)) < bb || board[bb_row+1][bb_column] == 0)){
			move_down = 1;
		}

		if(last_move == 'L' || last_move == 'l')
		{
			if (move_left == 1)
				return true;
			else
				return false;
		}

		else if(last_move == 'R' || last_move == 'r')
		{
			if (move_right == 1)
				return true;
			else
				return false;
		}

		else if(last_move == 'U' || last_move == 'u')
		{
			if (move_up == 1)
				return true;
			else
				return false;
		}

		else if(last_move == 'D' || last_move == 'd')
		{
			if (move_down == 1)
				return true;
			else
				return false;
		}
		return false;
	}

}//eryilmazGame