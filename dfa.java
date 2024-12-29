// Noah Beightol
// COT 4210
// Arup Guha
// Fall 2024

import java.util.*;

public class dfa {
  public static void main(String[] args){
    Scanner s = new Scanner(System.in);
    int dfaCount = Integer.parseInt(s.nextLine());
    HashMap<Integer, String> myHash = new HashMap<Integer, String>();
    System.out.println();

    // We need to loop through each dfa
    for (int index = 0; index < dfaCount; index++) {
      String[] dfaProps = s.nextLine().split(" ");
      int numStates = Integer.parseInt(dfaProps[0]); // Total lines to take in
      int alphabetSize = Integer.parseInt(dfaProps[1]);
      int numStrings = Integer.parseInt(dfaProps[2]);
      String[] acceptedStates = s.nextLine().split(" ");
      String[] words = new String[numStrings];
      int[][] array = new int[numStates][alphabetSize];

      // Since we always know the first int stores the # of accepted states
      // Grab first element
      int numAccStates = Integer.parseInt(acceptedStates[0]);

      // Use a hash map for easy look up when checking if the word is
      // in the language
      for (int i = 1; i < numAccStates + 1; i++) {
        myHash.put(Integer.parseInt(acceptedStates[i]), "valid");
      }

      // take in lamda transistions
      for (int i = 0; i < numStates; i++) {
        String[] transistions = s.nextLine().split(" ");
        for (int j = 0; j < alphabetSize; j++) {
          array[i][j] = Integer.parseInt(transistions[j]);
        }
      }

      // Take in strings
      for (int k = 0; k < numStrings; k++) {
        words[k] = s.nextLine();
      }

      System.out.println("DFA #" + (index+1));
      for (int x = 0; x < numStrings; x++) {
        if (isRegularLanguage(array, myHash, words[x], alphabetSize)) {
          System.out.println(words[x] + " is in L");
        } else {
          System.out.println(words[x] + " is not in L");
        }
      }
      System.out.println();
      myHash.clear();
    }
  }
  // DFA traversal algorithm
  public static boolean isRegularLanguage(int array[][], HashMap<Integer, String> myHash, String word, int aSize) {
    int curState = 0;
    int len = word.length();
    char[] newWord = word.toCharArray();

    for (int i = 0; i < len; i++) {
      int val = ((int) newWord[i]) - 'a';
      curState = array[curState][val];
    }
    return myHash.containsKey(curState);
  }
}
