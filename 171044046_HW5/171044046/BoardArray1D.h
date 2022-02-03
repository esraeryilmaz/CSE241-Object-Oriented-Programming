// BoardArray1D.h

#ifndef BOARDARRAY1D_H
#define BOARDARRAY1D_H

#include <string>
#include "AbstractBoard.h"

using std::string;

namespace eryilmazGame
{
	class BoardArray1D : public AbstractBoard
	{
	public:
		BoardArray1D();
		//Big Three
		BoardArray1D(const BoardArray1D& other);
		BoardArray1D & operator=(const BoardArray1D& other);
		~BoardArray1D();

		void print()const override;
		void readFromFile() override;
		void writeToFile() override;
		void reset() override;
		void setSize(const int user_size, string argv) override;
		void move(char action) override;
		bool isSolved()const override;
		int operator()(int a ,int b) override;
		friend bool operator==(const BoardArray1D & board, const BoardArray1D & ordered_board);
		int NumberOfBoards() override;
		char lastMove() override;
		int numberOfMoves() override;

		void swap(int & a, int & b);
		void shuffle()override;
		void moveRandom()override;
		bool validMoves()override;

	private:
		int *board;
		int *ordered_board;

	};


}//eryilmazGame


#endif // BOARDARRAY1D_H