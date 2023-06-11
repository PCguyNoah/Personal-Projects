/* Noah Beightol
 * Dr. Steinberg
 * COP3503 Spring 2023
 * Programming Assignment 1
 */
 import java.util.*;
 import java.io.*;

 public class Game {
   // declaring all needed variables
   int board[][];
   char moves[];
   int edge1 = 7, edge2 = 0, knight = 407;
   int k = 1;
   // constructor
   Game(int size, String fileName) {
     this.board = new int[size][size];
     this.moves = readMoves(fileName);

     // setting edge of board in order to check move validity later
     for (int i = 0; i < size; i++) {
       // all moves are valid if the position is not -1
       board[i][edge1] = -1;
       board[edge2][i] = -2;
     }
     // important to overwrite the index 0,7 so that the array doesn't go out of bounds
     board[edge2][edge1] = -1;
   }

   // this method runs the game
   public int play(int player) {
     // declaring needed variables
      int winner = 0, player1 = 1, player2 = 2, choice = 0, row = 7, col = 0, i = 0;
      int goNext = player1;
      Boolean keepPlaying = true;
      char p1Choice[] = {'d','r','b'};

      // strategy for player 1
      if (player == 1) {
        // keep playing until a winner is found
        while (keepPlaying) {
          if (goNext == player1) {
            //char input = in.next().charAt(0);
            int tempMove[] = coordinateCalc(board, p1Choice[choice], row, col, player1);
            row = tempMove[0];
            col = tempMove[1];

            // end the game if knight is at the bottom
            if (row == 0 && col == 7) {
              player = tempMove[2];
              // ends game
              keepPlaying = false;
              break;
            }
            // mirror players move in order to always win
            if (this.moves[i] == 'r') {
              choice = 1;
            }
            if (this.moves[i] == 'b') {
              choice = 2;
            }
            if (this.moves[i] == 'd') {
              choice = 0;
            }
            // move to player2's turn
            goNext = player2;
          }

          if (goNext == player2) {
            int tempMove[] = coordinateCalc(board, moves[i], row, col, player2);
            row = tempMove[0];
            col = tempMove[1];

            // end the game if knight is at the bottom
            if (row == 0 && col == 7) {
              player = tempMove[2];
              // ends game
              keepPlaying = false;
              break;
            }
            // incrementing to next move
            i++;
            // move to player1's turn
            goNext = player1;
          }
        }
      }
      // strategy for player 2
      if (player == 2) {
        // if we go down first and then mirror we always lose
        choice = 2;
        // keep playing until a winner is found
        while (keepPlaying) {
          if (goNext == player1) {

            // special case if player does all right attack
            if (row == 6 && col == 5) {
              choice = 2;
            }

            // get next move
            int tempMove[] = coordinateCalc(board, p1Choice[choice], row, col, player1);
            row = tempMove[0];
            col = tempMove[1];

            // end the game if knight is at the bottom
            if (row == 0 && col == 7) {
              player = tempMove[2];
              // ends game
              keepPlaying = false;
              break;
            }

            // mirror moves
            if (this.moves[i] == 'r') {
              choice = 1;
            }
            if (this.moves[i] == 'b') {
              choice = 2;
            }
            if (this.moves[i] == 'd') {
              choice = 0;
            }
            // move to player2's turn
            goNext = player2;
          }

          if (goNext == player2) {
            int tempMove[] = coordinateCalc(board, moves[i], row, col, player2);
            row = tempMove[0];
            col = tempMove[1];

            // end the game if knight is at the bottom
            if (row == 0 && col == 7) {
              player = tempMove[2];
              // ends game
              keepPlaying = false;
              break;
            }
            // incrementing to next move
            i++;
            // move to player1's turn
            goNext = player1;
          }
        }
      }

      // returning the winner
      winner = player;
      return winner;
   }

   // function returns the move commands for player2
   public char[] readMoves(String fileName) {
     // variables needed to store moves
     char tempMoves[] = new char[64];
     int i = 0, c = 0;

     // handles file io
     try {
       File myFile = new File(fileName);
       FileReader fileIn = new FileReader(myFile);
       BufferedReader buffer = new BufferedReader(fileIn);

       // reading in char at a time from file
       while((c = buffer.read()) != -1) {
          // making sure we dont get any white space
          if (c != 13 && c != 10) {
            tempMoves[i] = (char) c;
            i++;
          }
       }
     }
     // catches any errors
     catch (IOException e) {
       e.printStackTrace();
     }
     // returns moves to function
     return tempMoves;
   }

   // This function calculates and returns the coordinates of a valid move
   public int[] coordinateCalc(int board[][], char move, int row, int col, int player) {
     int validMove[] = new int[3];

     // checks for invalid move
     if (board[row][col] == -1) {
       // invalid move is corrected to move down
       validMove[0] = row - 1;
       validMove[1] = col;
       validMove[2] = player;
     }
     if (board[row][col] == -2) {
       // invalid move is correct to move right
       validMove[0] = row;
       validMove[1] = col + 1;
       validMove[2] = player;
     }
     if (board[row][col] == 0) {
       // math for a down move
       if (move == 'b') {
         // down one row, same col
         validMove[0] = row - 1;
         validMove[1] = col;
         validMove[2] = player;
       }
       // math for a diagonal move
       if (move == 'd') {
         // down one row, over one col
         validMove[0] = row - 1;
         validMove[1] = col + 1;
         validMove[2] = player;
       }
       // math for a right move
       if (move == 'r') {
         // same row, over one col
         validMove[0] = row;
         validMove[1] = col + 1;
         validMove[2] = player;
       }
     }
     // returns array storing valid coordinates
     return validMove;
   }
 }
