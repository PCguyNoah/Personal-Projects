// Noah Beightol, NID: no145336, COP 3503, Fall 2022
// Last edited: Oct 10/2/2022
import java.util.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.awt.Point;

// this class determines wether, given an arbitrary sized chess board and # of knights pieces,
// if any knights can attack each other, returns false if they can, true otherwise
public class SneakyKnights
{
	// using a hashset, we are able to determine if any knight would be able to attack another
	public static boolean allTheKnightsAreSafe(ArrayList<String> coordinateStrings, int boardSize)
	{
		// creating the chess board with a hash set
		HashSet<Point> board = new HashSet<Point>();
		int[] tmpArray = new int[2];

		// iterating through the coordinate array list to conveter the strings to int values
		for (int i = 1; i < (coordinateStrings.size()); i++){

			// assiging temp string and passing it into the conveter method
			String temp = coordinateStrings.get(i);
			tmpArray = converter(temp);

			// temporally add to int array
			int row = tmpArray[0];
			int col = tmpArray[1];

			// if attackVectors returns true, then we know one of the knights can be attacked so we exit
			if (attackVectors(board, row, col))
			{
					return false;
			}
			// otherwise, were going to add the knight and keep checking
			else
			{
				board.add(new Point(row, col));
			}
		}
		// if no knight can attack
		return true;
	}

	// takes in the hashset and coordinates of potential knight, calulates the possible attack vectors
	// and returns  true or false if the knight will attack a previously entered knight
	public static boolean attackVectors(HashSet<Point> board, int row, int col)
	{
		// these variables store the potential attacks of a passed in knight
		int row1 = 0, col1 = 0, row2 = 0, col2 = 0;

		// we split each knights attacks into 4 quadrants: Q1, Q2, Q3, Q4
		// math to check Q1 attack 2 up, 1 left
		row1 = row + 2;
		col1 = col - 1;

		// Q1 attack 2 calculations 1 up, 2 left
		row2 = row + 1;
		col2 = col - 2;

		// checking to see if generated attack points match any previously entered knights
		if (board.contains(new Point(row1, col1)) || board.contains(new Point(row2, col2)))
		{
			return true;
		}
		// we need to reset values back to zero for next calculations
		row1 = 0;
		row2 = 0;
		col1 = 0;
		col2 = 0;

		// Q2 math: 2 up, 1 right
		row1 = row + 2;
		col1 = col + 1;
		// 1 up, 2 right
		row2 = row + 1;
		col2 = col + 2;

		// check and reset
		if (board.contains(new Point(row1, col1)) || board.contains(new Point(row2, col2)))
		{
			return true;
		}
		row1 = 0;
		row2 = 0;
		col1 = 0;
		col2 = 0;

		//Q3 math: 1 down, 2 left
		row1 = row - 1;
		col1 = col - 2;
		// 1 up, 2 right
		row2 = row - 2;
		col2 = col - 1;

		// check and reset
		if (board.contains(new Point(row1, col1)) || board.contains(new Point(row2, col2)))
		{
			return true;
		}
		row1 = 0;
		row2 = 0;
		col1 = 0;
		col2 = 0;

		// Q4 math: 1 down, 2 right
		row1 = row - 1;
		col1 = col + 2;
		// 1 up, 2 right
		row2 = row - 2;
		col2 = col + 1;

		// check and reset
		if (board.contains(new Point(row1, col1)) || board.contains(new Point(row2, col2)))
		{
			return true;
		}

		// if there are no possible attacks, we return false
		return false;
	}

	// takes in a string coordnate and converters it to an array storing x and y location
	public static int[] converter(String str)
	{
		int yCord = 0;
		int xCord = 0;
		int[] array = new int[2];

		// loop through the coordinate string to convert to correct integer values
		for (int i = 0; i < str.length(); i++)
		{
			// declaring needed flag for if statement
			Boolean flag = Character.isDigit(str.charAt(i));

			// checking if charcter at index i is a "number"
			if (flag)
			{
				// multiplying by 10 to get it into the right spot using Horners Method
				xCord = xCord * 10;
				xCord += (str.charAt(i) - '0');
			}
			else
			{
				// multiplying by 26 (base 26 to base 10) to get it into the right spot again using Horners Method
				yCord = yCord * 26;
				yCord += (str.charAt(i) - 'a') + 1;
			}
		}
		// here we store each coorinate in the array and return it
		array[0] = xCord;
		array[1] = yCord;
		return array;
	}

	// returns precieved difficultyRating
	public static double difficultyRating(){
		return 3.0;
	}

	// returns number of hours spent on the project
	public static double hoursSpent() {
		return 6.0;
	}
}
