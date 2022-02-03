// BoardVector.cpp

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "BoardVector.h"

using namespace std;

namespace eryilmazGame
{
	BoardVector::BoardVector() : AbstractBoard(), board(0), ordered_board(0)
	{
		//deliberately empty
	}

	void BoardVector::shuffle()
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

	void BoardVector::moveRandom()
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

	void BoardVector::print()const
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

	void BoardVector::readFromFile()
	{
		fstream file;
		file.open(input_line);		//open file
		int temp_board[80];

		if(!file.is_open())
		{
			cout << "FAILED" << endl;
		}
		else
		{
			int i=0;
			while(getline(file, line, ' '))
			{
				if (line.find("bb") == 0 || line.find("bb") == 1)
				{
					temp_board[i] = -10;
					bb = i;
					i++;
				}
				else
				{
					temp_board[i] = std::atoi(line.c_str());
					i++;
				}
				total_element++;
			}
		}

		file.close();		//close file

		fstream file2;
		file2.open(input_line);		//to find the number of row and column I've read the file again
		int row_counter=0, column_counter=0;

		if(!file2.is_open())
		{
			cout << "FAILED" << endl;
		}
		else
		{
			while(getline(file2, line))
			{
				row_counter++;
			}
		}
		column_counter = total_element/row_counter;

		row = row_counter;
		column = column_counter;

		board.resize(row, vector<int>(column,0));
		ordered_board.resize(row*column);

		int k=0;

		for(int i=0 ; i<row ; ++i)
		{
			for(int j=0 ; j<column ; ++j)
			{
				board[i][j] = temp_board[k];

				ordered_board[k] = board[i][j];
				k++;

				if(board[i][j] == -10)
				{
					bb_row = i;
					bb_column = j;
				}
			}
		}

		int counter=0;		//it holds number of "00"

		for (int i=0 ; i<column*row ; ++i)
		{
			if(ordered_board[i] == 0)
			{
				counter++;
			}
		}
		numb_of_zeros = counter;

		int total_number = row*column - counter;
		int num = 1;
		int i=0;
		while(num <= total_number)
		{
			if(ordered_board[i] != 0)
			{
				if(i == row*column-1){
					ordered_board[i] = -10;
					i++;
				}
				else{
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
		cout<<endl;
		size = row*column;

		file2.close();
		cout << "Your initial random board is:\n";
	}

	void BoardVector::writeToFile()
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

	void BoardVector::reset()
	{
		int k = 1;

		for(int i=0 ; i<row ; ++i)	// It takes the board to the final solution
		{
			board.push_back(vector<int>());

			for(int j=0 ; j<column ; ++j)
			{
				if(i==row-1 && j==column-1)
				{
					board[i].push_back(-10);
					bb_row = i;
					bb_column = j;
				}
				else
				{
					board[i].push_back(k);
					k++;
				}
			}
		}

		for(int i=0 ; i<size*size-1 ; ++i)		// It takes the ordered_board to the final solution
		{
			ordered_board.push_back(i+1);
		}

		bb = row*column-1;
		ordered_board[bb] = -10;
	}

	void BoardVector::setSize(const int user_size, string argv)
	{
		size = user_size;
		input_line = argv;
		if(argv=="NULL")
		{
			row = size;
			column = size;
		}
		numb_of_board_obj++;
	}

	void BoardVector::move(char action)
	{
		cout << "Your action(L, R, U, D, I, S, T, E ,O or Q): ";
		cout << action<<endl;
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

		else if(action == 'S' || action == 's')
		{
			cout<<"Shuffle the board\n";
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

	 	else if (action == 'O' || action == 'o')
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

	bool BoardVector::isSolved()const
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

	int BoardVector::operator()(int a ,int b)
	{
		return board[a][b];
	}

	bool operator==(const BoardVector & b1, const BoardVector & b2)
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

	int BoardVector::NumberOfBoards()
	{
		AbstractBoard::NumberOfBoards();
	}

	char BoardVector::lastMove()
	{
		AbstractBoard::lastMove();
	}

	int BoardVector::numberOfMoves()
	{
		AbstractBoard::numberOfMoves();
	}

	void BoardVector::swap(int & a, int & b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	bool BoardVector::validMoves()
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
	}

}//eryilmazGame
