// Noah Beightol
// COT 4210
// Arup Guha
// Fall 2024

import java.util.*;

public class chomsky {
  public static void main(String[] args){
    Scanner s = new Scanner(System.in);
    int grammarCount = Integer.parseInt(s.nextLine());
    TreeMap<String, String[]> myMap = new TreeMap<>();

    // Loop through the # of grammars
    for (int index = 0; index < grammarCount; index++) {
      int nRules = Integer.parseInt(s.nextLine());

      // Take in the rules
      for (int i = 0; i < nRules; i++) {
        // Loop through each rule line
        String temp[] = s.nextLine().split(" ");
        int len = Integer.parseInt(temp[0]);
        String rules[] = new String[len];
        String rule = temp[1];

        // Since we know the first two chars of the line will be the size
        // and the start symbol we only need to store the n+2 items
        for (int j = 2; j < temp.length; j++) {
          rules[j-2] = temp[j];
        }

        // Store rules in map
        myMap.put(rule, rules);
      }

      // Take in strings to process
      int numStrings = Integer.parseInt(s.nextLine());
      String words[] =  new String[numStrings];

      System.out.println("Grammar #" + (index+1) + ":");
      for (int k = 0; k < numStrings; k++) {
        String result = "NO";
        words[k] = s.nextLine();
        if (stringBelongs(words[k], myMap, words[k].length())) {
          result = "YES";
        }
        System.out.println(words[k] + ": " + result);
      }
      System.out.println();
      myMap.clear();
    }
  }

  // Determines if a string belongs to a given CFG
  public static boolean stringBelongs(String word, TreeMap<String, String[]> myMap, int n) {
    // Check for empty string base case
    if (word.equals("@")) {
      boolean epiRule = false;
      String rules[] = myMap.get("S");
      for (int i = 0; i < rules.length; i++) {
        if (rules[i].equals("@")) {
          epiRule = true;
        }
      }

      return epiRule;
    }

    // Initialize table
    StringBuilder[][] table = new StringBuilder[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            table[i][j] = new StringBuilder(""); // Assign an empty string
        }
    }

    // Initialize our DP table
    char[] wordInChars = word.toCharArray();
    for (int i = 0; i < n; i++) {
      // Check every variable in rules for A -> b where b is some letter i in the word[]
      for (String key : myMap.keySet()) {
        String tRules[] = myMap.get(key);

        // Check every rule in variable A to see if it equals word[i]
        for (int j = 0; j < tRules.length; j++) {
          // We only want to check for rules of the form A -> b
          if (tRules[j].length() < 2) {
            String temp = String.valueOf(wordInChars[i]);

            // If A -> b we need to place it in our table
            if (temp.equals(tRules[j])) {
              // System.out.println(temp + " matches " + tRules[j]);
              if (table[i][i].toString().equals("")) {
                table[i][i].append(key);
              } else {
                table[i][i].append("," + key);
              }
            }
          }
        }
      }
    }

    // Phase 3
    for (int l = 2; l <= n; l++) {
      for (int i = 0; i <= n-l; i++) {
        int j = i+l-1;

        for (int k = i; k < j; k++) {
          // Check each rule for A -> BC type
          for (String key : myMap.keySet()) {
            String tRules[] = myMap.get(key);

            // Check every rule in variable A to see if it equals word[i]
            for (int index = 0; index < tRules.length; index++) {
              // We only want to check for rules of the form A -> BC
              // Since CNF guarentees that all variables are in the form A -> BC
              // We know we have to check the B and C
              if (tRules[index].length() > 1) {
                // Convert the string of len 2 into a char array
                char tWord[] = tRules[index].toCharArray();
                String firstHalf = String.valueOf(tWord[0]);
                String secondHalf = String.valueOf(tWord[1]);

                // If A ->BC and B belongs to i, k and C belongs in k+1, j we add the rule to the table
                if (table[i][k].toString().contains(firstHalf) && table[k+1][j].toString().contains(secondHalf)) {

                  // We check to make sure we're not adding duplicate rules
                  // Formatting to not add the , before the key
                  if (table[i][j].toString().equals("") && !table[i][j].toString().contains(key)) {
                    table[i][j].append(key);
                  } else if(!table[i][j].toString().contains(key)){
                    table[i][j].append("," + key);
                  }
                }
              }
            }
          }
        }
      }
    }

    // Check if we have an S in the last row first column
    if (table[0][n-1].toString().contains("S")) {
      return true;
    }
    return false;
  }
}
