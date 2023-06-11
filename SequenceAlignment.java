/* Noah Beightol
   Dr. Steinberg
   COP3503 Spring 2023
   Programming Assignment 4
*/
import java.io.*;
import java.util.*;

// This
class SequenceAlignment {
  // delcaring needed variables
  private String x;
  private String y;
  private String optimalString;
  private StringBuilder aligString1 = new StringBuilder();
  private StringBuilder aligString2 = new StringBuilder();
  private final char[] vowels = {'a', 'e', 'i', 'o', 'u', 'y'};
  private HashMap<Character, Integer> myVowels = new HashMap<Character, Integer>();

  // constructor
  SequenceAlignment(String stringOne, String stringTwo) {
    this.x = stringOne;
    this.y = stringTwo;

    // hashing vowels
    for (int i = 0; i < vowels.length; i++) {
      myVowels.put(vowels[i], i);
    }
  }

  // dynamic programming solution
  public void computeAlignment(int delta) {
    // setting up variables
    int xLen = x.length() + 1;
    int yLen = y.length() + 1;
    int i = 0, j = 0, cost = 0;
    int array[][] = new int[xLen+1][yLen+1];
    String tString;
    String bString;

    // initializing matrix with delta penatlies
    for (i = 0; i < xLen; i++) {
      array[i][0] = i * delta;
    }
    for (j = 0; j < yLen; j++) {
      array[0][j] = j * delta;
    }

    // find optimal solution
    for (j = 1; j < yLen; j++) {
      for (i = 1; i < xLen; i++) {

        // checks for match
        if (x.charAt(i-1) == y.charAt(j-1)) {
          cost = 0;
        }
        // checks if both are vowels
        else if (myVowels.containsKey(x.charAt(i-1)) && myVowels.containsKey(y.charAt(j-1))) {
          cost = 1;
        }
        // checks if theyre both consonants
        else if (myVowels.containsKey(x.charAt(i-1)) == false && myVowels.containsKey(y.charAt(j-1)) == false) {
          cost = 1;
        }
        else {
          // mismatch case
          cost = 3;
        }
        // update the position
        array[i][j] = min((cost + array[i-1][j-1]), (delta + array[i-1][j]), (2 + array[i][j-1]));
      }
    }

    // Building solution
    i = x.length();
    j = y.length();
    int curCost = array[i][j];

    while (i > 0 || j > 0) {
      // declaring variables
      // set each of these to a high value in case they go out of bounds
      int diagonal = 9999;
      int vertical = 9999;
      int horizontal = 9999;

      // making sure moves dont go out of bounds
      if (i-1 > 0) {
        vertical = array[i-1][j];
      }
      if (j-1 > 0) {
        horizontal = array[i][j-1];
      }
      if ((i-1) > 0 && (j-1) > 0) {
        diagonal = array[i-1][j-1];
      }
      // get the smallest move cost
      int min = min(diagonal, vertical, horizontal);

      // if the two characters are a match and diagonal we take that move
      if (i > 0 && j > 0 && (x.charAt(i-1) == y.charAt(j-1))) {
        curCost = array[i-1][j-1];
        aligString1.insert(0, x.charAt(i-1));
        aligString2.insert(0, y.charAt(j-1));
        i--;
        j--;
      }
      // otherwise the they are consonants and vowels
      else if (min == diagonal) {
        curCost = array[i-1][j-1];
        aligString1.insert(0, x.charAt(i-1));
        aligString2.insert(0, y.charAt(j-1));
        i--;
        j--;
      }
      // make vertical move
      else if (i > 0 && (array[i][j] == array[i-1][j] + delta)) {
        curCost = array[i-1][j];
        aligString1.insert(0, x.charAt(i-1));
        aligString2.insert(0, '-');
        i--;
      }
      // make horizontal move
      else {
        curCost = array[i][j-1];
        aligString1.insert(0, '-');
        aligString2.insert(0, y.charAt(j-1));
        j--;
      }
    }
  }

  // finds and returns the smallest value from 3 passed in parameters
  public int min(int case1, int case2, int case3) {
    if (case3 < case2 && case3 < case1) {
      return case3;
    }
    else if (case2 < case1 && case2 < case3) {
      return case2;
    }
    if (case3 <= case2 && case3 < case1) {
      return case2;
    }
    return case1;
  }
  // returns optimal string
  public String getAlignment() {
    String opt = aligString1.toString() + " " + aligString2.toString();
    return opt;
  }
}
