// Noah Beightol
// COT 4210
// Arup Guha
// Fall 2024

import java.util.*;
import java.awt.Point;

// Takes in a DFA and returns the minimized version using SudKamp DFA
// minimization algorithm
public class dfamin {
  public static HashMap<Integer, String> aStates = new HashMap<Integer, String>();
  public static HashMap<Integer, String> newAcceptStates = new HashMap<Integer, String>();
  public static void main(String[] args){
    Scanner s = new Scanner(System.in);
    int dfaCount = Integer.parseInt(s.nextLine());

    // Loop through each DFA
    for (int index = 0; index < dfaCount; index++) {
      String[] dfaProps = s.nextLine().split(" ");
      int startState = 0;
      int numStates = Integer.parseInt(dfaProps[0]);
      int alphabetSize = Integer.parseInt(dfaProps[1]);
      String[] acceptedStates = s.nextLine().split(" ");
      int[][] array = new int[numStates][alphabetSize];
      int numAccStates = Integer.parseInt(acceptedStates[0]);

      // Take in lamda transitions
      for (int i = 0; i < numStates; i++) {
        String[] transition = s.nextLine().split(" ");
        for (int j = 0; j < alphabetSize; j++) {
          array[i][j] = Integer.parseInt(transition[j]);
        }
      }

      // Use a hash map to mark accept states
      for (int i = 1; i < numAccStates + 1; i++) {
        aStates.put(Integer.parseInt(acceptedStates[i]), "valid");
      }

      // Remove non reachable states and get the new transitions array
      // Get new accepted states as well
      Set<Integer> reachableStates = findReachableStates(array, startState);
      int[][] newTransitions = removeNonReachableStates(array, reachableStates);
      int[][] finalizedTransitions = runMinimization(newTransitions, alphabetSize);

      // Final output
      System.out.println("DFA #" + (index + 1) + ":");
      System.out.println(finalizedTransitions.length + " " + alphabetSize);
      System.out.print(aStates.size() + " ");
      System.out.println(String.join(" ", aStates.keySet().stream().map(String::valueOf).toArray(String[]::new)));
      for (int i = 0; i < finalizedTransitions.length; i++) {
          for (int j = 0; j < finalizedTransitions[0].length; j++) {
            System.out.print(finalizedTransitions[i][j] + " ");
          }
          System.out.println();
      }
      System.out.println();
      // Empty our Hashmaps for next iteration
      aStates.clear();
      newAcceptStates.clear();
    }
  }

  // Sudkamp DFA minimization
  public static int[][] runMinimization(int[][] transitions, int alphabetSize) {
    // Needed variables
    int len = transitions.length;
    boolean[][] d = new boolean[len][len];
    ArrayList<ArrayList<HashSet<Point>>> s =  new ArrayList<ArrayList<HashSet<Point>>>();

    // Initialize s and d
    for (int i = 0; i < len; i++) {
      ArrayList<HashSet<Point>> tempList = new ArrayList<HashSet<Point>>();
      for (int j = 0; j < len; j++) {
        d[i][j] = false;
        tempList.add(new HashSet<Point>());
      }
      s.add(tempList);
    }

    // Mark pairs where one state is accepting and the other is not as distinguishable
    for (int i = 0; i < len; i++) {
      for (int j = i + 1; j < len; j++) {
        if (newAcceptStates.containsKey(i) != newAcceptStates.containsKey(j)) {
            d[i][j] = true;
        }
      }
    }

    // Step 3
    for (int i = 0; i < len; i++) {
      for (int j = i + 1; j < len; j++) {

        // Only check current undistinguishable states
        if (!d[i][j]) {
          // Check every letter in the alphabet
          for (int a = 0; a < alphabetSize; a++) {
            int m = transitions[i][a];
            int n = transitions[j][a];

            // Check if m, n is distinguishable
            if (d[m][n] || d[n][m]) {
              // Call Dist Function
              dist(d, s, i, j);
              break;
            }
            else {
              // Make sure i,j != m,n
              boolean mLess = (i == m && j == n);
              boolean nLess = (i == n && j == m);

              // If not lets add them to S[m][n].add[i][j]
              if (m < n && !mLess) {
                s.get(m).get(n).add(new Point(i, j));
              }
              else if (m > n && !nLess) {
                // Lets add them to S[n][m].add[j][i]
                s.get(n).get(m).add(new Point(i, j));
              }
            }
          }
        }
      }
    }
    // merge all indistinguishable states and rename states
    List<Set<Integer>> mergedStateGroups = mergeStates(d, len);
    int[][] finalizedTransitions = renumberStates(mergedStateGroups, transitions, alphabetSize);

    // Return final table
    return finalizedTransitions;
  }

  // DIST marks a pair of states as distinguishable
  public static void dist(boolean[][] d, ArrayList<ArrayList<HashSet<Point>>> s, int i, int j) {
      // Base case
      if (d[i][j]) {
        return;
      }

      // Set our current i and j to visited
      d[i][j] = true;
      d[j][i] = true;
      for (Point mn : s.get(i).get(j)) {
          // Recursively call on the next m and n
          dist(d, s, mn.x, mn.y);
      }
  }

  // Merge function
  public static List<Set<Integer>> mergeStates(boolean[][] d, int len) {
      boolean[] isMerged = new boolean[len];
      List<Set<Integer>> states = new ArrayList<>();

      // Loop through all our states
      for (int i = 0; i < len; i++) {
          if (!isMerged[i]) {
              Set<Integer> temp = new HashSet<>();
              temp.add(i);
              isMerged[i] = true;

              // Check for states that can be merged with i
              for (int j = i + 1; j < len; j++) {
                  if (!d[i][j]) {
                      temp.add(j);
                      isMerged[j] = true;
                  }
              }
              states.add(temp);
          }
      }
      // Return updated states
      return states;
  }

  // Renumbering function
  public static int[][] renumberStates(List<Set<Integer>> states, int[][] transitions, int alphabetSize) {
      // Sort our states into lowest first
      states.sort(Comparator.comparingInt(state -> Collections.min(state)));

      // recycle old HashMap
      aStates.clear();

      // Update accepted states table
      for (Set<Integer> state : states) {
        // check if we have the first value in our accepted states
        int accepted = Collections.min(state);
        if (newAcceptStates.containsKey(accepted) && !aStates.containsKey(accepted)) {
          aStates.put(accepted, "valid");
        }
      }

      // Update mapping
      Map<Integer, Integer> stateMapping = new HashMap<>();
      for (int index = 0; index < states.size(); index++) {

          // Loop through each state group
          for (int prevState : states.get(index)) {
              stateMapping.put(prevState, index);
          }
      }

      // Create our new transistions table
      int[][] newTransitions = new int[states.size()][alphabetSize];
      for (int i = 0; i < transitions.length; i++) {
          int newState = stateMapping.get(i);

          // Go through and check each of the transitions in our alphabet
          for (int a = 0; a < alphabetSize; a++) {
              int target = transitions[i][a];
              newTransitions[newState][a] = stateMapping.get(target);
          }
      }

      // Return our new transisitons
      return newTransitions;
  }

  // BFS algorithm to find all reachable states
  public static Set<Integer> findReachableStates(int[][] array, int startState) {
      Queue<Integer> q = new LinkedList<>();
      Set<Integer> vis = new HashSet<>();

      // Our queue
      q.add(startState);
      // Visisted
      vis.add(startState);

      // BFS traversal
      while (!q.isEmpty()) {
          int currentState = q.poll();

          // Explore all transitions
          for (int nextState : array[currentState]) {
              if (!vis.contains(nextState)) {
                  vis.add(nextState);
                  q.add(nextState);
              }
          }
      }
      // Return the set of reachable states
      return vis;
  }

  // Function to remove non reachable states from the transitions array
  public static int[][] removeNonReachableStates(int[][] array, Set<Integer> reachableStates) {
      List<int[]> filteredArray = new ArrayList<>();
      Map<Integer, Integer> stateRemapping = new HashMap<>();

      // Create a mapping from old state indices to new continuous indices
      int newStateIndex = 0;
      for (int state : reachableStates) {
          stateRemapping.put(state, newStateIndex++);
      }

      // Filter and remap the transitions array
      for (int state : reachableStates) {
          int[] newArray = new int[array[state].length];
          for (int i = 0; i < array[state].length; i++) {
              // Check if the current state is an accept state and if we have
              // already added it to our hashmap
              if ((aStates.containsKey(array[state][i])) && !(newAcceptStates.containsKey(array[state][i]))) {
                newAcceptStates.put(stateRemapping.get(array[state][i]), "valid");
              }
              newArray[i] = stateRemapping.get(array[state][i]);
          }
          filteredArray.add(newArray);
      }

      // Convert the filtered transitions list to a 2D array
      return filteredArray.toArray(new int[0][0]);
  }
}
