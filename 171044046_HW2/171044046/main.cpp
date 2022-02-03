/*
 *	CSE241_HW2 - The N-Puzzle Continued
 *
 *	Date:	22.10.2019
 *	Author:	Esra ERYILMAZ	171044046
 *
 *
 *	NOTE!!	# I CONSIDER THERE IS A SPACE AT THE END OF EACH LINE WHEN READING AND WRITING FILES
 *			# My code continues too long for the v command
 *			# I sent 2 resolvable sample files: file1.txt and file2.txt
 */

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;


/* function declarations */
int user_input(int size);
void swap(int *a, int *b);
void shuffle(int arr[], int size);
int inver_count(int arr[], int size);
int find_space_pos(int arr[], int size);
int is_solvable(int arr[], int size);
int is_game_finished(int arr[], int size);
int intelligent_move(int arr[], int size, int space);
int move_left(int board[], int column, int bb);
int move_right(int board[], int column, int bb);
int move_up(int board[], int column, int bb);
int move_down(int board[], int row, int column, int bb);
int is_game_finished2(int board[], int column, int row);
int print_board(int board[], int bb, int row, int column);
int random_move(int board[], int bb, int row, int column);
int new_intelligent(int board[], int ordered_board[], int bb, int row, int column);
int gameplay(int board[], int ordered_board[], int bb, int row, int column, int argc, int total_move);



int main(int argc, char const *argv[])
{
	const int MIN_SIZE = 3;
	const int MAX_SIZE = 9;

	auto size=0, space=0, total_move=0 ;

	srand(time(NULL));

	cout<< "\tThe N-Puzzle Game"<< endl<<endl;

	if ( argc == 1)		//if user didn't type any file name on command line
	{
		cout<<"You didn't write any textfile name on command line so;\n";
		size = user_input(size);

		int arr[size*size-1];

		if (size < MIN_SIZE || size > MAX_SIZE)
		{
			cout<< "Invalid board size...Try again!\n\n";
		}

		else
		{
			cout << "Your initial random board is:\n";
			shuffle(arr, size);

			while(is_solvable(arr,size) == 0)	//if the board is not solvable then shuffle again
			{
				shuffle(arr,size);
			}

			space = print_board(arr,space,size,size);

			while(is_game_finished(arr,size) == 0)		//to play until the game is over
			{
				total_move = total_move + gameplay(arr,arr,space,size,size,argc,total_move);		//it keeps the total number of moves
				space = print_board(arr, space,size,size);
			}

			if (is_game_finished(arr,size) == 1)
			{
				cout << "Problem solved!" << endl
					 << "Total number of moves " << total_move << endl << endl;
			}
		}
		total_move = 0;
	}

	else if(argc == 2)		//if user type file name on command line
	{
		int board[MAX_SIZE*MAX_SIZE-1], ordered_board[MAX_SIZE*MAX_SIZE-1];
		int i=0, j=0, bb=0, row=0, column=0, total_element=0;
		string line;

		fstream file;

		file.open(argv[1]);		//open file

		if(!file.is_open())
		{
			cout << "FAILED" << endl;
		}
		else
		{
			cout<<"You write file name on command line and your initial board is:\n";
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
					i++;
				}
				total_element++;
			}
		}
		file.close();		//close file


		fstream file2;
		file2.open(argv[1]);		//to find the number of row and column I've read the file again
		if(!file2.is_open())
		{
			cout << "Failed" << endl;
		}
		else
		{
			while(getline(file2, line))
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

		cout<<endl;
		print_board(board, bb ,row, column);

		while(is_game_finished2(board, column, row) == 0)
		{
			total_move = total_move + gameplay(board, ordered_board, bb, row, column,argc,total_move);
			bb = print_board(board, bb ,row, column);
		}
		if (is_game_finished2(board, column, row) == 1)
		{
			cout << "Problem solved!" << endl
				 << "Total number of moves " << total_move << endl << endl;

		}
		file2.close();
	}
	else
	{
		cout << "Wrong selection!!";
	}


	return 0;
}



int user_input(int size)
{
	cout<< "Please enter the problem size (3,4,5...9)" << endl;
	cin >> size;

	if(!(size))		// it is for to prevent from infinite loop if user enters letters
	{
		cin.clear();
		cin.ignore(1000, '\n');
	}

	return size;
}


void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void shuffle(int arr[], int size)
{
	arr[0] = -10;
	for(int i=1 ; i<size*size ; ++i)	// It takes the board to the final solution
	{
			arr[i] = i;
	}

	for(int i=size*size-1 ; i>0 ; --i)	// It makes random moves to shuffle the board
	{
		int j = rand() % (i+1);
		swap(&arr[i], &arr[j]);
	}
}

// it finds the number of inversions in the array
int inver_count(int arr[], int size)
{
	int count = 0;
	for(int i=0 ; i<size*size-1 ; ++i)
	{
		for(int j=i+1 ; j<size*size ; ++j)
		{
			if(arr[j] && arr[i] && arr[i] > arr[j])
			{
				count++;
			}
		}
	}
	return count;
}


// it finds position of blank space from bottom
int find_space_pos(int arr[], int size)
{
	for(int i=0 ; i<size*size ; ++i)
	{
		if(arr[i] == -10)
		{
			return (size - (i/size));
		}
	}
}


// This function returns true if given puzzle is solvable
int is_solvable(int arr[], int size)
{
	int n = inver_count(arr,size);

	if (size%2 != 0)	// if size of the game is odd
	{
		if (n%2 == 0){
			return 1;	//it returns true if puzzle is solvable
		}
		else{
			return 0;	//it returns false if puzzle is not solvable
		}
	}
	else		//if size of the game is even then we should consider the blank space position and inversion counts together
	{
		int space_pos = find_space_pos(arr,size);

		if(space_pos%2 == 0 && n%2 != 0)	//if space position is even and then number of inversions should be odd
		{
			return 1;
		}
		else if(space_pos%2 != 0 && n%2 == 0)	//if space position is odd then number of inversions should be even
		{
			return 1;
		}
		else		//otherwise puzzle is not solvable then it returns false
		{
			return 0;
		}
	}
}


// it checks whether the game is over
int is_game_finished(int arr[],int size)
{
	for(int i=0 ; i<size*size-1 ; ++i)
	{
		if(arr[i] != i+1)
		{
			return 0;
		}
	}
	if(arr[size*size-1] == -10)
	{
		return 1;
	}
}

//it controls left, if there is room then it returns true
int move_left(int board[], int column, int bb)
{
	if (bb%column == 0 || board[bb-1] == 0)
	{
		return 0;	//false
	}
	else
	{
		return 1;	//true
	}
}

//it controls right, if there is room then it returns true
int move_right(int board[], int column, int bb)
{
	if ((bb+1)%column == 0 || board[bb+1] == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//it controls up, if there is room then it returns true
int move_up(int board[], int column, int bb)
{
	if (bb < column || board[bb-column] == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//it controls down, if there is room then it returns true
int move_down(int board[], int row, int column, int bb)
{
	if ((row*column-(column+1)) < bb || board[bb+column] == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


int intelligent_move(int arr[], int size, int space)
{
	auto left=-1,right=-1,up=-1,down=-1;		//I initialize them -1 because then I can understand they are changed or not

//	If there is space on the left ,right ,up or down then I find the differences between the number should be in the blank space and the numbers around the blank space.
	if (move_left(arr,size,space))
	{
		left = abs(arr[space-1] - (space+1));
	}
	if (move_right(arr,size,space))
	{
		right = abs(arr[space+1] - (space+1));
	}
	if (move_up(arr,size,space))
	{
		up = abs(arr[space-size] - (space+1));
	}
	if (move_down(arr,size,size,space))
	{
		down = abs(arr[space+size] - (space+1));
	}


/*	I swap the number on the side closest to the number that should be in the space	*/
	if(left>=0 && right>=0 && up>=0 && down>=0)		// Only if there is space on the left ,right ,up and down
	{
		if (left<=right && left<=up && left<=down)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(&arr[space], &arr[space-1]);
		}
		else if (right<=left && right<=up && right<=down)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(&arr[space], &arr[space+1]);
		}
		else if (up<=left && up<=right && up<=down)
		{
			cout << "Intelligent move chooses U" << endl;
			swap(&arr[space], &arr[space-size]);
		}
		else if(down<=left && down<=right && down<=up)
		{
			cout << "Intelligent move chooses D" << endl;
			swap(&arr[space], &arr[space+size]);
		}
	}

	else if(left>=0 && right>=0 && down>=0)		// Only if there is space on the left ,right and down
	{
		if (left<=right && left<=down)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(&arr[space], &arr[space-1]);
		}
		else if (right<=left && right<=down)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(&arr[space], &arr[space+1]);
		}
		else if(down<=left && down<=right)
		{
			cout << "Intelligent move chooses D" << endl;
			swap(&arr[space], &arr[space+size]);
		}
	}

	else if(right>=0 && up>=0 && down>=0)		// Only if there is space on the right ,up and down
	{
		if (right<=up && right<=down)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(&arr[space], &arr[space+1]);
		}
		else if (up<=right && up<=down)
		{
			cout << "Intelligent move chooses U" << endl;
			swap(&arr[space], &arr[space-size]);
		}
		else if(down<=right && down<=up)
		{
			cout << "Intelligent move chooses D" << endl;
			swap(&arr[space], &arr[space+size]);
		}
	}

	else if(left>=0 && up>=0 && down>=0)		// Only if there is space on the left ,up and down
	{
		if (left<=up && left<=down)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(&arr[space], &arr[space-1]);
		}
		else if (up<=left && up<=down)
		{
			cout << "Intelligent move chooses U" << endl;
			swap(&arr[space], &arr[space-size]);
		}
		else if(down<=left && down<=up)
		{
			cout << "Intelligent move chooses D" << endl;
			swap(&arr[space], &arr[space+size]);
		}
	}

	else if(left>=0 && right>=0 && up>=0)		// Only if there is space on the left ,right and up
	{
		if (left<=right && left<=up)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(&arr[space], &arr[space-1]);
		}
		else if (right<=left && right<=up)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(&arr[space], &arr[space+1]);
		}
		else if (up<=left && up<=right)
		{
			cout << "Intelligent move chooses U" << endl;
			swap(&arr[space], &arr[space-size]);
		}
	}

	else if(right>=0 && down>=0)		// Only if there is space on the right and down
	{
		if(right<=down)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(&arr[space], &arr[space+1]);
		}
		else
		{
			cout << "Intelligent move chooses D" << endl;
			swap(&arr[space], &arr[space+size]);
		}
	}

	else if(left>=0 && down>=0)		// Only if there is space on the left and down
	{
		if(left<=down)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(&arr[space], &arr[space-1]);
		}
		else
		{
			cout << "Intelligent move chooses D" << endl;
			swap(&arr[space], &arr[space+size]);
		}
	}

	else if(right>=0 && up>=0)		// Only if there is space on the right and up
	{
		if(right<=up)
		{
			cout << "Intelligent move chooses R" << endl;
			swap(&arr[space], &arr[space+1]);
		}
		else
		{
			cout << "Intelligent move chooses U" << endl;
			swap(&arr[space], &arr[space-size]);
		}
	}

	else if(left>=0 && up>=0)		// Only if there is space on the left and up
	{
		if(left<=up)
		{
			cout << "Intelligent move chooses L" << endl;
			swap(&arr[space], &arr[space-1]);
		}
		else
		{
			cout << "Intelligent move chooses U" << endl;
			swap(&arr[space], &arr[space-size]);
		}
	}
}


int print_board(int board[], int bb, int row, int column)
{
	int k=0;
	for(int i=0 ; i<row ; ++i)
	{
		for(int j=0 ; j<column ; ++j)
		{
			if (board[k] == -10)		// -10 is a blank space for my implementation
			{
				cout << "bb\t";
				bb = k;
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

	return bb;
}


int is_game_finished2(int board[], int column, int row)
{
	int zero_count = 0;		//it counts the number of "00" impossible positions
	int i;
	for(i=0 ; i<column*row-1 ; ++i)
	{
		if(board[i] == 0)
		{
			zero_count++;
		}
		else if(board[i] != i-zero_count+1)
		{
			return 0;
		}
	}
	if(board[i] == -10)
	{
		return 1;
	}
}


int random_move(int board[], int bb, int row, int column)
{
	int random_num = 0, counter = 0;

	random_num = rand() % 4;

	if (random_num == 0)
	{
		if(move_left(board,column,bb))
		{
			cout << "Random move chooses L\n";
			swap(&board[bb], &board[bb-1]);
			counter++;
			return 1;
		}
	}
	if (random_num == 1)
	{
		if(move_right(board,column,bb))
		{
			cout << "Random move chooses R\n";
			swap(&board[bb], &board[bb+1]);
			counter++;
			return 1;
		}
	}
	if (random_num == 2)
	{
		if(move_up(board,column,bb))
		{
			cout << "Random move chooses U\n";
			swap(&board[bb], &board[bb-column]);
			counter++;
			return 1;
		}
	}
	if (random_num == 3)
	{
		if(move_down(board,row,column,bb))
		{
			cout << "Random move chooses D\n";
			swap(&board[bb], &board[bb+column]);
			counter++;
			return 1;
		}
	}
	return 0;
}


int new_intelligent(int board[], int ordered_board[], int bb, int row, int column)
{
	int a = 0;

	if(move_left(board,column,bb))
	{
		if (board[bb-1] == ordered_board[bb])
		{
			cout << "Intelligent move chooses L" << endl;
			swap(&board[bb], &board[bb-1]);
			a++;
			return 1;
		}
	}
	if(move_right(board,column,bb))
	{
		if (board[bb+1] == ordered_board[bb])
		{
			cout << "Intelligent move chooses R" << endl;
			swap(&board[bb], &board[bb+1]);
			a++;
			return 1;
		}
	}
	if(move_up(board,column,bb))
	{
		if (board[bb-column] == ordered_board[bb])
		{
			cout << "Intelligent move chooses U" << endl;
			swap(&board[bb], &board[bb-column]);
			a++;
			return 1;
		}
	}
	if(move_down(board,row,column,bb))
	{
		if (board[bb+column] == ordered_board[bb])
		{
			cout << "Intelligent move chooses D" << endl;
			swap(&board[bb], &board[bb+column]);
			a++;
			return 1;
		}
	}
	if(a==0)		//if intelligent move doesn't work than call random move function
	{
		int b = random_move(board, bb, row, column);
		while(b == 0)
		{
			b = random_move(board, bb, row, column);
		}
	}
}


int gameplay(int board[], int ordered_board[], int bb, int row, int column, int argc, int total_move)
{
	char action;
	int count = 0;		// it holds the number of moves
	cout << "Your action(L, R, U, D, I, S, V, T, E, Y or Q): ";
	cin >> action;

	if(action == 'L' || action == 'l')
	{
		if (move_left(board,column,bb)){
			count++;
			swap(&board[bb], &board[bb-1]);
		}
		else{
			cout << "There is no space!!\n";
		}
	}

	else if(action == 'R' || action == 'r')
	{
		if (move_right(board,column,bb)){
			count++;
			swap(&board[bb], &board[bb+1]);
		}
		else{
			cout << "There is no space!!\n";
		}
	}

	else if(action == 'U' || action == 'u')
	{
		if (move_up(board,column,bb)){
			count++;
			swap(&board[bb], &board[bb-column]);
		}
		else{
			cout << "There is no space!!\n";
		}
	}

	else if(action == 'D' || action == 'd')
	{
		if (move_down(board,row,column,bb)){
			count++;
			swap(&board[bb], &board[bb+column]);
		}
		else{
			cout << "There is no space!!\n";
		}
	}

	else if(action == 'I' || action == 'i')
	{
		if (argc==1)
		{
			intelligent_move(board,column,bb);
			count++;
		}
		if (argc==2)
		{
			if(new_intelligent(board, ordered_board, bb ,row,column))
			{
				count++;
			}
		}
	}

	else if(action == 'S' || action == 's')
	{
		if (argc==1)
		{
			do{
				shuffle(board,column);
			}while(is_solvable(board,column) == 0);
		}
	}

	else if(action == 'Q' || action == 'q')
	{
		cout << "Exiting..." << endl << endl;
		_Exit(0);
	}

	else if (action == 'V' || action == 'v')
	{
		while(is_game_finished2(board, column, row) == 0)
		{
			bb = new_intelligent(board, ordered_board, bb, row, column);
			bb = print_board(board,bb,row,column);
			count++;
		}
	}

	else if(action == 'T' || action == 't')
	{
		cout<< "\nNumber of movement : "<< total_move << endl
			<< "The solution is not found\n\n";
	}

	else if(action == 'E' || action == 'e')
	{
		cout << "Please enter file name for saving the current board configuration : ";
		string name;
		cin >> name;
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

	else if(action == 'Y' || action == 'y')
	{
		cout << "Please enter file name for loading the current board configuration : ";
		string name, line;
		auto i=0, total_move=0, total_element=0, row=0 ,column=0 ,counter=0;
		cin >> name;

		ifstream file;		//reading mode
		file.open(name);

		if(!file.is_open())
		{
			cout << "FAILED" << endl;
			_Exit(0);
		}
		else
		{
			while(getline(file, line, ' '))
			{
				if (line.find("bb") == 0 || line.find("bb") == 1)	//line.find("bb") == 1,,,   (line.compare(" bb")) == 0 ... line =="bb"
				{
					board[i] = -10;
					bb = i;
					i++;
				}
				else
				{
					board[i] = std::atoi(line.c_str());
					i++;
				}
				total_element++;
			}
		}
		file.close();

		fstream file2;
		file2.open(name);
		if(!file2.is_open())
		{
			cout << "Failed" << endl;
		}
		else
		{
			while(getline(file2, line)){
				row++;
			}
		}
		column = total_element/row;

		for(int k=0 ; k<row*column ; ++k)
		{
			ordered_board[k] = board[k];
		}

		for (int i=0 ; i<column*row ; ++i)
		{
			if(ordered_board[i] == 0)
			{
				counter++;		//it holds number of "00"
			}
		}

		int total_number = row*column - counter-1;
		int num = 1;
		i=0;
		while(num <= total_number)
		{
			if(ordered_board[i] != 0)
			{
				ordered_board[i] = num;
				num++;
				i++;
			}
			else
			{
				i++;
			}
		}

		cout<<endl<<endl;
		print_board(board, bb ,row, column);

		while(is_game_finished2(board, column, row) == 0)
		{
			total_move = total_move + gameplay(board, ordered_board, bb, row, column,argc,total_move);
			bb = print_board(board, bb ,row, column);
		}

		if (is_game_finished2(board, column, row) == 1)
		{
			cout << "Problem solved!" << endl
				 << "Total number of moves " << total_move << endl << endl;

		}
		file2.close();
	}

	else
	{
		cout << "\nYou entered wrong action!!\n\n";
	}

	return count;
}
