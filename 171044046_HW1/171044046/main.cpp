/*
 *	CSE241_HW1 - The N-Puzzle Problem
 *
 *	Date:	12.10.2019
 *	Author:	Esra ERYILMAZ	171044046
 */

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;


/* function declarations */
int user_input(int size);
void swap(int *a, int *b);
void shuffle(int arr[], int size);
int print_board(int arr[], int size, int space);
int inver_count(int arr[], int size);
int find_space_pos(int arr[], int size);
int is_solvable(int arr[], int size);
int is_game_finished(int arr[], int size);
int intelligent_move(int arr[], int size, int space);
int move_left(int size, int space);
int move_right(int size, int space);
int move_up(int size, int space);
int move_down(int size, int space);
int gameplay(int arr[], int size, int space);


int main()
{
	int MIN_SIZE = 3;
	int MAX_SIZE = 9;
	int size, space, total_move=0 ;

	srand(time(NULL));

	cout<< "\tThe N-Puzzle Game"<< endl;

	size = user_input(size);

	int arr[size*size-1];

	if (size < MIN_SIZE || size > MAX_SIZE)
	{
		cout<< "Invalid board size...Try again!\n\n";
	}

	else
	{
		cout << "Your initial random board is\n";
		shuffle(arr, size);

		while(is_solvable(arr,size) == 0)	//if the board is not solvable then shuffle again
		{
			shuffle(arr,size);
		}

		space = print_board(arr,size,space);

		while(is_game_finished(arr,size) == 0)		//to play until the game is over
		{
			total_move = total_move + gameplay(arr,size,space);		//it keeps the total number of moves
			space = print_board(arr, size, space);
		}

		if (is_game_finished(arr,size) == 1)
		{
			cout << "Problem solved!" << endl
				 << "Total number of moves " << total_move << endl << endl;
		}
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
	for(int i=0 ; i<size*size ; ++i)	// It takes the board to the final solution
	{
			arr[i] = i;
	}

	for(int i=size*size-1 ; i>0 ; --i)	// It makes random moves to shuffle the board
	{
		int j = rand() % (i+1);
		swap(&arr[i], &arr[j]);
	}
}


int print_board(int arr[], int size, int space)
{
	int k=0;
	for(int i=0 ; i<size ; ++i)
	{
		for(int j=0 ; j<size ; ++j)
		{
			if(arr[k] == 0)		// zero is a blank space for my implementation
			{
				cout << "\t";
				space = k;
			}
			else
			{
				cout << arr[k] << "\t";
			}
			k++;

		}
		cout << endl;
	}
	cout << endl;

	return space;
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
		if(arr[i] == 0)
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
	if(arr[size*size-1] == 0)
	{
		return 1;
	}
}

//it controls left, if there is room then it returns true
int move_left(int size, int space)
{
	if(space % size == 0)
		return 0;
	else
		return 1;
}

//it controls right, if there is room then it returns true
int move_right(int size, int space)
{
	if((space+1) % size == 0)
		return 0;
	else
		return 1;
}

//it controls up, if there is room then it returns true
int move_up(int size, int space)
{
	if(space < size)
		return 0;
	else
		return 1;
}

//it controls down, if there is room then it returns true
int move_down(int size, int space)
{
	if(space >= size*(size-1))
		return 0;
	else
		return 1;
}


int intelligent_move(int arr[], int size, int space)
{
	int left=-1,right=-1,up=-1,down=-1;		//I initialize them -1 because then I can understand they are changed or not

/*	If there is space on the left ,right ,up or down then I find the differences between the number should be in the blank space 
	and the numbers around the blank space. */
	if (move_left(size,space))
	{
		left = abs(arr[space-1] - (space+1));
	}
	if (move_right(size,space))
	{
		right = abs(arr[space+1] - (space+1));
	}
	if (move_up(size,space))
	{
		up = abs(arr[space-size] - (space+1));
	}
	if (move_down(size,space))
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


int gameplay(int arr[], int size, int space)
{
	char move;
	int count = 0;		// it holds the number of moves
	cout << "Your move: ";
	cin >> move;


	if (move == 'L' || move == 'l')
	{
		if (move_left(size, space))		//Is there any space for moving
		{
			count++;
			swap(&arr[space], &arr[space-1]);
		}
		else
		{
			cout << "There is no space!!\n";
		}
	}

	else if(move == 'R' || move == 'r')
	{
		if(move_right(size, space))
		{
			count++;
			swap(&arr[space], &arr[space+1]);
		}
		else
		{
			cout << "There is no space!!\n";
		}
	}

	else if(move == 'U' || move == 'u')
	{
		if (move_up(size, space))
		{
			count++;
			swap(&arr[space], &arr[space-size]);
		}
		else
		{
			cout << "There is no space!!\n";
		}
	}

	else if(move == 'D' || move == 'd')
	{
		if(move_down(size, space))
		{
			count++;
			swap(&arr[space], &arr[space+size]);
		}
		else
		{
			cout << "There is no space!!\n";
		}
	}

	else if(move == 'I' || move == 'i')
	{
		intelligent_move(arr,size,space);
		count++;
	}

	else if(move == 'S' || move == 's')
	{
		do{
			shuffle(arr,size);
		}while(is_solvable(arr,size) == 0);
	}

	else if(move == 'Q' || move == 'q')
	{
		cout << "Exiting..." << endl << endl;
		_Exit(0);
	}

	else
	{
		cout << "You entered wrong!!\n";
	}

	return count;
}



