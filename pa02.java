/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Noah Beightol
| Language: c, c++, Java, GO, Python
|
| To Compile: javac pa02.java
| To Execute: java -> java pa02 inputFile.txt 8
|
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Fall 2022
| Instructor: McAlpin
| Due Date: Nov 27th 2022
|
+=============================================================================*/

// import statements
import java.util.*;
import java.io.*;


// main class
public class pa02 {
  public static void main(String[] args) throws IOException{
    // declaring needed variables
    //Scanner in = new Scanner();
    String readInput = "";
    String temp = "";
    String in = "";
    // store binary representation of input string
    int myBits = 0;
    int length = 0;
    int num = 0;
    int lf = 10;
    int total = 0;

    // checking if file is empty
    if (0 < args.length) {

      // scanning in input parameters
      Scanner input = new Scanner(new File(args[0]));
      temp = args[1];

      // converting string to int
      int size = Integer.parseInt(temp);


      // checking if checksum size is valid
      if (size != 8 && size != 16 && size != 32) {
        // print out error message if not valid
        System.err.println("Valid checksum sizes are 8, 16, or 32");
      }
      else {
        // loop to scan in all lines from input file
        while(input.hasNextLine())
        {
          in = input.nextLine();
          // concatinating each word into one large string
          readInput = readInput + in;
        }

        // stores length of input
        length = (readInput.length() + 1);

        // printing input 80 characters at a times
        for (int i = 0; i < readInput.length(); i++)
        {
          // move to next line if character limit has been reached
          if (i % 80 == 0)
            System.out.print("\n");
          System.out.print(readInput.charAt(i));

        }
        System.out.println("\n");

        // converts input string to binary
        for (int i = 0; i < length-1; i++) {

          // temporarily stores character
          char temp1 = readInput.charAt(i);

          // converts it to ascii value
          num = (int) temp1;

          // adds up ascii values
          myBits = myBits + num;
        }
      }
      // adding terminating charater
      myBits = myBits + lf;

      // converts into 8 bit format
      if (size == 8) {
        total = myBits % 256;
        System.out.println(String.format(size + " bit checksum is    %x for all  " + length + " chars", total));
      }
      // converts into 16 bit format
      if (size == 16) {
        total = myBits % 526;
        System.out.println(String.format(size + " bit checksum is    %x for all  " + length + " chars", total));
      }
      // converts into 32 bit format
      if (size == 32) {
        total = myBits % 1028;
        System.out.println(String.format(size + " bit checksum is    %x for all  " + length + " chars", total));
      }

    }
    else {
      // if not file is detected, print error
      System.err.println("No files detected!");
    }
  }
}

/*=============================================================================
| I Noah Beightol no145336 affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
