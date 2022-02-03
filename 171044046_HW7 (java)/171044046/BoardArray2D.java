/**
 * BoardArray2D class
 *
 * @author Esra Eryılmaz
 * @version 1.0
 * @since 2020-01-15
 */

import java.util.*;
import java.lang.*;
import java.io.*;


public class BoardArray2D extends AbstractBoard
{
	private int[][] board;
	private int[][] ordered_board;


	public BoardArray2D()
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
		for(int i=0 ; i<row ; ++i)
		{
			for(int j=0 ; j<column ; ++j)
			{
				if (board[i][j] == -10)		// -10 is a blank space for my implementation
				{
					System.out.printf("\t");
				}
				else if(board[i][j] == 0)
				{
					System.out.printf("00\t");
				}
				else if(board[i][j] == 1 || board[i][j] == 2 || board[i][j] == 3 || board[i][j] == 4 || board[i][j] == 5 || board[i][j] == 6 || board[i][j] == 7 || board[i][j] == 8 || board[i][j] == 9 )
				{
					System.out.printf("0%d\t",board[i][j]);
				}
				else
				{
					System.out.printf("%d\t",board[i][j]);
				}
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

		File file = new File(input_line);

		Scanner sc1 = new Scanner(file);
		Scanner sc2 = new Scanner(file);
		Scanner sc3 = new Scanner(file);

		int i=0,j=0;
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
		row=0;
		while(sc2.hasNextLine())
		{
			sc2.nextLine();
			row++;
		}
		sc2.close();

		size=0;
		i=0;
		while(sc3.hasNext())
		{
			if(i == bb)
			{
				tempBoard[i] = -10;
				sc3.next();
			}
			else
			{
				tempBoard[i] = Integer.parseInt(sc3.next());
				if(tempBoard[i] == 0)
				{
					numb_of_zeros++;
				}
			}
			i++;
		}

		sc3.close();
		size = i;
		column = size/row;

		if((bb+1)%column == 0)
		{
			bb_row = ((bb+1)/column)-1;
			bb_column = column-1;
		}
		else if((bb+2)%column == 0)
		{
			bb_row = ((bb+2)/column)-1;
			bb_column = column-2;
		}
		else if((bb+3)%column == 0)
		{
			bb_row = ((bb+3)/column)-1;
			bb_column = column-3;
		}
		else if((bb+4)%column == 0)
		{
			bb_row = ((bb+4)/column)-1;
			bb_column = column-4;
		}

		board = new int[row][column];
		ordered_board = new int[row][column];
		int total_number = size - numb_of_zeros;

		int k=0;
		for(i=0 ; i<row ; i++)
		{
			for(j=0 ; j<column ; j++)
			{
				board[i][j] = tempBoard[k];
				ordered_board[i][j] = tempBoard[k];
				k++;
			}
		}

		int num = 1;
		for(i=0 ; i<row ; i++)
		{
			for(j=0 ; j<column ; j++)
			{
				if(num == total_number)
				{
					ordered_board[i][j] = -10;
				}
				else if(ordered_board[i][j] != 0)
				{
					ordered_board[i][j] = num;
					num++;
				}
			}
		}
	}


	/**
	 *writes the board to the file
	 *@exception IOException
	 */
	@Override
	public void writeToFile() throws IOException
	{
		System.out.printf("Please enter file name for saving the current board configuration : ");
		String name = "newfile1.txt";
		int k=0;
		String s;
		String n = "\n";
		try
		{
			Writer wr = new FileWriter(name);

			for(int i=0 ; i<row ; ++i){
				for(int j=0 ; j<column ; ++j){
					if (board[i][j] == -10)
					{
						wr.write("bb ");
						k++;
					}
					else
					{
						s = String.valueOf(board[i][j]);
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
		int k = 1;
		board = new int[row][column];
		ordered_board = new int[row][column];

		for(int i=0 ; i<row ; ++i)	// It takes the board to the final solution
		{
			for(int j=0 ; j<column ; ++j)
			{
				if(i==row-1 && j==column-1)
				{
					board[i][j] = -10;
					ordered_board[i][j] = -10;
					bb_row = i;
					bb_column = j;
				}
				else
				{
					board[i][j] = k;
					ordered_board[i][j] = k;
					k++;
				}
			}
		}

		bb = row*column-1;
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

		System.out.printf("Your action(L, R, U, D, T, E, O or Q): %c\n",action);

		if(action == 'L' || action == 'l')
		{
			if (move_left == 1){
				temp = board[bb_row][bb_column];
				board[bb_row][bb_column] = board[bb_row][bb_column-1];
				board[bb_row][bb_column-1] = temp;
				--bb;
				--bb_column;
				total_move++;
			}
			else{
				System.out.printf("There is no space!!\n");
			}
		}

		else if(action == 'R' || action == 'r')
		{
			if (move_right == 1){
				temp = board[bb_row][bb_column];
				board[bb_row][bb_column] = board[bb_row][bb_column+1];
				board[bb_row][bb_column+1] = temp;
				++bb;
				++bb_column;
				total_move++;
			}
			else{
				System.out.printf("There is no space!!\n");
			}
		}

		else if(action == 'U' || action == 'u')
		{
			if (move_up == 1){
				temp = board[bb_row][bb_column];
				board[bb_row][bb_column] = board[bb_row-1][bb_column];
				board[bb_row-1][bb_column] = temp;
				bb = bb - column;
				--bb_row;
				total_move++;
			}
			else{
				System.out.printf("There is no space!!\n");
			}
		}

		else if(action == 'D' || action == 'd')
		{
			if (move_down == 1){
				temp = board[bb_row][bb_column];
				board[bb_row][bb_column] = board[bb_row+1][bb_column];
				board[bb_row+1][bb_column] = temp;
				bb = bb + column;
				++bb_row;
				total_move++;
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
							System.out.printf("NOT SOLVED\n");
							return false;
						}
					}
				}
			}
		}
		if (board[row-1][column-1] == -10)
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
	public int cell(int a,int b)
	{
		if(a>row || a<0 || b>column || b<0)
		{
			System.out.printf("Indexes are not valid. Exiting...\n\n");
			System.exit(0);
		}

		return board[a][b];
	}


	/**
	 *Equals method takes object of type object and cast object into BoardArray2D
	 *and controls if two boards equal or not
	 *@return true if two boards are equal
	 *@param o object of type object
	 */
	@Override
	public boolean Equals(Object o)
	{
		BoardArray2D temp = (BoardArray2D)o;
		if(size == temp.size)
		{
			for (int i=0 ; i<temp.row ; ++i)
			{
				for(int j=0 ; j<temp.column ; ++j)
				{
					if(board[i][j] != temp.board[i][j])
					{
						return false;
					}
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

		if(last_move == 'L' || last_move == 'l')
		{
			if (move_left == 1)
				return true;
			else
				return false;
		}

		else if(last_move == 'R' || last_move == 'r')
		{
			if (move_right == 1)
				return true;
			else
				return false;
		}

		else if(last_move == 'U' || last_move == 'u')
		{
			if (move_up == 1)
				return true;
			else
				return false;
		}

		else if(last_move == 'D' || last_move == 'd')
		{
			if (move_down == 1)
				return true;
			else
				return false;
		}
		return false;
	}

}