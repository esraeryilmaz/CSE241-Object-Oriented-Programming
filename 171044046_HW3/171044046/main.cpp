/*
 *	CSE241_HW3 - The N-Puzzle Using OOP
 *
 *	Date:	03.11.2019
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

using namespace std;

const int MIN_SIZE = 3;
const int MAX_SIZE = 9;


class NPuzzle
{
public:

	inline void print()const		{game_board.print();}
	inline void printReport()const	{game_board.printReport();}
	inline void readFromFile()		{game_board.readFromFile();}
	inline void writeToFile()		{game_board.writeToFile();}
	inline void shuffle()			{game_board.shuffle();}
	inline void reset()				{game_board.reset();}
	inline void moveRandom()		{game_board.moveRandom();}
	inline void moveIntelligent()	{game_board.moveIntelligent();}
	inline int move()				{game_board.move();}
	inline int solvePuzzle()		{game_board.solvePuzzle();}
	inline bool isSolved()const		{game_board.isSolved();}
	inline void setsize(const int user_size, const int argc,char const *argv[])		{game_board.setSize(user_size,argc,argv);}


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
		void moveIntelligent();
		int move();
		int solvePuzzle();
		bool isSolved()const;
		void swap(int & a, int & b);
		void setSize(const int user_size, const int argc, char const *argv[]);

	private:

		int array[MAX_SIZE][MAX_SIZE];			//private C type 2D board array
		int ordered_board[MAX_SIZE*MAX_SIZE];
		int size=0;
		int row=0;
		int column=0;
		int bb=0;
		int bb_row=0;
		int bb_column=0;
		int total_move=0;			// it holds the number of moves
		int total_element=0;
		int numb_of_zeros=0;		// it holds the impossible positions
		int arg=0;				// for command line option
		string input_line;
		string line;
	};

	Board game_board;		//object of board
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

			while(!game.isSolved())		//to play until the game is over
			{
				int a = game.move();
				
				if(a == 11)
				{
					while(!game.isSolved())		//to play until the game is over
					{
						game.solvePuzzle();		//this is for V command
						game.print();
					}
				}
				if(a != 11)
				{
					game.print();
				}
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
			int a = game.move();

			if(a == 11)
			{
				while(!game.isSolved())		//to play until the game is over
				{
					game.solvePuzzle();		//this is for V command
					game.print();
				}
			}
			if(a != 11)
			{
				game.print();
			}
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


void NPuzzle::Board::readFromFile()
{
	int temp_board[MAX_SIZE*MAX_SIZE-1];

	fstream file;
	file.open(input_line);		//open file

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


	int k=0;

	for(int i=0 ; i<row ; ++i)
	{
		for(int j=0 ; j<column ; ++j)
		{
			array[i][j] = temp_board[k];

			ordered_board[k] = array[i][j];
			k++;

			if(array[i][j] == -10)
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

			if (array[i][j] == -10)
			{
				file<<"bb ";
			}
			else
			{
				if( array[i][j]==0 || array[i][j]==1 || array[i][j]==2 || array[i][j]==3 || array[i][j]==4 || array[i][j]==5 || array[i][j]==6 || array[i][j]==7 || array[i][j]==8 || array[i][j]==9 )
				{
					file<<"0"<<array[i][j]<<" ";
				}
				else
				{
					file<<array[i][j]<<" ";
				}
			}
		}
		file<<endl;
	}
	file.close();
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
				if(array[i][j] == k)
				{
					k++;
				}
				else if((array[i][j] == -10) && (i==row-1) && (j==column-1))
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
				if (array[i][j] == 0)
				{
					zero_count++;
					continue;
				}
				else if (array[i][j] != 0)
				{
					if (array[i][j] == numb)
					{
						numb++;
					}
					else
					{
						if (array[i][j] != -10)
						{
							return false;
						}
					}
				}
			}
		}

		if (array[row-1][column-1] == -10)
		{
			return true;
		}
	}
}



void NPuzzle::Board::print()const
{
	for(int i=0 ; i<row ; ++i)
	{
		for(int j=0 ; j<column ; ++j)
		{
			if (array[i][j] == -10)		// -10 is a blank space for my implementation
			{
				cout << "bb\t";
			}
			else if(array[i][j] == 0)
			{
				cout << "00\t";
			}
			else if(array[i][j] == 1 || array[i][j] == 2 || array[i][j] == 3 || array[i][j] == 4 || array[i][j] == 5 || array[i][j] == 6 || array[i][j] == 7 || array[i][j] == 8 || array[i][j] == 9 )
			{
				cout << "0"<<array[i][j]<<"\t";
			}
			else
			{
				cout << array[i][j] << "\t";
			}
		}
		cout<<endl;
	}
	cout<<endl;
}



void NPuzzle::Board::setSize(const int user_size, const int argc, char const *argv[])
{
	size = user_size;

	if (argc == 1)
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



void NPuzzle::Board::printReport()const
{
	cout << "Problem solved!" << endl		// I call this function just solution is found ,in other case i just write  cout<<total_move;
		 << "Total number of moves " << total_move << endl << endl;
}



void NPuzzle::Board::reset()
{
	int k = 1;

	for(int i=0 ; i<row ; ++i)	// It takes the board to the final solution
	{
		for(int j=0 ; j<column ; ++j)
		{
			if(i==row-1 && j==column-1)
			{
				array[i][j] = -10;
				bb_row = i;
				bb_column = j;
			}
			else
			{
				array[i][j] = k;
				k++;
			}
		}
	}

	for(int i=0 ; i<size*size-1 ; ++i)	// It takes the board to the final solution
	{
		ordered_board[i] = i+1;
	}

	bb = row*column-1;
	ordered_board[bb] = -10;
}



void NPuzzle::Board::swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}



void NPuzzle::Board::shuffle()
{
	int count=0;		// it holds the number of random moves

	reset();

	while(count < size*size)	// It makes size*size random moves to shuffle the board
	{
		moveRandom();
		count++;
	}

	print();
}


void NPuzzle::Board::moveRandom()
{
	int temp=0;

	temp = rand() % 4;

	if (temp==0)
	{
		if (!(bb%column == 0 || array[bb_row][bb_column-1] == 0))
		{
			swap(array[bb_row][bb_column], array[bb_row][bb_column-1]);
			--bb;
			--bb_column;
		}
	}
	else if(temp==1)
	{
		if (!((bb+1)%column == 0 || array[bb_row][bb_column+1] == 0))
		{
			swap(array[bb_row][bb_column], array[bb_row][bb_column+1]);
			++bb;
			++bb_column;
		}
	}
	else if(temp==2)
	{
		if ( !(bb < column || array[bb_row-1][bb_column] == 0))
		{
			swap(array[bb_row][bb_column], array[bb_row-1][bb_column]);
			bb = bb - column;
			--bb_row;
		}
	}
	else if(temp==3)
	{
		if (!((row*column-(column+1)) < bb || array[bb_row+1][bb_column] == 0))
		{
			swap(array[bb_row][bb_column], array[bb_row+1][bb_column]);
			bb = bb + column;
			++bb_row;
		}
	}
}



int NPuzzle::Board::move()
{
	char action;
	
	cout << "Your action(L, R, U, D, I, S, V, T, E, O or Q): ";
	cin >> action;

	int move_left=0, move_right=0, move_up=0, move_down=0;

	if ( !(bb%column == 0 || array[bb_row][bb_column-1] == 0)){
		move_left = 1;
	}
	if ( !((bb+1)%column == 0 || array[bb_row][bb_column+1] == 0)){
		move_right = 1;
	}
	if ( !(bb < column || array[bb_row-1][bb_column] == 0)){
		move_up = 1;
	}
	if ( !((row*column-(column+1)) < bb || array[bb_row+1][bb_column] == 0)){
		move_down = 1;
	}

	if(action == 'L' || action == 'l')
	{
		if (move_left == 1){
			swap(array[bb_row][bb_column], array[bb_row][bb_column-1]);
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
			swap(array[bb_row][bb_column], array[bb_row][bb_column+1]);
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
			swap(array[bb_row][bb_column], array[bb_row-1][bb_column]);
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
			swap(array[bb_row][bb_column], array[bb_row+1][bb_column]);
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
		moveIntelligent();
		total_move++;
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
	// I call solvePuzzle function in the main function 
		return 11;
	}

	else if(action == 'T' || action == 't')
	{
		cout<< "\nNumber of movement : "<< total_move << endl
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
 		cin >> name;
 		input_line = name;

 		readFromFile();
 	}

	else
	{
		cout << "\nYou entered wrong action!!\n\n";
	}
}




int NPuzzle::Board::solvePuzzle()
{
	int counter=0;

	auto left=-1,right=-1,up=-1,down=-1;		//I initialize them -1 because then I can understand they are changed or not

//	If there is space on the left ,right ,up or down then I find the differences between the number should be in the blank space and the numbers around the blank space.
	if (!(bb%column == 0 || array[bb_row][bb_column-1] == 0)){
		left = abs(array[bb_row][bb_column-1] - (bb+1));
	}
	if (!((bb+1)%column == 0 || array[bb_row][bb_column+1] == 0)){
		right = abs(array[bb_row][bb_column+1] - (bb+1));
	}
	if (!(bb < column || array[bb_row-1][bb_column] == 0)){
		up = abs(array[bb_row-1][bb_column] - (bb+1));
	}
	if (!((row*column-(column+1)) < bb || array[bb_row+1][bb_column] == 0)){
		down = abs(array[bb_row+1][bb_column] - (bb+1));
	}


	if(left == 0)
	{
		cout << "New intelligent move chooses L" << endl;
		swap(array[bb_row][bb_column], array[bb_row][bb_column-1]);
		--bb;
		--bb_column;
		++counter;
		++total_move;
	}
	else if(right == 0)
	{
		cout << "New intelligent move chooses R" << endl;
		swap(array[bb_row][bb_column], array[bb_row][bb_column+1]);
		++bb;
		++bb_column;
		++counter;
		++total_move;
	}
	else if(up == 0)
	{
		cout << "New intelligent move chooses U" << endl;
		swap(array[bb_row][bb_column], array[bb_row-1][bb_column]);
		bb = bb - column;
		--bb_row;
		++counter;
		++total_move;
	}
	else if(down == 0)
	{
		cout << "New intelligent move chooses D" << endl;
		swap(array[bb_row][bb_column], array[bb_row+1][bb_column]);
		bb = bb + column;
		++bb_row;
		++counter;
		++total_move;
	}


	if(counter==0)		//if intelligent move doesn't work than call random move function
	{
		cout << "Random movement "<< endl;
		moveRandom();
		++total_move;
	}
}



void NPuzzle::Board::moveIntelligent()
{
	auto left=-1,right=-1,up=-1,down=-1;		//I initialize them -1 because then I can understand they are changed or not

//	If there is space on the left ,right ,up or down then I find the differences between the number should be in the blank space and the numbers around the blank space.
	if (!(bb%column == 0 || array[bb_row][bb_column-1] == 0)){
		left = abs(array[bb_row][bb_column-1] - (bb+1));
	}
	if (!((bb+1)%column == 0 || array[bb_row][bb_column+1] == 0)){
		right = abs(array[bb_row][bb_column+1] - (bb+1));
	}
	if (!(bb < column || array[bb_row-1][bb_column] == 0)){
		up = abs(array[bb_row-1][bb_column] - (bb+1));
	}
	if (!((row*column-(column+1)) < bb || array[bb_row+1][bb_column] == 0)){
		down = abs(array[bb_row+1][bb_column] - (bb+1));
	}


/*	I swap the number on the side closest to the number that should be in the space	*/
	if(left>=0 && right>=0 && up>=0 && down>=0)		// Only if there is space on the left ,right ,up and down
	{
		if (left<=right && left<=up && left<=down)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column-1]);
			--bb;
			--bb_column;
		}
		else if (right<=left && right<=up && right<=down)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column+1]);
			++bb;
			++bb_column;
		}
		else if (up<=left && up<=right && up<=down)
		{
			cout << "Intelligent move chooses U" << endl;
			swap(array[bb_row][bb_column], array[bb_row-1][bb_column]);
			bb = bb - column;
			--bb_row;
		}
		else if(down<=left && down<=right && down<=up)
		{
			cout << "Intelligent move chooses D" << endl;
			swap(array[bb_row][bb_column], array[bb_row+1][bb_column]);
			bb = bb + column;
			++bb_row;
		}
	}

	else if(left>=0 && right>=0 && down>=0)		// Only if there is space on the left ,right and down
	{
		if (left<=right && left<=down)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column-1]);
			--bb;
			--bb_column;
		}
		else if (right<=left && right<=down)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column+1]);
			++bb;
			++bb_column;
		}
		else if(down<=left && down<=right)
		{
			cout << "Intelligent move chooses D" << endl;
			swap(array[bb_row][bb_column], array[bb_row+1][bb_column]);
			bb = bb + column;
			++bb_row;
		}
	}

	else if(right>=0 && up>=0 && down>=0)		// Only if there is space on the right ,up and down
	{
		if (right<=up && right<=down)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column+1]);
			++bb;
			++bb_column;
		}
		else if (up<=right && up<=down)
		{
			cout << "Intelligent move chooses U" << endl;
			swap(array[bb_row][bb_column], array[bb_row-1][bb_column]);
			bb = bb - column;
			--bb_row;
		}
		else if(down<=right && down<=up)
		{
			cout << "Intelligent move chooses D" << endl;
			swap(array[bb_row][bb_column], array[bb_row+1][bb_column]);
			bb = bb + column;
			++bb_row;
		}
	}

	else if(left>=0 && up>=0 && down>=0)		// Only if there is space on the left ,up and down
	{
		if (left<=up && left<=down)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column-1]);
			--bb;
			--bb_column;
		}
		else if (up<=left && up<=down)
		{
			cout << "Intelligent move chooses U" << endl;
			swap(array[bb_row][bb_column], array[bb_row-1][bb_column]);
			bb = bb - column;
			--bb_row;
		}
		else if(down<=left && down<=up)
		{
			cout << "Intelligent move chooses D" << endl;
			swap(array[bb_row][bb_column], array[bb_row+1][bb_column]);
			bb = bb + column;
			++bb_row;
		}
	}

	else if(left>=0 && right>=0 && up>=0)		// Only if there is space on the left ,right and up
	{
		if (left<=right && left<=up)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column-1]);
			--bb;
			--bb_column;
		}
		else if (right<=left && right<=up)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column+1]);
			++bb;
			++bb_column;
		}
		else if (up<=left && up<=right)
		{
			cout << "Intelligent move chooses U" << endl;
			swap(array[bb_row][bb_column], array[bb_row-1][bb_column]);
			bb = bb - column;
			--bb_row;
		}
	}

	else if(right>=0 && down>=0)		// Only if there is space on the right and down
	{
		if(right<=down)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column+1]);
			++bb;
			++bb_column;
		}
		else
		{
			cout << "Intelligent move chooses D" << endl;
			swap(array[bb_row][bb_column], array[bb_row+1][bb_column]);
			bb = bb + column;
			++bb_row;
		}
	}

	else if(left>=0 && down>=0)		// Only if there is space on the left and down
	{
		if(left<=down)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column-1]);
			--bb;
			--bb_column;
		}
		else
		{
			cout << "Intelligent move chooses D" << endl;
			swap(array[bb_row][bb_column], array[bb_row+1][bb_column]);
			bb = bb + column;
			++bb_row;
		}
	}

	else if(right>=0 && up>=0)		// Only if there is space on the right and up
	{
		if(right<=up)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column+1]);
			++bb;
			++bb_column;
		}
		else
		{
			cout << "Intelligent move chooses U" << endl;
			swap(array[bb_row][bb_column], array[bb_row-1][bb_column]);
			bb = bb - column;
			--bb_row;
		}
	}

	else if(left>=0 && up>=0)		// Only if there is space on the left and up
	{
		if(left<=up)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(array[bb_row][bb_column], array[bb_row][bb_column-1]);
			--bb;
			--bb_column;
		}
		else
		{
			cout << "Intelligent move chooses U" << endl;
			swap(array[bb_row][bb_column], array[bb_row-1][bb_column]);
			bb = bb - column;
			--bb_row;
		}
	}
}
