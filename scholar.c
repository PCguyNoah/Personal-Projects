//Noah Beightol, Arup Guha, 3/21/2022
#include  <stdlib.h>
#include <stdio.h>
#include <string.h>

//testing flag
int const TEST = 0;

//main function
int main()
{
    //declaring all needed variables
    int numBooks;
    long long numPages;
    int start = 0;
    int count = 0;
    int maxPages = 0;

    //testing flag
    if(TEST == 1)
        printf("Enter # of books and # of pages willing to read\n");

    //taking in # of books and # of pages willing to read
    scanf("%d %lld", &numBooks, &numPages);

    //allocating memory for array of size n
    int *myArray = malloc(sizeof(int) * numBooks);

    //Scanning in all of the books into the array
    for(int i = 0; i < numBooks; i++)
    {
        int temp;
        //testing flag
        if(TEST == 1)
            printf("Enter book\n");
        //taking in the book as well as putting it into the array
        scanf("%d", &temp);
        myArray[i] = temp;
    }
    //running merge sort function to sort our array
    MergeSort(myArray, start, numBooks-1);

    //traversing the array and finding total number of books we can have
    for(int j = 0; j < numBooks; j++)
    {
        //temporarily storing a book in this variable
        int temp = 0;
        temp = myArray[j];

        //adding up the number of books
        maxPages = maxPages + myArray[j];

        //making sure the total pages read does not exceed the # of pages willing to read
        if(maxPages > numPages)
            break;
        if(temp <= numPages)
        {
            count++;
        }

    }

    //printing final answer
    printf("%d ", count);
}

//this function takes in the array of books and conducts merge sort
void MergeSort(int myArray[], int start, int end)
{
    //declaring all needed variables
    int mid;
    //Check if our sorting range is more than one element.
    if (start < end) {

        //finding mid point
        mid = (start+end)/2;
        // sorting the first half of the array
        MergeSort(myArray, start, mid);
        //sorting second half of array
        MergeSort(myArray, mid+1, end);
        //merging arrays together
        Merge(myArray, start, mid+1, end);
    }
}

//this function merges the sorted arrays together
void Merge(int values[], int start, int mid, int end)
{
    //declaring all needed variables
    int *temp;
    int i;
    int length;
    int cnt1;
    int cnt2;
    int mergeCount;

    //allocating memory for needed arraysa
    length = end - start + 1;
    temp = (int*)calloc(length, sizeof(int));

    //creating indexes for our arrays
    cnt1 = start;
    cnt2 = mid;
    mergeCount = 0;

    //copying over values into new arrays
    while ((cnt1 < mid) || (cnt2 <= end))
    {
        if (cnt2 > end || (cnt1 < mid && values[cnt1] < values[cnt2])) {
            temp[mergeCount] = values[cnt1];
            cnt1++;
            mergeCount++;
        }
        else
        {
            //copying the next value into the new array
            temp[mergeCount] = values[cnt2];
            cnt2++;
            mergeCount++;
        }
    }
    // Copy back all of our values into the original array.
    for (i=start; i<=end; i++)
        values[i] = temp[i - start];
    //freeing memory
    free(temp);
}
