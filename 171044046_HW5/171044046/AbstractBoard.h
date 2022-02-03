// AbstractBoard.h

#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H

#include <string>

using std::string;

namespace eryilmazGame
{
	class AbstractBoard
	{
	public:
		AbstractBoard();

		virtual void print()const = 0;
		virtual void readFromFile() = 0;
		virtual void writeToFile() = 0;
		virtual void reset() = 0;
		virtual void setSize(const int user_size, string argv) = 0;
		virtual void move(char action) = 0;
		virtual bool isSolved()const = 0;
		virtual int operator()(int a ,int b) = 0;
		friend bool operator==(const AbstractBoard & board, const AbstractBoard & ordered_board);
		virtual int NumberOfBoards();
		virtual char lastMove();
		virtual int numberOfMoves();

		virtual void swap(int & a, int & b) = 0;
		virtual void shuffle() = 0;
		virtual void moveRandom() = 0;
		inline int get_size()const {return size;}
		inline int numb_of_board()const {return numb_of_board_obj;}
		virtual bool validMoves() = 0;
		inline char last(){return last_move;}
	protected:
		int size;
		int row;
		int column;
		int bb;
		int bb_row;
		int bb_column;
		int total_move;
		int total_element;
		int numb_of_zeros;		// it holds the impossible positions
		char last_move;
		int numb_of_board_obj;
		string input_line;
		string line;
	};


	//Global function
	bool validMoves(AbstractBoard* arr[]);


}//eryilmazGame

#endif //ABSTRACTBOARD_H