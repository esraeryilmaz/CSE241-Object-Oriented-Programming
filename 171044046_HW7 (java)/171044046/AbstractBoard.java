/**
 * AbstractBoard class
 *
 * @author Esra Eryılmaz
 * @version 1.0
 * @since 2020-01-15
 */

import java.util.*;
import java.lang.*;
import java.io.*;


public abstract class AbstractBoard
{
	protected int size;
	protected int row;
	protected int column;
	protected int bb;
	protected int bb_row;
	protected int bb_column;
	protected int total_move;
	protected int total_element;
	protected int numb_of_zeros;		// it holds the impossible positions
	protected char last_move;
	protected int numb_of_board_obj;
	protected String input_line;

	public AbstractBoard()
	{
		size=0;
		row=0;
		column=0;
		bb=0;
		bb_row=0;
		bb_column=0;
		total_move=0;
		total_element=0;
		numb_of_zeros=0;
		last_move='S';
		numb_of_board_obj=0;
		input_line="NULL";
	}


	/**
	 *produces the board as string
	 *@return board as string
	 */
	public abstract String toString();


	/**
	 *reads the board from the file
	 *@exception Exception
	 */
	public abstract void readFromFile() throws Exception;


	/**
	 *writes the board to the file
	 *@exception IOException
	 */
	public abstract void writeToFile() throws IOException;


	/**
	 *resets the board to the solution
	 */
	public abstract void reset();


	/**
	 *sets the board size to given values
	 *@param user_size given user size
	 *@param argv given file name
	 */
	public abstract void setSize(int user_size, String argv);


	/**
	 *makes a move according to the given char parameter
	 *@param action given character
	 */
	public abstract void move(char action);


	/**
	 *compares board and ordered board
	 *@return true if board is a solution
	 */
	public abstract boolean isSolved();


	/**
	 *takes indexes and returns the corresponding cell content
	 *@param a
	 *@param b
	 *@return corresponding cell content
	 */
	public abstract int cell(int a,int b);


	/**
	 *@return true if two boards are equal
	 *@param o object of type object
	 */
	public abstract boolean Equals(Object o);


	/**
	 *@return true if the last move is valid or not
	 */
	public abstract boolean validMoves();


	/**
	 *returns the number of board objects created so far
	 *@return number of board
	 */
	public int NumberOfBoards()
	{
		System.out.printf("Number of board objects : %d\n",numb_of_board_obj);
		return numb_of_board_obj;
	}


	/**
	 *returns the last move
	 *@return last move
	 */
	public char lastMove()
	{
		System.out.printf("Last move : %c\n",last_move);
		return last_move;
	}


	/**
	 *returns the number of moves this board made
	 *@return number of moves
	 */
	public int numberOfMoves()
	{
		System.out.printf("Number of moves this board made : %d\n",total_move);
		return total_move;
	}

}
