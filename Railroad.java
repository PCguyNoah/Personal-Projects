// Noah Beightol

// Import statements
import java.util.*;
import java.io.*;

// We store the information for each route in these nodes:
class Node implements Comparable<Node> {
  public String source;
  public String destination;
  public int weight;

  // Implement the compareTo method so we can sort Nodes later
  @Override
  public int compareTo(Node other) {
     return Integer.compare(this.weight, other.weight);
  }
};

// Main method
public class Railroad {
  // Declaring needed variables
  int numTracks;
  int cost;
  String fileName;
  String [] track;
  List <Node> nodeArray = new ArrayList<>();

  // Constructor
  Railroad(int n, String fileN) {
    this.numTracks = n;
    this.fileName = fileN;

    // Reads file and sets the values into the array
    nodeArray = read(numTracks, fileName);
  }

  // This method computes cost efficient railroad system
  public String buildRailroad() {
    // Delclaring needed variables
    StringBuilder str = new StringBuilder();
    String result;
    int cost = 0;
    String parentSource;
    String parentDest;
    List<Node> mst = new ArrayList<>();
    Map<String, String> parent = new HashMap<>();
    Map<String, Integer> status = new HashMap<>();

    // Sort edges in ascending order
    Collections.sort(nodeArray);

    // kruskals algorithm:
    // Loop through each node in the node array
    for (Node n : nodeArray) {

      // Check if parent node is the destination
      if (!parent.containsKey(n.destination)) {
        // if not we put that node into the parent hash map
        parent.put(n.destination, n.destination);
        status.put(n.destination, 0);
      }
      // check if parent node is the source
      if (!parent.containsKey(n.source)) {
        // if not we put that node into the parent hash map
        parent.put(n.source, n.source);
        status.put(n.source, 0);
      }

      // Find the parent of each node
      parentSource = findParent(n.source, parent);
      parentDest = findParent(n.destination, parent);

      // Checks to make sure theyre not a loop and adds into the MST
      if (parentSource != parentDest) {
        mst.add(n);
        parent.put(parentSource, parentDest);

        // If source comes lexicographically before destination
        // We build that first in the string
        if (n.source.compareTo(n.destination) < 0) {
          str.append(n.source).append("---").append(n.destination).append("\t").append("$").append(n.weight).append("\n");
        } else {
          // Else list the destination in the string
          str.append(n.destination).append("---").append(n.source).append("\t").append("$").append(n.weight).append("\n");
        }

        // Update the total cost
        cost += n.weight;
      }
    }

    // Add on final cost to string
    str.append("The cost of the railroad is ").append("$").append(cost).append(".");
    result = str.toString();

    // Return fully built string
    return result;
  }

  // find parent of a specific Node
  public String findParent(String n, Map<String, String> parent) {
    // find parent of the node v

    // make sure parent doesnt contain the new node
    if (parent.get(n) != n) {
      parent.put(n, findParent(parent.get(n), parent));
    }
    return parent.get(n);
  }

  // Reads file and returns an array of positions and weights
  public List<Node> read(int num, String fileName) {
    // Needed variables
    List <Node> temp = new ArrayList<>();
    File myFile = new File(fileName);

    // Attempt to read file
    try {
      // Intialize new scanner object
      Scanner in = new Scanner(myFile);

      // Loop through file
      while (in.hasNextLine()) {
        String line = in.nextLine();
        Node n = new Node();

        // Splice the line whereever there is a space
        String[] split = line.split(" ");

        // Set values
        String str1 = split[0];
        String str2 = split[1];
        int num1 = Integer.parseInt(split[2]);

        // Store values in node
        n.source = str1;
        n.destination = str2;
        n.weight = num1;
        temp.add(n);
      }
    }
    // Catches any errors
    catch (IOException e) {
      e.printStackTrace();
    }

    // Return our list
    return temp;
  }
}
