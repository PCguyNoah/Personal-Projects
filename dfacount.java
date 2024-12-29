// Noah Beightol
// COT 4210
// Arup Guha
// Fall 2024

import java.util.*;

// This program takes in a given number of DFA descriptions
// a integer K and outputs how many strings of length K are accepted by the dfa
public class dfacount {
  // mod 10^9 + 7
  public static int MOD_SIZE = 1000000007;
  public static void main(String[] args){
    Scanner s = new Scanner(System.in);
    int dfaCount = Integer.parseInt(s.nextLine());

    // We loop through each dfa
    for (int index = 0; index < dfaCount; index++) {
      String[] dfaProps = s.nextLine().split(" ");
      int numStates = Integer.parseInt(dfaProps[0]);
      int alphabetSize = Integer.parseInt(dfaProps[1]);
      int kSize = Integer.parseInt(dfaProps[2]);
      String[] acceptedStates = s.nextLine().split(" ");
      int[][] array = new int[numStates][alphabetSize];

      // Grab first element in the next line which stores # of accepted states
      int numAccStates = Integer.parseInt(acceptedStates[0]);
      int[] acceptingStates = new int[numAccStates];

      // Now we loop through and store all accept states
      for (int i = 1; i < numAccStates + 1; i++) {
        acceptingStates[i-1] = Integer.parseInt(acceptedStates[i]);
      }

      // take in lamda transistions
      for (int i = 0; i < numStates; i++) {
        String[] transistions = s.nextLine().split(" ");
        for (int j = 0; j < alphabetSize; j++) {
          array[i][j] = Integer.parseInt(transistions[j]);
        }
      }

      // Output results
      long res = dfaSizer(
        array,
        acceptingStates,
        kSize,
        numStates,
        alphabetSize
      );
      System.out.println(res);
    }
  }

  // Calculates # of accepted strings of length k in a given DFA
  public static long dfaSizer
  (
    int[][] transitions,
    int[] acceptingStates,
    int k,
    int s,
    int alphabetSize
  ) {
    // Create our DP 2D array
    long[][] dp = new long[k+1][s];
    dp[0][0] = 1;
    long res = 0;

    // Loop through all lengths x to size k-1
    for (int x = 0; x < k; x++) {
      for (int y = 0; y < s; y++) {
        if (dp[x][y] == 0) continue;

        // loop through the all characters in the alphabet
        for (int c = 0; c < alphabetSize; c++) {
          // find transition for state y on character c
          int z = transitions[y][c];
          // update value in the table
          dp[x+1][z] = (dp[x+1][z] + dp[x][y]) % MOD_SIZE;
        }
      }
    }

    // sum all words in the accepting states
    for (int y : acceptingStates) {
      res = (res + dp[k][y]) % MOD_SIZE;
    }

    // return the result
    return res;
  }
}
