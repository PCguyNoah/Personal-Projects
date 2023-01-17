// Noah Beightol, COP 3503, Fall 2022, SneakyQueens.java
// last edited: 09/04/2022

import java.util.*;
import java.util.ArrayList;
import java.util.Scanner;

public class SneakyQueens {
	// testing flag
	public static final int TEST_FLAG = 0;

	// main function for testing
	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		String input = "";

		// this function allows me to test my own test cases and inputs
		if(TEST_FLAG == 1){

			// taking in board size
			int boardSize = scan.nextInt();

			// creating my own arraylist and scanning in values
			ArrayList<String> coords = new ArrayList<String>();
			while(!(input.equals("a1"))){
				input = scan.nextLine();
				coords.add(input);
			}

			// determining if true or not
			if(allTheQueensAreSafe(coords, boardSize)){
				System.out.println("Hooray!");
			}
			else
				System.out.println("Queens are in danger!!");
		}

	}

	// this method returns true if queens are safe, false otherwise
	public static boolean allTheQueensAreSafe(ArrayList<String> coordinateStrings, int boardSize) {

		// declaring needed variables
		int[] rowFreq = new int[boardSize+1];
		int[] colFreq = new int[boardSize+1];
		int[] firstDiag = new int[boardSize+boardSize];
		int[] secDiag = new int[boardSize+boardSize];
		int[] tmpArray = new int[2];

		// looping through arrayList to get correct coordinate
		for (int i = 0; i < (coordinateStrings.size()); i++){

			// getting coordinate string from list and converting it
			String temp = coordinateStrings.get(i);
			tmpArray = converter(temp);
			int row = tmpArray[0];
			int col = tmpArray[1];

			// checks if queen has already been added to the same poistion
			if(rowFreq[row] > 0 || colFreq[col] > 0){
				return false;
			}
			else{
				rowFreq[row]++;
				colFreq[col]++;
			}

			// sum for main diagonals
			int sum = (row + col);

			// checking if queens has already been added in the same position
			if(firstDiag[sum] > 0){
				return false;
			}
			else{
				firstDiag[sum]++;
			}

			// calculating the sum for the secondary diagonal
			sum = (boardSize - row + 1) + col;

			// checking if queen shares same position, and returning if so
			if(secDiag[sum] > 0){
				return false;
			}
			else{
				secDiag[sum]++;
			}
		}
		// if all other test cases are not true, all queens are safe!
		// return true
		return true;
}

	// this method takes in a string coordinate and converts it to the correct format
	public static int[] converter(String str){

		// declaring needed variables
		int yCord = 0;
		int xCord = 0;
		int[] array = new int[2];

		// loop through the coordinate string to convert to correct integer values
		for (int i = 0; i < str.length(); i++){

			// declaring needed flag for if statement
			Boolean flag = Character.isDigit(str.charAt(i));

			// checking if charcter at index i is a "number"
			if(flag){
				// multiplying by 10 to get it into the right spot using Horners Method
				xCord = xCord * 10;
				xCord += (str.charAt(i) - '0');
			}
			else{
				// multiplying by 26 (base 26 to base 10) to get it into the right spot again using Horners Method
				yCord = yCord * 26;
				yCord += (str.charAt(i) - 'a') + 1;
			}
		}

		// storing indexes in Array
		array[0] = xCord;
		array[1] = yCord;

		// test function for printing newly created postions
		if(TEST_FLAG == 1){
			System.out.println("row position: " + array[0]);
			System.out.println("Col position: " + array[1]);
			System.out.println("\n");
		}

		// returning the coordinates
		return array;
	}

	// returns precieved difficultyRating
	public static double difficultyRating(){
		 double rating = 3.0;
		 return rating;
	}

	// returns number of hours spent on the project
	public static double hoursSpent() {
		double numHours = 16.0;
		return numHours;
	}
}
