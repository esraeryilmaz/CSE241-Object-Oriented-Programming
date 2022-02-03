// BoardArray2D.h

#ifndef BOARDARRAY2D_H
#define BOARDARRAY2D_H

#include <string>
#include "AbstractBoard.h"

namespace eryilmazGame
{
	class BoardArray2D : public AbstractBoard
	{
	public:
		BoardArray2D();
		//Big Threes
		BoardArray2D(const BoardArray2D& other);
		BoardArray2D & operator=(const BoardArray2D& other);
		~BoardArray2D();

		inline int get_board(int i, int j)const	{return board[i][j];}
		inline int get_ordered(int i, int j)const	{return ordered_board[i][j];}

		void print()const override;
		void readFromFile() override;
		void writeToFile() override;
		void reset() override;
		void setSize(const int user_size, string argv) override;
		void move(char action) override;
		bool isSolved()const override;
		int operator()(int a ,int b) override;
		friend bool operator==(const BoardArray2D & board, const BoardArray2D & ordered_board);
		int NumberOfBoards() override;
		char lastMove() override;
		int numberOfMoves() override;

		void swap(int & a, int & b);
		void shuffle()override;
		void moveRandom()override;
		bool validMoves()override;

	private:
		int **board;
		int **ordered_board;
	};


}//eryilmazGame


#endif // BOARDARRAY2D_H