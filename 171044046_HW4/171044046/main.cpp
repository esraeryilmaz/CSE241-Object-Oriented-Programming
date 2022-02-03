/*
 *	CSE241_HW4 - N-Puzzle Continued
 *
 *	Date:	11.11.2019
 *	Author:	Esra ERYILMAZ	171044046
 *
 *********************************************************************************************************************************************
 *	NOTE!!	# I CONSIDER THERE IS A SPACE AT THE END OF EACH LINE WHEN READING AND WRITING FILES	*********************************************
 *			# I sent 2 resolvable sample files: file1.txt and file2.txt		******************************************************************
 *********************************************************************************************************************************************
 */



#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

const int MIN_SIZE = 3;
const int MAX_SIZE = 9;


class NPuzzle
{
public:

	inline void print()const		{game_board.print();}
	inline void printReport()const	{game_board.printReport();}
	inline void readFromFile()		{object.resize(1);	game_board.readFromFile();}
	inline void writeToFile()		{game_board.writeToFile();}
	inline void shuffle()			{object.resize(1);	game_board.shuffle();}
	inline void reset()				{object.resize(1);	game_board.reset();}
	inline void moveRandom()		{object.resize(1);	game_board.moveRandom();}
	inline void move()				{object.resize(1);	game_board.move();}
	inline int solvePuzzle()		{game_board.solvePuzzle();}
	inline bool isSolved()const		{game_board.isSolved();}
	inline void setsize(const int user_size, const int argc,char const *argv[])		{game_board.setSize(user_size,argc,argv);}
	friend ostream& operator<<(ostream& outputStream, NPuzzle obj);
	friend istream& operator>>(istream& inputStream, NPuzzle obj);
	friend bool operator==(const NPuzzle & board, const NPuzzle & ordered_board);


private:

	class Board
	{
	public:

		void print()const;
		void printReport()const;
		void readFromFile();
		void writeToFile();
		void shuffle();
		void reset();
		void moveRandom();
		void move();
		int solvePuzzle();
		bool isSolved()const;
		void swap(int & a, int & b);
		void setSize(const int user_size, const int argc, char const *argv[]);
		inline int NumberOfBoards(){ return numb_of_board_obj;}
		inline char lastMove(){ return last_move;}
		inline int get_size()const	{return size;}
		inline int get_board(int i, int j)const	{return board[i][j];}
		inline int get_ordered(int i)const	{return ordered_board[i];}
		bool can_move();
		inline int operator()(int a, int b){return board[a][b];}

	private:

		vector <vector<int>> board;
		vector<int> ordered_board;
		int size = 0;
		int row = 0;
		int column = 0;
		int bb = 0;
		int bb_row = 0;
		int bb_column = 0;
		int arg = 0;
		int total_move = 0;
		int total_element=0;
		int numb_of_zeros=0;		// it holds the impossible positions
		char last_move;
		int numb_of_board_obj=0;
		string input_line;
		string line;
		bool move_left, move_right, move_up, move_down;
	};

	Board game_board;		//object of board
	vector <Board> object;		//vector of Board objects
};




int main(int argc, char const *argv[])
{
	int user_size;
	srand(time(NULL));

	cout<< "\tThe N-Puzzle Game"<< endl<<endl;

	if ( argc == 1)		//if user didn't type any file name on command line
	{
		NPuzzle game;	//object

		cout<<"You didn't write any textfile name on command line so;\n"
			<< "Please enter the problem size (3,4,5...9)" << endl;
		cin >> user_size;

		if(user_size >= MIN_SIZE && user_size <= MAX_SIZE)
		{
			cout << "Your initial random board is:\n";
			game.setsize(user_size, argc, NULL);
			game.shuffle();
			cout << game <<endl;		// << operator overloaded

			while(!game.isSolved())		//to play until the game is over
			{
				game.move();
				game.print();
			}

			if (game.isSolved())
			{
				game.printReport();
			}
		}
		else
		{
			cout<< "Invalid board size...Try again!\n\n";
		}
	}

	else if(argc == 2)
	{
		cout<<"You write file name on command line and your initial board is:\n";

		NPuzzle game;

		game.setsize(0, argc, argv);
		game.readFromFile();
		game.print();

		while(!game.isSolved())		//to play until the game is over
		{
			game.move();
			game.print();
		}

		if (game.isSolved())
		{
			game.printReport();
		}
	}

	else
	{
		cout << "Wrong selection!!";
	}


	return 0;
}



/*
 *	I couldn't construct the algorithm that wrote in the assignment
 */
int NPuzzle::Board::solvePuzzle()
{
	while(!isSolved())
	{
		can_move();
		if (move_left == true)
		{
			++numb_of_board_obj;
			last_move = 'L';
		}

		if (move_right == true)
		{
			++numb_of_board_obj;
			last_move = 'R';
		}

		if (move_up == true)
		{
			++numb_of_board_obj;
			last_move = 'U';
		}

		if (move_down == true)
		{
			++numb_of_board_obj;
			last_move = 'D';
		}
	}
}


void NPuzzle::Board::shuffle()
{
	int count = 0;			// it holds the number of random moves

	reset();

	while(count < size*size)	// It makes size*size random moves to shuffle the board
	{
		moveRandom();
		count++;
	}
}


void NPuzzle::Board::reset()
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

	for(int i=0 ; i<size*size-1 ; ++i)		// It takes the board to the final solution
	{
		ordered_board.push_back(i+1);
	}

	bb = row*column-1;
	ordered_board[bb] = -10;
}


void NPuzzle::Board::moveRandom()
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
			}
		}
	}
}


void NPuzzle::Board::swap(int & a, int & b)
{
	int temp = a;
	a = b;
	b = temp;
}


void NPuzzle::Board::setSize(const int user_size, const int argc, char const *argv[])
{
	size = user_size;

	if(argc == 1)
	{
		row = size;
		column = size;
		arg = argc;
	}
	else if(argc == 2)
	{
		arg = argc;
		input_line = argv[1];
	}
}


ostream& operator<<(ostream& outputStream, NPuzzle obj)
{
	for(int i=0 ; i<obj.game_board.get_size() ;i++)
	{
		for(int j=0 ; j<obj.game_board.get_size() ; j++)
		{
			if (obj.game_board.get_board(i,j) == -10)
			{
				outputStream << "\t";
			}
			else
			{
				outputStream << obj.game_board.get_board(i,j)<<"\t";
			}
		}
		cout <<endl;
	}
	return outputStream;
}


bool operator==(const NPuzzle & board, const NPuzzle & ordered_board)
{
	int k=0;
	NPuzzle obj;
	for(int i=0 ; i<obj.game_board.get_size() ; ++i)
	{
		for(int j=0 ; j<obj.game_board.get_size() ; ++j)
		{
			if (obj.game_board.get_board(i,j) != obj.game_board.get_ordered(k))
			{
				return false;
			}
			k++;
		}
	}
	return true;
}


void NPuzzle::Board::print()const
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


void NPuzzle::Board::printReport()const
{
	cout << "Problem solved!" << endl		// I call this function just solution is found ,in other case i just write  cout<<total_move;
			 << "Total number of moves " << total_move << endl << endl;
}


void NPuzzle::Board::readFromFile()
{
	fstream file;
	file.open(input_line);		//open file
	int temp_board[MAX_SIZE*MAX_SIZE-1];

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
		cout << "Failed" << endl;
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

	file2.close();
}


void NPuzzle::Board::writeToFile()
{
	cout << "Please enter file name for saving the current board configuration : ";
	string name;
	cin >> name;

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


void NPuzzle::Board::move()
{
	char action;
	
	cout << "Your action(L, R, U, D, S, V, T, E, O or Q): ";
	cin >> action;

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
		if (arg==1)
		{
			cout<<"Shuffle the board "<<endl;
			shuffle();
		}
	}

	else if(action == 'Q' || action == 'q')
	{
		cout << "Exiting..." << endl << endl;
		_Exit(0);
	}

	else if (action == 'V' || action == 'v')
	{
		//solvePuzzle();
	}

	else if(action == 'T' || action == 't')
	{
		cout<< "\nNumber of movement : "<< total_move << endl
			<< "The solution is not found\n\n";
		//if the solution is found I call printReport function
	}

	else if(action == 'E' || action == 'e')
	{
		writeToFile();
	}

 	else if (action == 'O' || action == 'o')
 	{
 		string name;
 		cout << "Please enter file name for loading the current board configuration : ";
 		cin >> name;
 		input_line = name;

 		readFromFile();
 	}

	else
	{
		cout << "\nYou entered wrong action!!\n\n";
	}
}


// this is for to control that there is a appropriate cell in that location
bool NPuzzle::Board::can_move()
{
	if ( !(bb%column == 0 || board[bb_row][bb_column-1] == 0)){
		move_left = true;
	}
	if ( !((bb+1)%column == 0 || board[bb_row][bb_column+1] == 0)){
		move_right = true;
	}
	if ( !(bb < column || board[bb_row-1][bb_column] == 0)){
		move_up = true;
	}
	if ( !((row*column-(column+1)) < bb || board[bb_row+1][bb_column] == 0)){
		move_down = true;
	}
}


bool NPuzzle::Board::isSolved()const
{
	if(arg==1)
	{
		int k=1;

		for(int i=0 ; i<row ; ++i)
		{
			for(int j=0 ; j<column ; ++j)
			{
				if(board[i][j] == k)
				{
					k++;
				}
				else if((board[i][j] == -10) && (i==row-1) && (j==column-1))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		return true;
	}

	else if(arg==2)
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
							return false;
						}
					}
				}
			}
		}

		if (board[row-1][column-1] == -10)
		{
			return true;
		}
	}
}