//Name: Noah Beightol
//UCF ID: 5388648
//Instructor: Arup Guha
//1/16/2022
//This program allows a user to input a certain number of card decks, and outputs the # of ascending sequences
//and same suit sequences.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DECK 104
#define HALF 52

//declaring all functions
int GetSameSuit();
int GetAscending();

//this is the main function
int main()
{
    //this variable will control how many times the loop executes
    int userInput;
    //taking in user input
    scanf("%d", &userInput);
    //making sure users input is less than 25
    if(userInput > 25)
    {
        scanf("%d", &userInput);
    }

    //this for loop runs everything needed to sort and print out the # of ascending and same suit sequences.
    for(int i = 0; i < userInput; i++)
    {
        //declaring these strings in order to take in the deck 1 line at a time
        char line1[HALF];
        //scanning in input
        scanf("%s", line1);

        char line2[HALF];
        //scanning in input
        scanf("%s", line2);


        //declaring the full deck that we will actually use
        char mainDeck[DECK];


        //copying over each piece of the deck into the main deck
        strcpy(mainDeck, line1);
        strcat(mainDeck, line2);

        //creating a int variable to store the highest ascending and same suit, while also running their respective functions
        int totalSuit = GetSameSuit(mainDeck);
        printf("%d", totalSuit);

        int totalAsc = GetAscending(mainDeck);
        printf(" %d \n", totalAsc);
    }
    return 0;

}

//this function goes through the deck and returns the largest ascending sequence
int GetAscending(char mainDeck[DECK])
{

    //declaring the needed ints
    int max = 1;
    int b = 1;
    int controller = 2;

    //this loop will find the largest ascending sequence and return it to main
    while(controller < DECK)
    {
        //declaring temporary arrays to iterate through
        //we subtract 2 in order to make sure it compares the first element to the second element
        char testCase1 = mainDeck[controller - 2];
        char testCase2 = mainDeck[controller];

        if(testCase1 == 'J')
        {
            if(testCase2 == 'Q')
            b = b + 1;
        }
            else if(testCase1 == 'Q')
            {
                if(testCase2 == 'K')
                    b = b + 1;
            }
            else if(testCase1 == 'K')
            {
                if(testCase2 == 'A')
                    b = b + 1;
            }
            else if(testCase1 == 'A')
            {
                if(testCase2 == '2')
                    b = b + 1;
            }
            else if(testCase1 == 'T')
            {
                if(testCase2 == 'J')
                    b = b + 1;
            }
            else if(testCase1 == '9')
            {
                if(testCase2 == 'T')
                    b = b + 1;
            }
            else if(testCase1 !='T' && testCase1 !='J' && testCase1 !='Q' && testCase1 !='K' && testCase1 != 'A' && testCase2 !='A' && testCase2 !='T' && testCase2 != 'J' && testCase2 !='Q' && testCase2 !='K' && (int)testCase1 ==(int)testCase2 - 1)
            {
                b = b + 1;
            }
            else
                b = 1;
            // Largest number in variable
            if(max < b)
                max = b;
                controller = controller + 2;
            }

            return max;
}



int GetSameSuit(char mainDeck[DECK])
{
    //declaring the needed ints
    int max = 1;
    int count = 1;
    int controller = 3;

    //this loop checks to see if the 2nd letter is same as the 4th letter and so on
    while(controller < DECK)
    {
        //if the next letter is the same as the first we add to the count
        if(mainDeck[controller] == mainDeck[controller - 2])
        {
            count = count + 1;
        }
        else
            count = 1;

        if(max < count)
            //this is now the largest number
        max = count;
        controller = controller + 2;
        }
        //returning the max number
        return max;
    }










