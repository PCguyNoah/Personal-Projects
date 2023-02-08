// Noah Beightol, COP 3402, Fall 2022 UCF ID: 5388648
// Team members: Daniel Moshovetis

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// defined constraints
#define MAX_CHAR_LEN 11
#define MAX_NUM_LEN 5

//declaring all functions
char* CleanStrings(char* word, int len, int numWords);
int FindWord(char *word);

// definition of USABLE variables throughout code
typedef enum tokens
{
    identifier = 1,
    number = 2,
    keyword_const = 3,
    keyword_var = 4,
    keyword_procedure = 5,
    keyword_call = 6,
    keyword_begin = 7,
    keyword_end = 8,
    keyword_if = 9,
    keyword_then = 10,
    keyword_else = 11,
    keyword_while = 12,
    keyword_do = 13,
    keyword_read = 14,
    keyword_write = 15,
    keyword_def = 16,
    period = 17,
    assignment_symbol = 18,
    minus = 19,
    semicolon = 20,
    left_curly_brace = 21,
    right_curly_brace = 22,
    equal_to = 23,
    not_equal_to = 24,
    less_than = 25,
    less_than_or_equal_to = 26,
    greater_than = 27,
    greater_than_or_equal_to = 28,
    plus = 29,
    times = 30,
    division = 31,
    left_parenthesis = 32,
    right_parenthesis = 33,
    invalid = 999,
    error = 666,
} tokens;

int myIndex = 0;
int tokenArray[1000];
char* array[10000];
int masterCheck = 0;

int main(int argc, char *argv[])
{
    //declaring variables
    int numWords = 0, i = 0;
    char word[20];
    char word2[20];

    //creating new file and opening text file
    FILE *fp = fopen(argv[1], "r");

    //making sure we successfully create or open a file
    if(fp == NULL){
        printf("We were unable to open the file :(\n");
        return 0;
    }

    // grabs each word from file
    while(fscanf(fp, "%s", word) != EOF)
    {

        //TODO needs work actually ignoring comments and the words associated to them
        // comments should start with the character "#' and end with a '\n' terminator
        // haven't figured out how to check for new line when reading in
        if(word[0] == '#')
        {
            fscanf(fp, "%*[^\n]\n");
        }
        else
        {
            int len = strlen(word);
            array[numWords] = (char*)malloc(sizeof(char) * len+1);

            char* temp = CleanStrings(word, len, numWords);
            strcpy(array[numWords], word);

            // checks if there is a semicolon attached, if so we have to add it to the array of words
            if(masterCheck == -1){
                //allocates memory for new word at the next index
                array[numWords+1] = (char*)malloc(sizeof(char));

                //copies it in and updates word count and resets master checker
                strcpy(array[numWords+1], ";");
                numWords++;
                masterCheck = 0;
            }
            // checks if a period is attached, if so we need to add it to the array of words too
            if(masterCheck == -2){
                //allocates memory for new word at the next index
                array[numWords+1] = (char*)malloc(sizeof(char));

                //copies it in and updates word count and resets master checker
                strcpy(array[numWords+1], ".");
                numWords++;
                masterCheck = 0;
            }

            numWords++;
            myIndex++;
        }
    }

    // Printing out all words and tokens
    printf("Lexeme List:\n");
    printf("lexeme      token type\n");
    for(i = 0; i < myIndex; i++)
    {
        int length = strlen(array[i]) + 1;
        // checking if invalid name

        if(tokenArray[i] == 2 && length > MAX_NUM_LEN)
        {
            printf("Lexical Analyzer Error: maximum number length is 5\n");
            continue;
        }
        if(tokenArray[i] == 1 && length > MAX_CHAR_LEN)
        {
            printf("Lexical Analyzer Error: maximum identifier length is 11\n");
            continue;
        }
        if(tokenArray[i] < 0)
        {
            printf("Lexical Analyzer Error: identifiers cannot be named 'null' or 'main'\n");
            continue;
        }
        if(tokenArray[i] == invalid)
        {
            printf("Lexical Analyzer Error: invalid symbol\n");
            continue;
        }
        if(tokenArray[i] == error)
        {
            printf("Lexical Analyzer Error: identifiers cannot begin with digits\n");
        }
        else
        {
            printf("    %s    %d \n",array[i], tokenArray[i]);
        }

    }

    //closing file
    fclose(fp);
    return 0;
}


// takes in a string and removes any of the unwanted characters
// updates token Array
char* CleanStrings(char* word, int len, int numWords)
{

    // iterate over word to check for special character
    for(int i = 0; i < len+1; i++){
        // if char is any of these we need to remove it and keep track of it
        if(word[i] == ';'){
            //removes semi colon from word
            word[len-1] = '\0';

            // check calls the word identifier to determine what it should be in the array
            int check = FindWord(word);

            //storing the word BEFORE the semicolon
            tokenArray[myIndex] = check;

            // important to add at this index since the word needs to be stored before it in just index
            tokenArray[myIndex+1] = semicolon;

            // important to update global index and master checker
            masterCheck = -1;
            myIndex++;
            return NULL;
        }
        if(word[i] == '.'){
            //removes period from word
            word[len-1] = '\0';

            // check calls the word identifier to determine what it should be in the array
            int check = FindWord(word);

            //storing the word BEFORE the period
            tokenArray[myIndex] = check;

            // important to add at this index since the word needs to be stored before it in just index
            tokenArray[myIndex+1] = period;

            // important to update global index and master checker
            masterCheck = -2;
            myIndex++;
            return NULL;
        }

    }

    // if none of the special cases are met, we just figure out which type of word it is and add it to the token array
    int check = FindWord(word);
    // storing token at correct index
    tokenArray[myIndex] = check;

    return word;
}

// function returns an integer value based on the word
// NOTE: should be completely done, dont mess with for loop at the bottom
int FindWord(char *word)
{
    if(strcmp(word, "else") == 0)
        return keyword_else;
    if(strcmp(word, "begin") == 0)
        return keyword_begin;
    if(strcmp(word, "end") == 0)
        return keyword_end;
    if(strcmp(word, "if") == 0)
        return keyword_if;
    if(strcmp(word, "then") == 0)
        return keyword_then;
    if(strcmp(word, "while") == 0)
        return keyword_while;
    if(strcmp(word, "do") == 0)
        return keyword_do;
    if(strcmp(word, "call") == 0)
        return keyword_call;
    if(strcmp(word, "const") == 0)
        return keyword_const;
    if(strcmp(word, "var") == 0)
        return keyword_var;
    if(strcmp(word, "procedure") == 0)
        return keyword_procedure;
    if(strcmp(word, "read") == 0)
        return keyword_read;
    if(strcmp(word, "write") == 0)
        return keyword_write;
    if(strcmp(word, "def") == 0)
        return keyword_def;
    if(strcmp(word,";") == 0)
        return semicolon;
    if(strcmp(word, ":=") == 0)
        return assignment_symbol;
    if(strcmp(word, "+") == 0)
        return plus;
    if(strcmp(word, ".") == 0)
        return period;
    if(strcmp(word,"==") == 0)
        return equal_to;
    if(strcmp(word, "<>") == 0)
        return not_equal_to;
    if(strcmp(word, "<") == 0)
        return less_than;
    if(strcmp(word, "<=") == 0)
        return less_than_or_equal_to;
    if(strcmp(word, ">") == 0)
        return greater_than;
    if(strcmp(word, ">=") == 0)
        return greater_than_or_equal_to;
    if(strcmp(word, "*") == 0)
        return times;
    // BUG program crashes every time we scan a minus symbol
    if(strcmp(word, "-") == 0)
        return minus;
    if(strcmp(word, "/") == 0)
        return division;
    if(strcmp(word, "{") == 0)
        return left_curly_brace;
    if(strcmp(word, "}") == 0)
        return right_curly_brace;
    if(strcmp(word, "(") == 0)
        return left_parenthesis;
    if(strcmp(word, ")") == 0)
        return right_parenthesis;
    if(strcmp(word, "null") == 0)
        return -1;
    if(strcmp(word, "main") == 0)
        return -2;
    if(strcmp(word,"%") == 0)
        return invalid;
    if(strcmp(word,"?") == 0)
        return invalid;
    if(strcmp(word,"^") == 0)
        return invalid;
    if(strcmp(word,"&") == 0)
        return invalid;
    if(strcmp(word,"$") == 0)
        return invalid;
    if(strcmp(word,"@") == 0)
        return invalid;
    if(isdigit(word[0]) == 1 && strlen(word+1) > 5)
    {
        for(int i = 1; i < 5; i++)
        {
            if(isdigit(word[i]) == 0)
                return error;
        }
    }
    //checks if its a number
    for(int i = 0; i < strlen(word); i++)
        if(isdigit(word[i]) != 0)
            return number;
    else
        return identifier;
}
