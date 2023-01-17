//Noah Beightol, fall 2022, COP 3402
//Last edited 09/15/22
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//constant value for array size
int const ARRAY_SIZE = 500;

//struct for storing instructions
typedef struct instruction{
    int op;
    int lVal;
    int m;
} instruction;

//declaring all function prototypes
int base(int *pas, int BP, int L);

//main function
int main(int argc, char *argv[])
{

    //declaring needed variables
    int pas[ARRAY_SIZE];
    int bar[ARRAY_SIZE];
    int bp = 0, pc = 0, sp = 0, i = 0, halt;
    instruction ir;
    int stackCnt = 0;

    //setting all values in the array to 0 for the stack
    for(i = 0; i < ARRAY_SIZE; i++){
        pas[i] = 0;
        bar[i] = 0;
    }


    //creating new file and opening text file
    FILE *fp = fopen(argv[1], "r"); //note to self change to


    //making sure we successfully create or open a file
    if(fp == NULL){
        printf("We were unable to open the file :(\n");
        return 0;
    }



    //variables needed to control loop
    int index = 0, val = 0;

    //reading in values from file and storing them in our main array
    while(fscanf(fp, "%d", &val) != EOF)
    {
        pas[index] = val;
        //counter controls the indexing for the main array
        index++;
    }

    //closing file
    fclose(fp);


    //setting bp to the last input index
    bp = index;
    int start = bp;
    sp = bp - 1;
    halt = 1;


    //initial print
    printf("                  PC  BP  SP    stack\n");
    printf("Initial values: ");

    int j = 0;
    while(halt){
        ///////////////////////////////Begin Fetch Cycle/////////////////////////////////
        if(j == 0){
            printf("  %d   %d  %d\n", pc, bp, sp);
            j = 1;
        }
        int cur;
        //storing each value into the ir
        ir.op = pas[pc];
        cur = ir.op;
        ir.lVal = pas[pc + 1];
        ir.m = pas[pc + 2];

        //incrementing pc
        pc += 3;

        ////////////////////////////////Begin executable cycle/////////////////////////////
        switch(cur)
        {

            case 1: //LIT
            {
                bar[(sp - start) + 1] = 0;
                sp++;
                bar[(sp - start) + 1] = 1;
                pas[sp] = ir.m;

                //prints out the stack at this instance
                printf("     LIT %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                //each of these for loops control where the bar is placed
                for(int i = 0; i < (sp - start) + 1; i++){

                    if(bar[i] == 1)
                        printf("| %d ", pas[start + i]);
                    else
                        printf("%d ", pas[start + i]);
                }

                printf("\n");

                break;
            }
            case 2: //OPR
            {
                //switch for each OPR value
                switch(ir.m)
                {
                    case 0: //RTN
                    {
                        sp = bp - 1;
                        bp = pas[sp+2];
                        pc = pas[sp+3];
                        printf("     RTN %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                    for(int i = 0; i < (sp - start) + 1; i++){

                        if(bar[i] == 1)
                            printf("| %d ", pas[start + i]);
                        else
                            printf("%d ", pas[start + i]);
                    }

                    printf("\n");

                    break;
                    }
                    case 1: //ADD
                    {

                        pas[sp-1] = (pas[sp-1] + pas[sp]);

                        bar[(sp - start) + 1] = 0;
                        sp--; // sp = sp - 1
                        bar[(sp - start) + 1] = 1;

                        printf("     ADD %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                        for(int i = 0; i < (sp - start) + 1; i++){

                            if(bar[i] == 1)
                                printf("| %d ", pas[start + i]);
                            else
                                printf("%d ", pas[start + i]);
                        }

                        printf("\n");

                        break;
                    }
                    case 2: //SUB
                    {

                        pas[sp-1] = (pas[sp-1] - pas[sp]);

                        bar[(sp - start) + 1] = 0;
                        sp--;
                        bar[(sp - start) + 1] = 1;

                        printf("     SUB %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                        for(int i = 0; i < (sp - start) + 1; i++){

                            if(bar[i] == 1)
                                printf("| %d ", pas[start + i]);
                            else
                                printf("%d ", pas[start + i]);
                        }

                        printf("\n");

                        break;
                    }
                    case 3: //MUL
                    {
                        pas[sp-1] = (pas[sp-1] * pas[sp]);

                        bar[(sp - start) + 1] = 0;
                        sp--;
                        bar[(sp - start) + 1] = 1;

                        printf("     MUL %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                        for(int i = 0; i < (sp - start) + 1; i++){

                            if(bar[i] == 1)
                                printf("| %d ", pas[start + i]);
                            else
                                printf("%d ", pas[start + i]);
                        }

                        printf("\n");
                        break;
                    }
                    case 4: //DIV
                    {
                        pas[sp-1] = (pas[sp-1]/pas[sp]);

                        bar[(sp - start) + 1] = 0;
                        sp--;
                        bar[(sp - start) + 1] = 1;

                        printf("     DIV %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                        for(int i = 0; i < (sp - start) + 1; i++){

                            if(bar[i] == 1)
                                printf("| %d ", pas[start + i]);
                            else
                                printf("%d ", pas[start + i]);
                        }

                        printf("\n");

                        break;
                    }
                    case 5: //EQL
                    {
                        if(pas[sp-1] == pas[sp]){
                            bar[(sp - start) + 1] = 0;
                            sp--;
                            bar[(sp - start) + 1] = 1;
                        }

                        printf("     EQL %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                        for(int i = 0; i < (sp - start) + 1; i++){

                            if(bar[i] == 1)
                                printf("| %d ", pas[start + i]);
                            else
                                printf("%d ", pas[start + i]);
                        }

                        printf("\n");

                        break;
                    }
                    case 6: //NEQ
                    {
                        if(pas[sp-1] != pas[sp]){
                            bar[(sp - start) + 1] = 0;
                            sp--;
                        bar[(sp - start) + 1] = 1;
                        }

                        printf("     NEQ %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                        for(int i = 0; i < (sp - start) + 1; i++){

                            if(bar[i] == 1)
                                printf("| %d ", pas[start + i]);
                            else
                                printf("%d ", pas[start + i]);
                        }

                        printf("\n");
                        break;
                    }
                    case 7: //LSS
                    {
                        if(pas[sp-1] > pas[sp]){

                            bar[(sp - start) + 1] = 0;
                            sp--;
                            bar[(sp - start) + 1] = 1;

                            pas[sp] = 0;
                        }

                        printf("     LSS %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                        for(int i = 0; i < (sp - start) + 1; i++){

                            if(bar[i] == 1)
                                printf("| %d ", pas[start + i]);
                            else
                                printf("%d ", pas[start + i]);
                        }

                        printf("\n");
                        break;
                    }
                    case 8: //LEQ
                    {
                        if(pas[sp-1] <= pas[sp]){

                            bar[(sp - start) + 1] = 0;
                            sp--;
                            bar[(sp - start) + 1] = 1;
                        }

                        printf("     LEQ %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                        for(int i = 0; i < (sp - start) + 1; i++){

                            if(bar[i] == 1)
                                printf("| %d ", pas[start + i]);
                            else
                                printf("%d ", pas[start + i]);
                        }

                        printf("\n");
                        break;
                    }
                    case 9: //GTR
                    {
                        if(pas[sp-1] > pas[sp]){
                            bar[(sp - start) + 1] = 0;
                            sp--;
                            bar[(sp - start) + 1] = 1;
                        }

                        printf("     GTR %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                        for(int i = 0; i < (sp - start) + 1; i++){

                            if(bar[i] == 1)
                                printf("| %d ", pas[start + i]);
                            else
                                printf("%d ", pas[start + i]);
                        }

                        printf("\n");
                        break;
                    }
                    case 10: //GEQ
                    {
                        if(pas[sp-1] >= pas[sp]){
                            bar[(sp - start) + 1] = 0;
                            sp--;
                            bar[(sp - start) + 1] = 1;
                        }

                        printf("     GEQ %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                        for(int i = 0; i < (sp - start) + 1; i++){

                            if(bar[i] == 1)
                                printf("| %d ", pas[start + i]);
                            else
                                printf("%d ", pas[start + i]);
                        }

                        printf("\n");
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                break;
            }
            case 3: //LOD
            {
                bar[(sp - start) + 1] = 0;
                sp++;
                bar[(sp - start) + 1] = 1;

                pas[sp] = pas[base(pas, bp, ir.lVal) + ir.m];
                printf("     LOD %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                for(int i = 0; i < (sp - start) + 1; i++){

                    if(bar[i] == 1)
                        printf("| %d ", pas[start + i]);
                    else
                        printf("%d ", pas[start + i]);
                }

                printf("\n");

                break;
            }
            case 4: //STO
            {
                pas[base(pas, bp, ir.lVal) + ir.m] = pas[sp];

                bar[(sp - start) + 1] = 0;
                sp--;
                bar[(sp - start) + 1] = 1;

                printf("     STO %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                for(int i = 0; i < (sp - start) + 1; i++){

                    if(bar[i] == 1)
                        printf("| %d ", pas[start + i]);
                    else
                        printf("%d ", pas[start + i]);
                }

                    printf("\n");
                    break;
            }
            case 5: //CAL
            {
                //static link (SL)
                pas[sp+1] = base(pas,bp,ir.lVal);
                //dynamic link (RA)
                pas[sp+2] = bp;
                //return address (RA)
                pas[sp+3] = pc;
                bp = sp + 1;
                pc = ir.m;
                printf("     CAL %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                for(int i = 0; i < (sp - start) + 1; i++){

                    if(bar[i] == 1)
                        printf("| %d ", pas[start + i]);
                    else
                        printf("%d ", pas[start + i]);
                }

                printf("\n");

                break;
            }
            case 6: //INC
            {

                sp = sp + ir.m;
                bar[sp-start+1] = 1;

                printf("     INC %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);



                for(int i = 0; i < (sp - start) + 1; i++){
                    if(bar[i] == 1)
                        printf("| %d ", pas[start + i]);
                    else
                        printf("%d ", pas[start + i]);

                }
                printf("\n");
                break;
            }
            case 7: //JMP
            {
                pc = ir.m;
                printf("     JMP %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                for(int i = 0; i < (sp - start) + 1; i++){

                    if(bar[i] == 1)
                        printf("| %d ", pas[start + i]);
                    else
                        printf("%d ", pas[start + i]);
                }

                printf("\n");

                break;
            }
            case 8: //JPC
            {
                if(pas[sp] == 0)
                {
                    pc = ir.m;

                    bar[(sp - start) + 1] = 0;
                    sp--;
                    bar[(sp - start) + 1] = 1;
                }

                printf("     JPC %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                for(int i = 0; i < (sp - start) + 1; i++){

                    if(bar[i] == 1)
                        printf("| %d ", pas[start + i]);
                    else
                        printf("%d ", pas[start + i]);
                }

                printf("\n");

                break;
            }
            case 9:
            {
                //WRT
                if(ir.m == 1){
                    printf("Output result is %d\n", pas[sp]);
                    sp--;
                    printf("     WRT %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                for(int i = 0; i < (sp - start) + 1; i++){

                    if(bar[i] == 1)
                        printf("| %d ", pas[start + i]);
                    else
                        printf("%d ", pas[start + i]);
                }

                printf("\n");

                break;
                }
                //RED
                if(ir.m == 2){

                    bar[sp - start + 1] = 0;
                    sp++;

                    bar[sp - start + 1] = 1;

                    printf("Please enter an integer: ");
                    scanf("%d", &pas[sp]);
                    printf("     RED %d   %d    %d  %d  %d   ",ir.lVal,ir.m, pc, bp, sp);

                    for(int i = 0; i < (sp - start) + 1; i++){

                        if(bar[i] == 1)
                            printf("| %d ", pas[start + i]);
                        else
                            printf("%d ", pas[start + i]);
                    }

                    printf("\n");

                    break;
                }
                //HLT
                if(ir.m == 3){
                    halt = 0;
                    printf("     HTL %d   %d    %d  %d  %d  ",ir.lVal,ir.m, pc, bp, sp);

                    for(int i = 0; i < (sp - start) + 1; i++){

                        if(bar[i] == 1)
                            printf("| %d ", pas[start + i]);
                        else
                            printf("%d ", pas[start + i]);
                    }

                printf("\n");

                break;

                }

            }

        }

    }
    return 0;
}

//function for getting the lexicographical levels
int base(int *pas, int BP, int L)
{
    int arb = BP; // arb = activation record base
    while ( L > 0)     //find base L levels down
    {
        arb = pas[arb];
        L--;
    }
    return arb;
}
