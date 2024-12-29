// Noah Beightol
// COT 4210
// Arup Guha
// Fall 2024

import java.util.*;
public class tm {
  static List<List<Map<Integer, String>>> stateList = new ArrayList<>();
  public static void main(String[] args){
    Scanner s = new Scanner(System.in);
    int tmCount = Integer.parseInt(s.nextLine());

    // Loop through each TM
    for (int index = 0; index < tmCount; index++) {
      // Handle program input //
      String firstLine[] = s.nextLine().split(" ");
      int numStates = Integer.parseInt(firstLine[0]);
      int numRules = Integer.parseInt(firstLine[1]);
      String [] rules = new String[numRules];

      // Collect all numStates
      int difStates = 0;
      int curSymbol = -1;

      // we need to calculate how many unique states there will be
      // excluding the accept/reject states
      for (int i = 0; i < numRules; i++) {
        rules[i] = s.nextLine();
        String tRules[] = rules[i].split(" ");
        int tmp = Integer.parseInt(tRules[0]);
        if (curSymbol != tmp) {
          difStates++;
        }
        curSymbol = tmp;
      }

      // account for the accept/reject states
      difStates = (difStates + 2);

      // Populate "Rules"
      for (int j = 0; j < difStates; j++) {
        // Data structure: List of lists, index of list is stored at the current state
        // current state represents the rule associated with it
        List<Map<Integer, String>> innerList = new ArrayList<>();
        // add accept state
        if (j == 1) {
          Map<Integer, String> map = new HashMap<>();
          map.put(j, "accept");
          innerList.add(map);
        }
        else if (j == 2) {
          // add reject state
          Map<Integer, String> map = new HashMap<>();
          map.put(j, "reject");
          innerList.add(map);
        }
        else {
          // If we dont add an accept or reject lets add the other rules
          for (int x = 0; x < numRules; x++) {
            // Find the first part of the rule holding the state number
            int fIndex = rules[x].indexOf(" ");
            String firstPart = rules[x].substring(0, fIndex);
            String secondPart = rules[x].substring(fIndex + 1);

            // We want to put all matching states together
            if (Integer.parseInt(firstPart) == j) {
              Map<Integer, String> map = new HashMap<>();
              map.put(j, secondPart);
              innerList.add(map);
            }
          }
        }
        // Add list of lists to our tape
        stateList.add(innerList);
      }

      // take in # of strings and max steps to allow
      String secondLine[] = s.nextLine().split(" ");
      int nWords = Integer.parseInt(secondLine[0]);
      int maxSteps = Integer.parseInt(secondLine[1]);
      String[] words = new String[nWords];

      System.out.println("Machine #" + (index+1) + ":");
      for (int k = 0; k < nWords; k++) {
        words[k] = s.nextLine();
        String res = isValid(words[k], rules, maxSteps);
        System.out.println(words[k] + ": " + res);
      }
      System.out.println();
      stateList.clear();
    }
  }

  public static String isValid(String word, String[] rules, int maxSteps) {
    // always start in q0
    int curState = 0, max = 0, tapeHead = 0;
    StringBuilder cmpHistory = new StringBuilder(word);

    // loop through the tm tape for only maxSteps
    while (max != maxSteps) {

      // check if were going to go "off" the tape head
      if (tapeHead >= word.length()) {
        cmpHistory.append("B");
      }

      // Current char were looking at on the tapeHead
      char c = cmpHistory.charAt(tapeHead);
      String[] curRule = new String[5];

      // Find current rule
      for (int i = 0; i < stateList.get(curState).size(); i++) {
        // Since we always store one rule in each map we need to grab the
        // rule at cur state, ith index, at rule curState
        String tRule = stateList.get(curState).get(i).get(curState);
        String rule[] = tRule.split(" ");

        // Find the rule that matches our current character on the string
        if (rule[0].equals(String.valueOf(c))) {
          curRule = rule;
        }
      }

      // Update current state and "write" new char on the cmp history
      curState = Integer.parseInt(curRule[1]);
      cmpHistory.setCharAt(tapeHead, curRule[2].charAt(0));

      // Check if we move to an accept/reject state
      if (curState == 1) {
        return "YES";
      }
      if (curState == 2) {
        return "NO";
      }
      // Check for left or right move
      if (curRule[3].equals("R")) {
        tapeHead++;
      } else if (curRule[3].equals("L") && tapeHead != 0){
        // Move left but not off the tape
        tapeHead--;
      }
      // Increment after each step
      max++;
    }

    if (max >= maxSteps) {
      return "DOES NOT HALT IN " + maxSteps + " STEPS";
    }
    return "NO";
  }
}
