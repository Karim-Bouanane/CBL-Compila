/***** Libraries ******/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Definition */

typedef enum
{
    FALSE,
    TRUE
} bool;

/* Function Prototype */

bool isempty();
void printErrors();

/* Main function */

int main(int argc, char *argv[])
{
    char commandLex[50] = "Lexer.exe ";
    char commandSyntax[50] = "Syntax.exe ";

    if (argc == 2) // check user give the name of program to compile
    {
        if (access(argv[1], F_OK) == 0) // program file exist
        {

            /*** Phase for lexical analyzer ***/

            strcat(commandLex, argv[1]);

            if (system(commandLex) == -1) // if error occur while executing lexical analyzer
            {
                perror("An error occur when executing lexical analyzer\n");
                exit(1);
            }

            FILE *lexErrorsFile = fopen("LexErrors", "r");

            if (!isempty(lexErrorsFile)) // If lexical errors exist, print them and exit the program
            {
                printf("\n Failed Compilation \n ");
                printf("Try to solve lexical errors: \n");
                printErrors(lexErrorsFile);

                // remove files of the output of lexical analyser
                fclose(lexErrorsFile);
                remove("LexErrors");
                remove("Tokens");
                exit(1);
            }

            fclose(lexErrorsFile);
            remove("LexErrors");

            /*** Phase for syntax analyzer ***/

            strcat(commandSyntax, argv[1]);

            if (system(commandSyntax) == -1) // if error occur while executing lexical analyzer
            {
                perror("An error occur when executing syntaxic analyzer\n");
            }

            FILE *SyntaxErrorsFile = fopen("SyntErrors", "r");

            if (!isempty(SyntaxErrorsFile)) // If syntaxic errors exist, print them and exit the program
            {
                printf("\n Failed Compilation \n ");
                printf("Try to solve syntax errors: \n");
                printErrors(SyntaxErrorsFile);

                // remove syntax analyser output files when finishing of them
                fclose(SyntaxErrorsFile);
                remove("SyntErrors");
                remove("Tokens");
                exit(1);
            }

            fclose(SyntaxErrorsFile);
            remove("Tokens");
            remove("SyntErrors");

            printf("Success compilation\n");
        }
        else // program file doesn't exist
        {
            printf("File not found in current repertory\n");
        }
    }
    else if (argc > 2)
    {
        printf("Too many arguments supplied.\n");
    }
    else
    {
        printf("One argument expected.\n");
    }
}

bool isempty(FILE *fp)
{
    if (NULL != fp)
    {
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);

        if (0 == size)
        {
            return TRUE;
        }

        return FALSE;
    }
}

void printErrors(FILE *fp)
{
    fseek(fp, 0, SEEK_SET);
    char line[50];

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s\n", line);
    }
}