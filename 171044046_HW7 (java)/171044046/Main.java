/**
 * Main class + Static Method  (Driver File)
 *
 * @author Esra Eryılmaz
 * @version 1.0
 * @since 2020-01-15
 */

public class Main
{
	public static void main(String[] args)
	{
		String argv1, argv2, argv3;
		argv1 = "file1.txt";
		argv2 = "file2.txt";
		argv3 = "file3.txt";

		// I create 3 BoardArray1D object and 2 BoardArray2D object
		BoardArray1D a1 = new BoardArray1D();
		BoardArray1D a2 = new BoardArray1D();
		BoardArray1D a3 = new BoardArray1D();
		BoardArray2D b1 = new BoardArray2D();
		BoardArray2D b2 = new BoardArray2D();

		System.out.printf("\n\t( HW7 ) Inheritance in Java\n\n");
		System.out.printf("\t\tTEST STARTING...\n\n");
		System.out.printf("-----------------------------------------------------------\n");

		System.out.printf("\tBOARDARRAY1D CLASS TEST STARTING...\n\n");
		System.out.printf("(1)BoardArray1D:\n");
		a1.setSize(0,argv1);
		try
		{
			a1.readFromFile();
		}
		catch(Exception e)
		{
			System.out.println("exception catch");
		}
		// I print board using toString method
		System.out.println(a1);
		a1.move('D');
		System.out.println(a1);
		a1.move('L');
		System.out.println(a1);
		a1.NumberOfBoards();
		a1.lastMove();
		a1.numberOfMoves();
		System.out.printf("isSolved: ");
		a1.isSolved();
		System.out.printf("\ncell() method test : (board[5] =  %d)",a1.cell(5,0));

		System.out.printf("\n-----\n\n");

		System.out.printf("(2)BoardArray1D:\n");
		a2.setSize(0,argv2);
		try
		{
			a2.readFromFile();
		}
		catch(Exception e)
		{
			System.out.println("exception catch");
		}

		System.out.println(a2);
		a2.move('R');
		System.out.println(a2);
		a2.move('D');
		System.out.println(a2);
		System.out.printf("Equals() method test : Are first and second 1D board array equal? -> %b\n\n",a1.Equals(a2));
		a2.lastMove();
		a2.numberOfMoves();
		System.out.printf("\ncell() method test : (board[7] =  %d)",a2.cell(7,0));

		System.out.printf("\n-----\n\n");

		System.out.printf("(3)BoardArray1D:\n");
		a3.setSize(0,argv3);
		try
		{
			a3.readFromFile();
		}
		catch(Exception e)
		{
			System.out.println("exception catch");
		}
		System.out.println(a3);
		a3.move('U');
		System.out.println(a3);
		a3.move('E');
		System.out.println(" newfile1.txt\n\n");

		System.out.printf("\tBOARDARRAY1D CLASS TEST FINISHED!\n\n");
		System.out.printf("-----------------------------------------------------------\n");

		System.out.printf("\tBOARDARRAY2D CLASS TEST STARTING...\n\n");

		System.out.printf("(1)BoardArray2D:\n");
		b1.setSize(0,argv1);
		try
		{
			b1.readFromFile();
		}
		catch(Exception e)
		{
			System.out.println("exception catch");
		}
		System.out.println(b1);
		b1.move('R');
		System.out.println(b1);
		b1.move('D');
		System.out.println(b1);
		b1.NumberOfBoards();
		b1.lastMove();
		b1.numberOfMoves();
		System.out.printf("isSolved: ");
		b1.isSolved();
		System.out.printf("\ncell() method test : (board[2][1] =  %d)",b1.cell(2,1));

		System.out.printf("\n-----\n\n");

		System.out.printf("(2)BoardArray2D:\n");
		b2.setSize(0,argv2);
		try
		{
			b2.readFromFile();
		}
		catch(Exception e)
		{
			System.out.println("exception catch");
		}
		System.out.println(b2);
		System.out.printf("Equals() method test. Are first and second 2D board array equal? -> %b\n\n",b1.Equals(b2));

		System.out.printf("\tBOARDARRAY2D CLASS TEST FINISHED!\n\n");
		System.out.printf("-----------------------------------------------------------\n");

		System.out.printf("\tSTATIC METHOD TEST STARTING...\n\n");

		AbstractBoard []arr = new AbstractBoard[5];
		arr[0] = a1;
		arr[1] = a2;
		arr[2] = a3;
		arr[3] = b1;
		arr[4] = b2;

		validMoves(arr);

		System.out.printf("-----------------------------------------------------------\n\n");
	}



	/**
	 *This static method takes an array of AbstractBoard references and controls if the last move is valid or not
	 *@return true or false according to the last move
	 *@param AbstractBoard array
	 */
	public static boolean validMoves(AbstractBoard[] arr)
	{
		boolean x = false;
		for(int i=0 ; i<5 ; i++)
		{
			x = arr[i].validMoves();

			System.out.printf("For arr[%d] ,Static method returns -> %b\n", i ,x);
		}
		return x;
	}
}