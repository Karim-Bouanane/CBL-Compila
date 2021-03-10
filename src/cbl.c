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
    char commandLex[50] = "cd Lexer && Lexer.exe ";
    char commandSyntax[50] = "cd Suntax && syntax.exe ";

    if (argc == 2) // check user give the name of program to compile
    {
        if (access(argv[1], F_OK) == 0) // program file exist
        {
            // Get current directory path and put it inside ""
            char currentDirPath[256];
            char programPath[256] = "\0";

            getcwd(currentDirPath, sizeof(currentDirPath));

            strcat(programPath, "\"");
            strcat(programPath, currentDirPath);
            strcat(programPath, "\\");
            strcat(programPath, argv[1]);
            strcat(programPath, "\"");

            printf("program %s\n", programPath);

            // Phase for lexical analyzer

            strcat(commandLex, programPath);

            if (system(commandLex) == -1) // if error occur while executing lexical analyzer
            {
                perror("An error occur when executing lexical analyzer\n");
                exit(1);
            }

            FILE *lexErrorsFile = fopen("errors.txt", "r"); //./Lexer/errors.txt

            if (!isempty(lexErrorsFile)) // If lexical errors exist, print them and exit the program
            {
                printf("Try to solve lexical errors\n\n");
                printErrors(lexErrorsFile);
                fclose(lexErrorsFile);
                exit(1);
            }

            // Phase for syntax analyzer

            strcat(commandSyntax, programPath);

            if (system(commandSyntax) == -1) // if error occur while executing lexical analyzer
            {
                perror("An error occur when executing syntaxic analyzer\n");
            }

            FILE *SyntaxErrorsFile = fopen("./Syntax/errors.txt", "r");

            if (!isempty(SyntaxErrorsFile)) // If syntaxic errors exist, print them and exit the program
            {
                printf("Try to solve syntax errors\n\n");
                printErrors(SyntaxErrorsFile);
                fclose(SyntaxErrorsFile);
                exit(1);
            }

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
    char line[50];

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s\n", line);
    }
}