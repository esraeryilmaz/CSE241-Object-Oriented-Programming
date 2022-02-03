// BoardVector.h

#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H

#include <string>
#include <vector>
#include "AbstractBoard.h"

using std::string;
using std::vector;

namespace eryilmazGame
{
	class BoardVector : public AbstractBoard
	{
	public:
		BoardVector();

		inline int get_board(int i, int j)const	{return board[i][j];}
		inline int get_ordered(int i)const	{return ordered_board[i];}

		void print()const override;
		void readFromFile() override;
		void writeToFile() override;
		void reset() override;
		void setSize(const int user_size, string argv) override;
		void move(char m) override;
		bool isSolved()const override;
		int operator()(int a ,int b) override;
		friend bool operator==(const BoardVector & board, const BoardVector & ordered_board);
		int NumberOfBoards() override;
		char lastMove() override;
		int numberOfMoves() override;

		void swap(int & a, int & b)override;
		void shuffle()override;
		void moveRandom()override;
		bool validMoves()override;

	private:
		vector <vector<int>> board;
		vector<int> ordered_board;

	};


}//eryilmazGame

#endif //BOARDVECTOR_H