//Noah Beightol
//UCF ID: 5388648
//Arup Guha
//2/11/22

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 16

//defining struct to hold cordinates
typedef struct Cords{
    int x;
    int y;
    int k;
}Cords;

//testing flag
const int TEST = 0;

//defining all function
void GetCords();
int runPerms(int n, Cords myCord[MAX]);
int GetPerms(int perm[], int used[], int k, int n, Cords myCord[MAX]);
void GetDistance(int array[], int n, Cords myCord[MAX]);
double myDist[1000];

//main
int main()
{
    //declaring all variables
    int count;
    int userInput;
    if(TEST == 1)
        printf("Enter number of test cases\n");
    //taking number of bridges
    scanf("%d", &userInput);
    //this loop controls the entire program
    while(userInput != 0)
    {
        GetCords();
        userInput--;
    }
    return 0;

}

//taking in users coordinates
void GetCords()
{
    //declaring all variables used for this function
    int numTrees;
    int tempSize;
    double res = 1000000000;
    Cords myCord[MAX];

    //testing flag
    if(TEST == 1)
        printf("Enter # of trees\n");
    scanf("%d", &tempSize);

    //making it "2n"
    numTrees = (tempSize*2);

    //taking in users coordinates
    for(int i = 0; i < numTrees; i++)
    {
        if(TEST == 1)
            printf("Enter coordinates\n");
        scanf("%d %d", &myCord[i].x, &myCord[i].y);
    }
    //testing flag
    if(TEST == 1)
        printf("Here are the distances\n");

    //this function calculates the distance between two trees and adds them to an array
    int count = runPerms(numTrees, myCord);
    for(int j = 0; j < count; j++)
    {
        if(myDist[j] == 0)
            continue;
        if(myDist[j] < res)
            res = myDist[j];
    }
    //final print with lowest number
    printf("%.3lf\n", res);

}

//this function runs the permuation and distance functions
int runPerms(int n, Cords myCord[MAX])
 {
    //declaring all variables needed
    int perm[n];
    int used[n];
    double total;

    for (int i = 0; i < n; i++)
    {
        used[i] = 0;
    }
    total = GetPerms(perm, used, 0, n, myCord);
    printf("\n");
    //returning the count
    return total;
}

//this function controls and creates different combinations of coordinates
int GetPerms(int perm[], int used[], int k, int n, Cords myCord[MAX])
{
    //variable controls the loop later on in GetCords()
    int count;
    // Base case.
    if (k == n)
    {
        GetDistance(perm, n, myCord);

    }
    // Recursive case - fill in slot k.
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (!used[i])
            {
                used[i] = 1;
                perm[k] = i;
                GetPerms(perm, used, k+1, n, myCord);
                used[i] = 0;
                count++;
            }
        }
    }
    //returns counter for GetCords()
    return count;

}
//this function calculates the distance
void GetDistance(int array[], int n, Cords myCord[MAX])
{
    //declaring all variables needed for this function
    double dist;
    double arrDist[2];
    double tempTotal = 0;
    for (int i = 0; i < n; i+=2)
    {
        //setting permutated number to k in struct
        int permNum = array[i];
        myCord[i].k = permNum;
        //declaring all int values needed
        int xOne, xTwo, yOne, yTwo;
        //copying over permuted number in the struct to new temp variables
        xOne = myCord[array[i]].x;
        yOne = myCord[array[i]].y;
        xTwo = myCord[array[i+1]].x;
        yTwo = myCord[array[i+1]].y;

        //calculating distance
        dist = sqrt(pow((xOne - xTwo), 2) + pow((yOne - yTwo), 2));
        //testing flag
        if(TEST == 1)
            printf("%d - %d + %d - %d = %.3lf\n", xOne, xTwo, yOne, yTwo, dist);
        tempTotal = tempTotal + dist;
    }
    //adding total distance to array for later calculations
    for(int j = 0; j < n; j++)
    {
        myDist[j] = tempTotal;
    }
}
