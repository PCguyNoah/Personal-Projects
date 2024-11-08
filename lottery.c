//Noah Beightol, Arup Guha, 2/25/22
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//testing flag
int const TEST = 1;
#define MAX 100000

typedef struct People{
    int num;
    struct People* next;
}People;

//struct group
typedef struct Group{
    int groupID;
    int numPeeps;
    int skipNum;
    int threshold;
    int winner;
    struct People* peeps;
}Node;

void Populate(Node* array, int size);
Node* GetGroup();
People* GetPeople();
//main function
int main()
{
    //declaring needed variables and allocating memory for root Node aka group #1
    int userInput;

    //testing
    if(TEST == 1)
        printf("Enter # of test cases\n");
    //taking # of test cases
    scanf("%d,", &userInput);

    //this loop runs the program for C test cases
    while(userInput != 0)
    {
        GetLottery();
        userInput--;
    }

    return 0;
}

//makes groups
void GetLottery()
{
    //declaring all needed variables
    int numGroups;
    //testing flag
    if(TEST == 1)
        printf("Enter # Groups\n");
    //taking in # groups
    scanf("%d", &numGroups);

    //creating array of structs

    Node* myGroups[numGroups];

    for(int i = 0; i < numGroups; i++)
    {
        //taking in # people, skip #, and threshold #
        Node* tempGroup = GetGroup();
        //assigns group #
        tempGroup->groupID = i+1;
        //adding the group to the array of groups
        myGroups[i] = tempGroup;
        int num = tempGroup->numPeeps;
    }

    //creates linked lists for each
    for(int j = 0; j < numGroups; j++)
    {
        //creates linked list for each of the groups
        Node* temp = myGroups[j];
        CreateLinkedList(temp);
        //SkipFunction(temp);
        PrintInfo(temp);
        PrintALL(temp);
    }
    //would print out winner here
    printf("Lottery winner is person #n/a from group n/a\n");


}

void CreateLinkedList(Node* group)
{
    //finding the size of each group
    int size = group->numPeeps;
    Populate(group, size);
    //testing
}

//creates groups
Node* GetGroup()
{
    //declaring all needed variables
    int tempP;
    int tempSkip;
    int tempThresh;

    if(TEST == 1)
            printf("Enter # people, Skip #, and Threshold #\n");
    scanf("%d %d %d", &tempP, &tempSkip, &tempThresh);

    Node* newGroup = malloc(sizeof(Node));
    newGroup->numPeeps = tempP;
    newGroup->skipNum = tempSkip;
    newGroup->threshold = tempThresh;

    return newGroup;
}

//populates the linked list
void Populate(Node* array, int size)
{
    //declaring first node in linked list
    People* root = malloc(sizeof(People));
    root = GetPeople(NULL);

    for(int i = 1; i < size+1; i++)
    {
        //creates person
        People* newPerson = GetPeople(root);
        //assigns number to each person
        newPerson->num = i+1;
        //inserts them into linked list
        //InsertPeople(root, newPerson);
    }
    array->peeps = root;

}

//creates the person
People* GetPeople(People* front)
{
    int num = 1;
    People* iter;
    People* newPerson = malloc(sizeof(People));
    newPerson->num = num;

    //base case for begining of linked list
    if(front == NULL)
    {
        newPerson->next = newPerson;
    }
    //adding to an already created list
    else
    {
        newPerson->next = front;
        iter = front;
        while(iter->next != front)
        {
            iter = iter->next;
        }
        iter->next = newPerson;
    }
    return newPerson;
}

//inserts each struct into the linked list
void InsertPeople(People* root, People* insertMe)
{
    //setting the root equal to the current
    People* currentPeep = root;
    while(currentPeep->next != NULL)
    {
        currentPeep = currentPeep->next;
    }
    currentPeep->next = insertMe;
}

//skips function
void SkipFunction(Node* group)
{
    //declaring all variables
    int size = group->numPeeps;
    int skip = group->skipNum;
    int thresh = group->threshold;
    People* root = group->peeps;
    People* currentNode = root;
    People* previous = root;

    while(size != thresh)
    {
        printf("test\n");
        if(previous->next = previous)
        {
            root = NULL;
            return;
        }
        while(previous->next != root)
        {
            previous = previous->next;
        }
        previous->next = currentNode->next;
        printf("end \n");
        root = previous->next;
        free(currentNode);
        size--;
    }


    return;
}


//prints out the numbers
void PrintALL(Node* array)
{
    //setting the root equal to a temp variable
    People* root = array->peeps;
    People* currentNode = root;

    while(currentNode->next != root)
    {
        printf("%d\n", currentNode->num);
        currentNode = currentNode->next;
    }
    printf("\n");

}


//final out put
void PrintInfo(Node* array)
{
    printf("Group #%d\n", array->groupID);
}

//freeing linked list
void FreeLinked(People* root)
{
    People* currentNode = root;
    while(currentNode != NULL)
    {
        free(currentNode->num);
        free(currentNode);
        currentNode = currentNode->next;
    }
}
//freeing indivudal nodes
void FreeMe(People* root)
{
    free(root->num);
    free(root);
}

