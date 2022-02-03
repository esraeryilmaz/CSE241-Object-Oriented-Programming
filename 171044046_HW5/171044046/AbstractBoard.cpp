// AbstractBoard.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include "AbstractBoard.h"

using std::string;
using std::cout;
using std::endl;

namespace eryilmazGame
{
	AbstractBoard::AbstractBoard() : size(0), row(0), column(0), bb(0), bb_row(0), bb_column(0),
									total_move(0), total_element(0), numb_of_zeros(0), last_move('S'),
									numb_of_board_obj(0), input_line("NULL"), line("NULL")
	{
		//deliberately empty
	}


	int AbstractBoard::NumberOfBoards()
	{
		cout<<"Number of board objects : "<<numb_of_board_obj<<endl;
		return numb_of_board_obj;
	}

	char AbstractBoard::lastMove()
	{
		cout<<"Last move : "<<last_move<<endl;
		return last_move;
	}

	int AbstractBoard::numberOfMoves()
	{
		cout <<"Number of moves this board made : "<< total_move<<endl;
		return total_move;
	}


	//This global function controls if the last_move is valid or not valid
	bool validMoves(AbstractBoard* arr[])
	{
		for(int i=0 ; i<5 ; i++)
		{
			int x = arr[i]->validMoves();
			cout<<"For arr["<<i<<"] ,Global function returns -> " << x << endl;
		}
	}

}//eryilmazGame