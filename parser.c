 // Noah Beightol,COP 3402, Fall 2022, UCF ID 5388648
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 500
#define MAX_IDT_LEN 11

typedef enum token_type {
	identifier = 1, number, keyword_const, keyword_var, keyword_procedure,
	keyword_call, keyword_begin, keyword_end, keyword_if, keyword_then,
	keyword_else, keyword_while, keyword_do, keyword_read, keyword_write,
	keyword_def, period, assignment_symbol, minus, semicolon,
	left_curly_brace, right_curly_brace, equal_to, not_equal_to, less_than,
	less_than_or_equal_to, greater_than, greater_than_or_equal_to, plus, times,
	division, left_parenthesis, right_parenthesis
} token_type;

typedef enum opcode_name {
	LIT = 1, OPR = 2, LOD = 3, STO = 4, CAL = 5, INC = 6, JMP = 7, JPC = 8,
	SYS = 9, WRT = 1, RED = 2, HLT = 3,
	RTN = 0, ADD = 1, SUB = 2, MUL = 3, DIV = 4, EQL = 5, NEQ = 6,
	LSS = 7, LEQ = 8, GTR = 9, GEQ = 10
} opcode_name;

typedef struct lexeme {
	token_type type;
	char identifier_name[12];
	int number_value;
	int error_type;
} lexeme;

typedef struct instruction {
	int op;
	int l;
	int m;
} instruction;

typedef struct symbol {
	int kind;
	char name[12];
	int value;
	int level;
	int address;
	int mark;
} symbol;

lexeme *tokens;
int token_index = 0;
symbol *table;
int table_index = 0;
instruction *code;
int code_index = 0;

int error = 0;
int level;
//global count for read in tokens
int count = 0;

void emit(int op, int l, int m);
void add_symbol(int kind, char name[], int value, int level, int address);
void mark();
int multiple_declaration_check(char name[]);
int find_symbol(char name[], int kind);
void block();
void program();
int declarations();

void varFunc(int num_vars);
void constFunc();
void proc();
void statementFunc();
void factor();

void print_parser_error(int error_code, int case_code);
void print_assembly_code();
void print_symbol_table();

int main(int argc, char *argv[])
{
	// variable setup
	int i;
	tokens = calloc(ARRAY_SIZE, sizeof(lexeme));
	table = calloc(ARRAY_SIZE, sizeof(symbol));
	code = calloc(ARRAY_SIZE, sizeof(instruction));
	FILE *ifp;
	int buffer;

	// read in input
	/*
	if (argc < 2)
    {
        printf("Error : please include the file name\n");
        return 0;
    }
    */
    ifp = fopen("ptext.txt", "r");
    // argv[1]
	while(fscanf(ifp, "%d", &buffer) != EOF)
	{
		tokens[token_index].type = buffer;
		if (buffer == identifier)
			fscanf(ifp, "%s", tokens[token_index].identifier_name);
		else if (buffer == number)
			fscanf(ifp, "%d", &(tokens[token_index].number_value));
		token_index++;
		count++;
	}

	fclose(ifp);
	token_index = 0;

    // loop runs while there are no errors
    while(error != -1)
    {
        program();

        // manually ending loop if there is no errors
        error = -1;
    }

	free(tokens);
	free(table);
	free(code);
	return 0;
}

// starts program
void program()
{
    // adding main to the symbol table first
    add_symbol(3, "main", 0, 0,0);

    //setting our current level
    level = -1;

    // we have to emit the first function and jmp straight to the main function
    emit(JMP, table[table_index].level, 0);
    block();
    for(int i = 0; i < code_index; i++)
    {
        if(code[i].op == CAL)
        {
            code[i].m = table[i].address;
        }
    }

    if(tokens[token_index].type != period)
    {
        print_parser_error(1, 1);
        error = -1;
    }
    // for each cal in code blah blah
    int j = 0;
    for(int i = 0; i < code_index; i++)
    {
        if(code[i].op == STO || code[i].op == LIT || code[i].op == RED)
        {
            j++;
        }
        if(code[i].op == CAL)
        {
            printf("\n TEST: %d \n", j);
            code[i].m = table[j].address;
        }
    }

    emit(SYS, 0 ,HLT);

    table[0].address = code_index * 2;
    code[0].m = code_index * 2;

    // final print
    print_assembly_code();
    print_symbol_table();
}

void block()
{

    level++;
    // first call
    int inc_m_val = declarations();

    //call procedure
    proc();

    table[code_index].address = code_index * 3;
    //emitting INC call
    emit(INC, 0, inc_m_val);

    statementFunc();

    // marks all visited symbols at this level
    mark();
    level--;
}

int declarations()
{
    // # of vars to pass in
    int numVars = 0;
    // loop while a const or var
    while(tokens[token_index].type == keyword_const || tokens[token_index].type == keyword_var)
    {
        // if its a const we call const function
        if(tokens[token_index].type == keyword_const)
        {
            constFunc();
        }
        // its a var call var function
        if(tokens[token_index].type == keyword_var)
        {
            varFunc(numVars);
            numVars++;
        }
    }
    // remove
    // returns current ar level
    return numVars + 3;
}

void varFunc(int num_vars)
{
    char name[MAX_IDT_LEN];
    // process var
    token_index++;

    // checking if value after var is an identifer
    if(tokens[token_index].type != identifier)
    {
        print_parser_error(2,2);
        error = -1;
    }
    // checks if variable is unique
    if(multiple_declaration_check(tokens[token_index].identifier_name) != -1)
    {
        // print error and end program
        print_parser_error(3, 3);
        error = -1;
    }

    // saving name and moving to next token
    strcpy(name,tokens[token_index].identifier_name);
    token_index++;

    // adding previous identifier to symbol table
    add_symbol(2, name, 0, level, num_vars+3);

    // making sure next symbol is a semiolon
    if(tokens[token_index].type != semicolon)
    {
        print_parser_error(6, 2);
        error = -1;
    }
    token_index++;
}

void constFunc()
{
    // 0 = false, 1 = true
    int minus_flag = 0;
    char name[MAX_IDT_LEN];

    //move to next token
    token_index++;

    //check if next token is valid
    if(tokens[token_index].type != identifier)
    {
        print_parser_error(2,1);
        error = -1;
    }

    // checks if variable is unique
    if(multiple_declaration_check(tokens[token_index].identifier_name) != -1)
    {
        // print error and end program
        print_parser_error(3, 3);
        error = -1;
    }

    // saving name and moving to next token
    strcpy(name,tokens[token_index].identifier_name);
    token_index++;

    // makes sure next symbol is valid
    if(tokens[token_index].type != assignment_symbol)
    {
        print_parser_error(4, 1);
        error = -1;
    }

    // moves to next token
    token_index++;

    // checks if next token is a minus
    if(tokens[token_index].type == minus)
    {
        minus_flag = 1;
        token_index++;
    }
    // checks for valid next token
    if(tokens[token_index].type != number)
    {
        print_parser_error(5, 0);
        error = -1;
    }

    // making value negative in the symbol table
    if(minus_flag == 1)
        tokens[token_index].number_value = tokens[token_index].number_value * -1;

    // adding to symbol table
    add_symbol(1, name, tokens[token_index].number_value, level, 0);

    // move to next symbol
    token_index++;
    // makes sure current value is a semicolon
    if(tokens[token_index].type != semicolon)
    {
        print_parser_error(6, 1);
        error = -1;
    }
    // move to next symbol
    token_index++;
}

void proc()
{
    // while we are on a procedure
    while(tokens[token_index].type == keyword_procedure)
    {
        char name[MAX_IDT_LEN];
        token_index++;
        // making sure next token is valid
        if(tokens[token_index].type != identifier)
        {
            print_parser_error(2, 3);
            error = -1;
        }

        // checks if variable is unique
        if(multiple_declaration_check(tokens[token_index].identifier_name) != -1)
        {
            // print error and end program
            print_parser_error(3, 3);
            error = -1;
        }
        // saving name and moving to next token
        strcpy(name,tokens[token_index].identifier_name);
        token_index++;

        add_symbol(3, name, 0, level, 0);

        // checks for validity
        if(tokens[token_index].type != left_curly_brace)
        {
            print_parser_error(14, 14);
            error = -1;
        }
        token_index++;
        block();

        emit(OPR, 0, RTN);

        // checks for validity
        if(tokens[token_index].type != right_curly_brace)
        {
            print_parser_error(15, 1);
            error = -1;
        }
        // move to next token
        token_index++;
    }
}

void statementFunc()
{
    int sym_index = 0;
    if(tokens[token_index].type == keyword_def)
    {
        // move to next token
        token_index++;

        // checking next token validity
        if(tokens[token_index].type != identifier)
        {
            print_parser_error(2, 6);
            error = -1;
        }

        sym_index = find_symbol(tokens[token_index].identifier_name, 2);

        // if we cant find symbol in our table
        if(sym_index == -1)
        {
            if(find_symbol(tokens[token_index].identifier_name, 1) == find_symbol(tokens[token_index].identifier_name, 3))
            {
                print_parser_error(8, 1);
                error = -1;
            }
            else
            {
                print_parser_error(7, 7);
                error = -1;
            }
        }
        // move to the next token
        token_index++;

        // checking for validity
        if(tokens[token_index].type != assignment_symbol)
        {
            print_parser_error(4, 2);
            error = -1;
        }

        // move to next token
        token_index++;

        //call factor
        factor();

        emit(STO, (level - table[sym_index].level), table[sym_index].address);
    }
    else if(tokens[token_index].type == keyword_call)
    {
        token_index++;

        // checking next token validity
        if(tokens[token_index].type != identifier)
        {
            print_parser_error(2, 4);
            error = -1;
        }

        // locating symbol
        sym_index = find_symbol(tokens[token_index].identifier_name, 3);

        // if we cant find the symbol
        if(sym_index == -1)
        {
            // temp variables hold our symbols
            int num1 = find_symbol(tokens[token_index].identifier_name, 1);
            int num2 = find_symbol(tokens[token_index].identifier_name, 2);

            // checking if there isnt a constant and no variable with the name
            if(num1 == num2)
            {
                print_parser_error(8, 2);
                error = -1;
            }
            else
            {
                print_parser_error(9, 9);
                error = -1;
            }
        }
        // moving to the next token
        token_index++;
        printf("test");
        emit(CAL,(level - table[table_index].level), sym_index);
        printf("%d", code[code_index - 1].m);
    }
    else if(tokens[token_index].type == keyword_begin)
    {
        do
        {
            token_index++;
            statementFunc();
        }while(tokens[token_index].type == semicolon);

        if(tokens[token_index].type != keyword_end)
        {
            if(tokens[token_index].type == identifier || tokens[token_index].type == keyword_call
               || tokens[token_index].type == keyword_read || tokens[token_index].type == keyword_def)
            {
                print_parser_error(6, 3);
                error = -1;
            }
            else
            {
                print_parser_error(10, 10);
                error = -1;
            }
        }
        token_index++;
    }
    else if(tokens[token_index].type == keyword_read)
    {
        // moving to next token
        token_index++;

        // checking next token validity
        if(tokens[token_index].type != identifier)
        {
            print_parser_error(2, 5);
            error = -1;
        }
        // finding current symbol
        sym_index = find_symbol(tokens[token_index].identifier_name, 2);

        // if we don;t find it
        if(sym_index == -1)
        {
            // temp variables hold our symbols
            int num1 = find_symbol(tokens[token_index].identifier_name, 1);
            int num3 = find_symbol(tokens[token_index].identifier_name, 3);

            // checking if there isnt a constant and no variable with the name
            if(num1 == num3)
            {
                print_parser_error(8, 3);
                error = -1;
            }
            else
            {
                print_parser_error(13, 13);
                error = -1;
            }
        }
        // moving to next token
        token_index++;

        emit(SYS, 0, RED);
        emit(STO, level - table[sym_index].level, table[sym_index].address);
    }
}

void factor()
{
    // checking validity
    if(tokens[token_index].type == identifier)
    {
        // temp variables
        int const_index = find_symbol(tokens[token_index].identifier_name, 1);
        int var_index = find_symbol(tokens[token_index].identifier_name, 2);

        if(const_index == var_index)
        {
            // checking if there is a valid procedure
            if(find_symbol(tokens[token_index].identifier_name, 3) != -1)
            {
                print_parser_error(17, 17);
                error = -1;
            }
            else
            {
                print_parser_error(8, 4);
                error = -1;
            }
        }
        if(const_index == -1)
        {
            emit(LOD, level - table[var_index].level, table[var_index].address);
        }
        else if(var_index == -1)
        {
            emit(LIT, 0, table[const_index].value);
        }
        else if(table[const_index].level > table[var_index].level)
        {
            emit(LIT, 0, table[const_index].value);
        }
        else
        {
            emit(LOD, level - table[var_index].level, table[var_index].address);
        }

        // move to next token
        token_index++;
    }
    else if(tokens[token_index].type == number)
    {
        emit(LIT, 0, tokens[token_index].number_value);
        token_index++;
    }
    else
    {
        print_parser_error(19, 19);
        error = -1;
    }

}

// adds a new instruction to the end of the code
void emit(int op, int l, int m)
{
	code[code_index].op = op;
	code[code_index].l = l;
	code[code_index].m = m;
	code_index++;
}

// adds a new symbol to the end of the table
void add_symbol(int kind, char name[], int value, int level, int address)
{
	table[table_index].kind = kind;
	strcpy(table[table_index].name, name);
	table[table_index].value = value;
	table[table_index].level = level;
	table[table_index].address = address;
	table[table_index].mark = 0;
	table_index++;
}

// marks all of the current procedure's symbols
void mark()
{
	int i;
	for (i = table_index - 1; i >= 0; i--)
	{
		if (table[i].mark == 1)
			continue;
		if (table[i].level < level)
			return;
		table[i].mark = 1;
	}
}

// returns -1 if there are no other symbols with the same name within this procedure
int multiple_declaration_check(char name[])
{
	int i;
	for (i = 0; i < table_index; i++)
		if (table[i].mark == 0 && table[i].level == level && strcmp(name, table[i].name) == 0)
			return i;
	return -1;
}

// returns the index of the symbol with the desi name and kind, prioritizing
// 		symbols with level closer to the current level
int find_symbol(char name[], int kind)
{
	int i;
	int max_idx = -1;
	int max_lvl = -1;
	for (i = 0; i < table_index; i++)
	{
		if (table[i].mark == 0 && table[i].kind == kind && strcmp(name, table[i].name) == 0)
		{
			if (max_idx == -1 || table[i].level > max_lvl)
			{
				max_idx = i;
				max_lvl = table[i].level;
			}
		}
	}
	return max_idx;
}

void print_parser_error(int error_code, int case_code)
{
	switch (error_code)
	{
		case 1 :
			printf("Parser Error 1: missing . \n");
			break;
		case 2 :
			switch (case_code)
			{
				case 1 :
					printf("Parser Error 2: missing identifier after keyword const\n");
					break;
				case 2 :
					printf("Parser Error 2: missing identifier after keyword var\n");
					break;
				case 3 :
					printf("Parser Error 2: missing identifier after keyword procedure\n");
					break;
				case 4 :
					printf("Parser Error 2: missing identifier after keyword call\n");
					break;
				case 5 :
					printf("Parser Error 2: missing identifier after keyword read\n");
					break;
				case 6 :
					printf("Parser Error 2: missing identifier after keyword def\n");
					break;
				default :
					printf("Implementation Error: unrecognized error code\n");
			}
			break;
		case 3 :
			printf("Parser Error 3: identifier is declared multiple times by a procedure\n");
			break;
		case 4 :
			switch (case_code)
			{
				case 1 :
					printf("Parser Error 4: missing := in constant declaration\n");
					break;
				case 2 :
					printf("Parser Error 4: missing := in assignment statement\n");
					break;
				default :
					printf("Implementation Error: unrecognized error code\n");
			}
			break;
		case 5 :
			printf("Parser Error 5: missing number in constant declaration\n");
			break;
		case 6 :
			switch (case_code)
			{
				case 1 :
					printf("Parser Error 6: missing ; after constant declaration\n");
					break;
				case 2 :
					printf("Parser Error 6: missing ; after variable declaration\n");
					break;
				case 3 :
					printf("Parser Error 6: missing ; after statement in begin-end\n");
					break;
				default :
					printf("Implementation Error: unrecognized error code\n");
			}
			break;
		case 7 :
			printf("Parser Error 7: procedures and constants cannot be assigned to\n");
			break;
		case 8 :
			switch (case_code)
			{
				case 1 :
					printf("Parser Error 8: undeclared identifier used in assignment statement\n");
					break;
				case 2 :
					printf("Parser Error 8: undeclared identifier used in call statement\n");
					break;
				case 3 :
					printf("Parser Error 8: undeclared identifier used in read statement\n");
					break;
				case 4 :
					printf("Parser Error 8: undeclared identifier used in arithmetic expression\n");
					break;
				default :
					printf("Implementation Error: unrecognized error code\n");
			}
			break;
		case 9 :
			printf("Parser Error 9: variables and constants cannot be called\n");
			break;
		case 10 :
			printf("Parser Error 10: begin must be followed by end\n");
			break;
		case 11 :
			printf("Parser Error 11: if must be followed by then\n");
			break;
		case 12 :
			printf("Parser Error 12: while must be followed by do\n");
			break;
		case 13 :
			printf("Parser Error 13: procedures and constants cannot be read\n");
			break;
		case 14 :
			printf("Parser Error 14: missing {\n");
			break;
		case 15 :
			printf("Parser Error 15: { must be followed by }\n");
			break;
		case 16 :
			printf("Parser Error 16: missing relational operator\n");
			break;
		case 17 :
			printf("Parser Error 17: procedures cannot be used in arithmetic\n");
			break;
		case 18 :
			printf("Parser Error 18: ( must be followed by )\n");
			break;
		case 19 :
			printf("Parser Error 19: invalid expression\n");
			break;
		default:
			printf("Implementation Error: unrecognized error code\n");

	}
}

void print_assembly_code()
{
	int i;
	printf("Assembly Code:\n");
	printf("Line\tOP Code\tOP Name\tL\tM\n");
	for (i = 0; i < code_index; i++)
	{
		printf("%d\t%d\t", i, code[i].op);
		switch(code[i].op)
		{
			case LIT :
				printf("LIT\t");
				break;
			case OPR :
				switch (code[i].m)
				{
					case RTN :
						printf("RTN\t");
						break;
					case ADD : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("ADD\t");
						break;
					case SUB : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("SUB\t");
						break;
					case MUL : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("MUL\t");
						break;
					case DIV : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("DIV\t");
						break;
					case EQL : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("EQL\t");
						break;
					case NEQ : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("NEQ\t");
						break;
					case LSS : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("LSS\t");
						break;
					case LEQ : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("LEQ\t");
						break;
					case GTR : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("GTR\t");
						break;
					case GEQ : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("GEQ\t");
						break;
					default :
						printf("err\t");
						break;
				}
				break;
			case LOD :
				printf("LOD\t");
				break;
			case STO :
				printf("STO\t");
				break;
			case CAL :
				printf("CAL\t");
				break;
			case INC :
				printf("INC\t");
				break;
			case JMP :
				printf("JMP\t");
				break;
			case JPC : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("JPC\t");
				break;
			case SYS :
				switch (code[i].m)
				{
					case WRT : // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
						printf("WRT\t");
						break;
					case RED :
						printf("RED\t");
						break;
					case HLT :
						printf("HLT\t");
						break;
					default :
						printf("err\t");
						break;
				}
				break;
			default :
				printf("err\t");
				break;
		}
		printf("%d\t%d\n", code[i].l, code[i].m);
	}
	printf("\n");
}

void print_symbol_table()
{
	int i;
	printf("Symbol Table:\n");
	printf("Kind | Name        | Value | Level | Address | Mark\n");
	printf("---------------------------------------------------\n");
	for (i = 0; i < table_index; i++)
		printf("%4d | %11s | %5d | %5d | %5d | %5d\n", table[i].kind, table[i].name, table[i].value, table[i].level, table[i].address, table[i].mark);
	printf("\n");
}
