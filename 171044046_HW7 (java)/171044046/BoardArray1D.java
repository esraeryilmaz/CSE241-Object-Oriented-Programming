/**
 * BoardArray1D class
 *
 * @author Esra Eryılmaz
 * @version 1.0
 * @since 2020-01-15
 */

import java.util.*;
import java.lang.*;
import java.io.*;


public class BoardArray1D extends AbstractBoard
{
	private int[] board;
	private int[] ordered_board;


	public BoardArray1D()
	{
		super();
		board = null;
		ordered_board = null;
	}


	/**
	 *produces the board as string
	 *@return board as string
	 */
	@Override
	public String toString()	//I implement toString method to print the board
	{
		int k=0;
		for(int i=0 ; i<row ; ++i)
		{
			for(int j=0 ; j<column ; ++j)
			{
				if (board[k] == -10)		// -10 is a blank space for my implementation
				{
					System.out.printf("\t");
				}
				else if(board[k] == 0)
				{
					System.out.printf("00\t");
				}
				else if(board[k] == 1 || board[k] == 2 || board[k] == 3 || board[k] == 4 || board[k] == 5 || board[k] == 6 || board[k] == 7 || board[k] == 8 || board[k] == 9 )
				{
					System.out.printf("0%d\t",board[k]);
				}
				else
				{
					System.out.printf("%d\t",board[k]);
				}
				k++;
			}
			System.out.printf("\n");
		}
		return String.format("\n");
	}

	/**
	 *reads the board from the file
	 *@exception Exception
	 */
	@Override
	public void readFromFile() throws Exception
	{
		int[] tempBoard = new int[100];

		File file1 = new File(input_line);

		Scanner sc1 = new Scanner(file1);
		Scanner sc2 = new Scanner(file1);
		Scanner sc3 = new Scanner(file1);

		int i=0;
		numb_of_zeros=0;
		while(sc1.hasNext())
		{
			String find_bb = sc1.next();
			if(find_bb.equals("bb"))
			{
				bb = i;
				break;
			}
			i++;
		}
		sc1.close();

		i=0;
		while(sc2.hasNext())
		{
			if(i == bb)
			{
				tempBoard[i] = -10;
				sc2.next();
			}
			else
			{
				tempBoard[i] = Integer.parseInt(sc2.next());
				if(tempBoard[i] == 0)
				{
					numb_of_zeros++;
				}
			}
			i++;
		}
		total_element = i;
		sc2.close();

		i=0;
		row=0;
		while(sc3.hasNextLine())
		{
			sc3.nextLine();
			row++;
		}

		size = total_element;

		board = new int[size];
		ordered_board = new int[size];

		for(i=0 ; i<total_element ; i++)
		{
			board[i] = tempBoard[i];
			ordered_board[i] = tempBoard[i];
		}

		column = total_element/row;

		int total_number = total_element - numb_of_zeros;
		int num = 1;
		i=0;

		while(num < total_number)
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
		sc3.close();
	}


	/**
	 *writes the board to the file
	 *@exception IOException
	 */
	@Override
	public void writeToFile() throws IOException
	{
		System.out.printf("Please enter file name for saving the current board configuration : \n");
		String name = "newfile1.txt";
		int k=0;
		String s;
		String n = "\n";
		try
		{
			Writer wr = new FileWriter(name);

			for(int i=0 ; i<row ; ++i){
				for(int j=0 ; j<column ; ++j){
					if (board[k] == -10)
					{
						wr.write("bb ");
						k++;
					}
					else
					{
						s = String.valueOf(board[k]);
						wr.write(s);
						wr.write(" ");
						k++;
					}
				}
				wr.write(n);
			}

			wr.close();
		}
		catch(IOException e)
		{
			System.out.printf("exception catch\n");
		}
	}

	/**
	 *resets the board to the solution
	 */
	@Override
	public void reset()
	{
		for(int i=0 ; i<size*size-1 ; ++i)
		{
			board[i] = i+1;
		}

		bb = row*column-1;
		board[bb] = -10;
	}


	/**
	 *sets the board size to given values
	 *@param user_size given user size
	 *@param argv given file name
	 */
	@Override
	public void setSize(int user_size, String argv)
	{
		size = user_size;
		input_line = argv;

		if(argv == "NULL")
		{
			row = size;
			column = size;
			board = new int[size*size-1];
			ordered_board = new int[size*size-1];
		}
		numb_of_board_obj++;
	}


	/**
	 *makes a move according to the given char parameter
	 *@param action given character
	 */
	@Override
	public void move(char action)
	{
		int temp;
		last_move = action;
		int move_left=0, move_right=0, move_up=0, move_down=0;

		if ( !((bb%column == 0 || board[bb-1] == 0))){
			move_left = 1;
		}
		if ( !((bb+1)%column == 0 || board[bb+1] == 0)){
			move_right = 1;
		}
		if ( !(bb < column || board[bb-column] == 0)){
			move_up = 1;
		}
		if ( !((row*column-(column+1)) < bb || board[bb+column] == 0)){
			move_down = 1;
		}
		System.out.printf("Your action(L, R, U, D, T, E, O or Q): %c\n",action);

		if(action == 'L' || action == 'l')
		{
			if (move_left == 1){
				total_move++;
				temp = board[bb];
				board[bb] = board[bb-1];
				board[bb-1] = temp;
				--bb;
			}
			else{
				System.out.printf("There is no space!!\n");
			}
		}

		else if(action == 'R' || action == 'r')
		{
			if (move_right == 1){
				total_move++;
				temp = board[bb];
				board[bb] = board[bb+1];
				board[bb+1] = temp;
				++bb;
			}
			else{
				System.out.printf("There is no space!!\n");
			}
		}

		else if(action == 'U' || action == 'u')
		{
			if (move_up == 1){
				total_move++;
				temp = board[bb];
				board[bb] = board[bb-column];
				board[bb-column] = temp;
				bb = bb - column;
			}
			else{
				System.out.printf("There is no space!!\n");
			}
		}

		else if(action == 'D' || action == 'd')
		{
			if (move_down == 1){
				total_move++;
				temp = board[bb];
				board[bb] = board[bb+column];
				board[bb+column] = temp;
				bb = bb + column;
			}
			else{
				System.out.printf("There is no space!!\n");
			}
		}

		else if(action == 'Q' || action == 'q')
		{
			System.out.printf("Exiting...\n\n");
			System.exit(0);
		}


		else if(action == 'T' || action == 't')
		{
			numberOfMoves();
		}

		else if(action == 'E' || action == 'e')
		{
			try
			{
				writeToFile();
			}
			catch(IOException e)
			{
				System.out.printf("exception catch\n");
			}
		}

		else if(action == 'O' || action == 'o')
		{
			try
			{
				readFromFile();
			}
			catch(Exception e)
			{
				System.out.println("exception catch");
			}
		}

		else
		{
			System.out.printf("\nYou entered wrong action!!\n\n");
		}

	}

	/**
	 *compares board and ordered board
	 *@return true if board is a solution
	 */
	@Override
	public boolean isSolved()
	{
		int zero_count = 0;
		int numb = 1;

		for(int i=0 ; i<size*size-1 ; ++i)
		{
			if(board[i] == 0)
			{
				zero_count++;
				continue;
			}
			else if(board[i] != 0)
			{
				if(board[i] == numb)
				{
					numb++;
				}
				else
				{
					if(board[i] != -10)
					{
						System.out.printf("NOT SOLVED\n");
						return false;
					}
				}
			}
		}
		if(board[size*size-1] == -10)
		{
			System.out.printf("SOLVED\n");
			return true;
		}
		return true;
	}


	/**
	 *takes indexes and returns the corresponding cell content
	 *@param a
	 *@param b
	 *@return corresponding cell content
	 */
	@Override
	public int cell(int a,int b)	//one dimensional array so I use just one parameter
	{
		if(a>size || a<0)
		{
			System.out.printf("Indexes are not valid. Exiting...\n\n");
			System.exit(0);
		}

		return board[a];
	}


	/**
	 *Equals method takes object of type object and cast object into BoardArray1D
	 *and controls if two boards equal or not
	 *@return true if two boards are equal
	 *@param o object of type object
	 */
	@Override
	public boolean Equals(Object o)
	{
		BoardArray1D temp = (BoardArray1D)o;
		if(size == temp.size)
		{
			for (int i=0 ; i<temp.size ; ++i)
			{
				if(board[i] != temp.board[i])
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
		return true;
	}


	/**
	 *@return true if the last move is valid or not
	 */
	@Override
	public boolean validMoves()
	{
		int move_left=0, move_right=0, move_up=0, move_down=0;

		if ( !((bb%column == 0 || board[bb-1] == 0))){
			move_left = 1;
		}
		if ( !((bb+1)%column == 0 || board[bb+1] == 0)){
			move_right = 1;
		}
		if ( !(bb < column || board[bb-column] == 0)){
			move_up = 1;
		}
		if ( !((row*column-(column+1)) < bb || board[bb+column] == 0)){
			move_down = 1;
		}

		if(last_move == 'L' || last_move == 'l')
		{
			if (move_left == 1){
				return true;
			}
			else{
				return false;
			}
		}

		else if(last_move == 'R' || last_move == 'r')
		{
			if (move_right == 1){
				return true;
			}
			else{
				return false;
			}
		}

		else if(last_move == 'U' || last_move == 'u')
		{
			if (move_up == 1){
				return true;
			}
			else{
				return false;
			}
		}

		else if(last_move == 'D' || last_move == 'd')
		{
			if (move_down == 1){
				return true;
			}
			else{
				return false;
			}
		}
		return false;
	}

}
