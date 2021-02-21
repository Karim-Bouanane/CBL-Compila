
#include <stdio.h>
#include <stdlib.h>

#include "Lexer.c"

//----- Declarations des variables :

const char *programFile = "test.txt"; // "..\\program.cbl"
const char *outputLex = "test.lex";   //"..\\program.lex"

/* Main function */

int main()
{
    program = fopen(programFile, "r");
    lex = fopen(outputLex, "a");

    if (program == NULL || lex == NULL)
    {
        perror("Error while opening the file");
        exit(1);
    }

    do
    {
        NextChar();

        ignoreWhiteSpaces();
        //printf("after whitespaces %c\n", currentChar);
        firstTokenChar = ftell(program) - 1; // keep the position of first Token character
        ignoreComment();

        //printf("after Comments %c\n", currentChar);

        if (isalpha(currentChar))
        {
            //printf("Case : Alphabet\n");
            getCurrentWord();

            // if one statement return true, then the condition is verified
            // without verifying the others
            if (isBloc() ||
                isDataType() ||
                isConditionOrLoop() ||
                isReturn() ||
                isIdentifier())
                continue;
        }
        else if (isdigit(currentChar))
        {
            //printf("Case : Number \n");
            if (isNumber())
                continue; // skip the other verification functions
        }
        else if (currentChar == '\'')
        {
            if (isCharacter())
                continue;
        }
        else if (currentChar == '\"')
        {
            if (isString())
                continue;
        }
        else
        {
            //printf("Case :Special symb\n");
            if (isSpecialSymb() ||
                isOperator())
                continue;
        }

        LexError("Invalid Token");
    } while (currentChar != EOF);

    fclose(program);
    fclose(lex);
    printf("\n\n\n\tFin");
    return 1;
}
