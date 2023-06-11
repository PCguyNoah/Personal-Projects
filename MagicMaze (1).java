/*  Noah Beightol
 *  COP3503 Computer Science 2
 *  Programming Assignment 2
 *  Spring 2023
 */

// import statements
import java.util.*;
import java.io.*;
import java.awt.Point;

// Solves a maze containing portals of a given size by using recursive backtracking
public class MagicMaze {
  // store all 4 possible moves
  public static final int [] x = {-1, 0, 1, 0};
  public static final int [] y = {0, -1, 0, 1};

  // declaring needed variables
  int row, col;
  String fileName;
  Point exit;
  int curMove[];
  char maze[][];
  int usedMaze[][];

  // this hashmap stores the locations of the first set of portals
  HashMap<String, Point> myHash = new HashMap<String, Point>();
  // we store the next set at the indexes of this point array
  Point portals[];

  // overloaded constructor
  MagicMaze(String fileName, int row, int col) {
    this.fileName = fileName;
    this.row = row;
    this.col = col;
    this.curMove = new int[2];
    this.usedMaze = new int[row][col];
    this.portals = new Point[row*col];
    this.maze = readFile(fileName, row, col);
  }

  // finds the quickest path out of the maze
  public Boolean solveMagicMaze() {
    int prev[] = new int[2];

    // temporarily store the first "previous" portal at the exit coordinates
    // that way it never gives us an out of bounds error, and we know there will never be an actual portal here
    prev[0] = exit.x;
    prev[1] = exit.y;

    // call the recursive function
    if (solveMagicMazeR(maze, row-1, 0, curMove, usedMaze, prev)) {
      // return true if we solved! otherwise we return false
      return true;
    }
    return false;
  }

  // recursive backtracking method for finding solution to the maze
  public Boolean solveMagicMazeR(char maze[][], int row, int col, int curMove[], int usedMaze[][], int prev[]) {
    // always mark the current position as used
    usedMaze[row][col] = 1;

    // loop tries all 4 possible moves
    for (int i = 0; i < 4; i++) {
      // calculate new move
      curMove[0] = row + x[i];
      curMove[1] = col + y[i];

      // bounds check
      if (isBoundsOk(curMove[0], curMove[1]) && maze[curMove[0]][curMove[1]] != '@') {
        // if the bounds are ok we update the current row and col
        row = curMove[0];
        col = curMove[1];

        // base case checks if we escaped the maze
        if (maze[curMove[0]][curMove[1]] == 'X') {
          return true;
        }
        // check if current location is a portal
        if (maze[row][col] != '@' && maze[row][col] != '*') {
          int index;
          String posIndex = Character.toString(maze[row][col]);

          // check if that portal is in HashMap
          if (myHash.containsValue(new Point(row,col))) {
            // set the portal that we just landed at to used before making the jump to next portal
            usedMaze[row][col] = 1;
            // get index of next portal
            index = Integer.parseInt(posIndex);

            // store new position in row and col
            row = portals[index].x;
            col = portals[index].y;

            // store location of this portal so we can unmark it later
            prev[0] = row;
            prev[1] = col;
          }
          // if the portal isnt in the hashmap its in the point array
          else {
            // set the portal that we just landed at to used before making the jump
            usedMaze[row][col] = 1;
            // get index from hashmap
            Point temp = myHash.get(posIndex);

            // store new coordinates
            row = temp.x;
            col = temp.y;

            // store location of this portal
            prev[0] = row;
            prev[1] = col;
          }
        }
        // check if the next move solves the maze
        if (solveMagicMazeR(maze, row, col, curMove, usedMaze, prev)) {
          return true;
        }
      }
    }
    // Backtracking and setting previous portal and position to unused
    usedMaze[row][col] = 0;
    usedMaze[prev[0]][prev[1]] = 0;
    return false;
  }

  // method verifies potential move is within the bounds of the maze and is unused
  public Boolean isBoundsOk(int x, int y) {
    // if the attempted coordinates are invalid we return false
    if (x < 0 || y < 0 || x >= row || y >= col || usedMaze[x][y] == 1) {
      return false;
    }
    return true;
  }

  // takes in our file and returns a 2d array storing maze
  public char[][] readFile(String fileName, int row, int col) {
    char array[][] = new char[row][col];
    int k = 0;
    int index = 0;

    // opens file and stores input
    try {
      Scanner in = new Scanner(new File(fileName));

      // Reads in each line of the maze
      while(in.hasNextLine()) {
        String input = in.nextLine();
        // converts string to char array
        char temp[] = input.toCharArray();

        // copies and array into 2d array
        for (int i = 0; i < col; i++)  {
          // stores the location of the exit
          if (temp[i] == 'X') {
            // store the location of the exit
            exit = new Point(k,i);
          }
          else if (temp[i] != '@' && temp[i] != '*') {
            // hash the portal location
            String portal = Character.toString(temp[i]);
            // check if already stored this value
            if (myHash.containsKey(portal)) {
              // store second portal location in array
              index = Integer.parseInt(portal);
              portals[index] = new Point(k,i);
            }
            else {
              // if we have haven't hashed the value we hash it
              myHash.put(portal, new Point(k, i));
            }
          }
          array[k][i] = temp[i];
        }
        k++;
      }
    }
    // catches any errors
    catch (IOException e) {
      e.printStackTrace();
    }
    // return the maze
    return array;
  }
}
