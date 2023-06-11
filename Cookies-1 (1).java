/* Noah Beightol
   Dr. Steinberg
   COP3503 Spring 2023
   Programming Assignment 3
*/
// import statements
import java.util.*;
import java.io.*;

public class Cookies {
  // declaring needed variables
  int greedFactor[];
  int sizeFactor[];
  int numHappy, numAngry, nCampers, nCookies;

  // overloaded constructor
  Cookies(int cookies, int campers, String greedyFile, String sizeFile) {
    // store file data into arrays
    this.greedFactor = read(greedyFile, campers);
    this.sizeFactor = read(sizeFile, cookies);
    this.nCookies = cookies;
    this.nCampers = campers;
  }

  // finds an optimal solution for campers using a greedy algorithm
  // Our greedy algorithm sorts the users from least greed to most greedy
  // We make the greedy choice to always find andgive the camper a desired cookie
  public void passCookies() {
    // sort the cookies and campers from smallest to largest
    Arrays.sort(sizeFactor);
    Arrays.sort(greedFactor);
    int index = 0;

    // loop through cookies and distribute to campers
    for (int i = 0; i < nCampers; i++) {
      // see if cookie does not meet the campers want
      if (sizeFactor[i] < greedFactor[i]) {
        index = i;
        int ogIndex = i;
        // go through cookies and find first cookie that meets campers desire
        while ((sizeFactor[index] < greedFactor[i]) && index < nCookies-1) {
          index++;
        }
        // if we found the correct cookie, update happy camper
        if (sizeFactor[index] >= greedFactor[i]) {
          sizeFactor[index] = -1;
          numHappy++;
        }
        else {
          sizeFactor[ogIndex] = -1;
          numAngry++;
        }
      }
      // if the cookie meets the campers needs at first, update happy camper
      else {
        sizeFactor[i] = -1;
        numHappy++;
      }
    }
  }

  // reads file
  public int[] read(String fileName, int size) {
    int array[] = new int[size];
    int i = 0;
    // attempts to read files
    try {
      Scanner in = new Scanner(new File(fileName));

      // takes in input from file
      while (in.hasNextInt()) {
        int tmp = in.nextInt();
        array[i] = tmp;
        i++;
      }
    }
    // catches any errors
    catch (IOException e) {
      e.printStackTrace();
    }
    return array;
  }

  // displays the # of happy and angry campers
  public void display() {
    System.out.println("There are " + numHappy + " happy campers.");
    System.out.println("There are " + numAngry + " angry campers.");
  }
}
