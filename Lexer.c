/***** Libraries ******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Lexer.h"

//----- Declarations des variables :

const char *programFile = ".\\program.cbl";
const char *outputLex = ".\\program.lex";

int firstTokenChar;
char currentChar;
char *currentWord;

FILE *program;
FILE *lex;

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

    NextChar();
    while (currentChar != EOF)
    {
        ignoreWhiteSpaces();
        //ignoreComments();
        firstTokenChar = ftell(program) - 1; // keep the position of first Token character

        if (isalpha(currentChar))
        {
            // if one statement return true, then the condition is verified
            // without verifying the others
            if (isBloc() ||
                isDataType() ||
                isConditionOrLoop() ||
                isIdentifier())
                continue;
        }
        else if (isdigit(currentChar))
        {
            if (isNumber())
                continue;
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
            if (isOperator() ||
                isSpecialSymb())
                continue;
        }

        LexError("Invalid Token");
    }

    free(currentWord);
    fclose(program);
    fclose(lex);
    printf("\n\n\n\tFin");
    return 1;
}

//----- Functions -------------- :

char NextChar()
{
    return currentChar = getc(program);
}

void saveToken(const char *token)
{
    fprintf(lex, "%s_TOKEN ", token);
}

bool search_for_token(const char *word, const char *list, int size_of_list)
{
    for (int j = 0; j < size_of_list; j++)
    {
        if (strcmp(word, list[j]) == 0)
        {
            saveToken(bloc_tokens[j]);
            return TRUE;
        }
    }
    return FALSE;
}

char *getCurrentWord(int max_size)
{
    currentWord = (char *)realloc(currentWord, max_size);
    int i = 0;

    while (isalpha(currentWord[i] = NextChar()) && ++i <= max_size)
        ;
    currentWord[i] = '\0';
}

void LexError(const char *message)
{
    printf("%s\n", message);
}

void ignoreWhiteSpaces()
{
    // Ignore blank space, tabulation, newline
    while (currentChar == ' ' ||
           currentChar == '\t' ||
           currentChar == '\n')
    {
        NextChar();
    }
}

void ignoreComment()
{
    if (currentChar != 'c' && NextChar() != 'o' && NextChar() != 'm' && NextChar() != ':')
        return;

    while ((currentChar == NextChar()) != ';' && currentChar != EOF)
        if (currentChar == EOF)
            LexError("Invalid Comments");

    ignoreWhiteSpaces();
}

bool isBloc()
{
    fseek(program, firstTokenChar, SEEK_SET); // return to first character in Token

    char *blocName = getCurrentWord(SIZE_ELEMENT_BLOC);

    return search_for_token(blocName, bloc_tokens, SIZE_TOKENSLIST_BLOC);
}

bool isDataType()
{
    fseek(program, firstTokenChar, SEEK_SET); // return to first character in Token

    char *dataType = getCurrentWord(SIZE_ELEMENT_DATATYPE);

    return search_for_token(dataType, dataType_tokens, SIZE_TOKENSLIST_DATATYPE);
}

bool isConditionOrLoop()
{
    fseek(program, firstTokenChar, SEEK_SET); // return to first character in Token

    char *keyword = getCurrentWord(SIZE_ELEMENT_DATATYPE);

    return search_for_token(keyword, conditionloop_tokens, SIZE_TOKENSLIST_CONDITIONLOOP);
}

bool isIdentifier()
{
    fseek(program, firstTokenChar, SEEK_SET); // return to first character in Token

    while (isalphanum(NextChar()))
        ;

    saveToken("ID");
    return TRUE;
}

bool isNumber()
{
    fseek(program, firstTokenChar, SEEK_SET); // return to first character in Token

    // We need to take into consideration - and +
    while (isdigit(NextChar()))
        ;
    if (currentChar == '.')
    {
        while (isdigit(NextChar()))
            ;
        saveToken("FLOAT");
        return TRUE;
    }

    saveToken("INT");
    return TRUE;
}

bool isString()
{
    while (NextChar() != '\"' && currentChar != EOF)
        ;

    if (currentChar == EOF)
        return FALSE;

    return TRUE;
}

bool isCharacter()
{
    if (isalpha(NextChar()))
        if (NextChar() == '\'')
            return TRUE;

    LexError("Invalid Char");
    // either to exit the program or skip the error
}

bool isOperator()
{
    char operator[3];
    memset(operator, '\0', sizeof(operator));

    operator[0] = currentChar;

    if ((operator[1] = NextChar()) != '=')
        operator[1] = '\0';

    return search_for_token(operator, operatorSymb_tokens, SIZE_TOKENSLIST_OPERATORSYMB);
}

bool isSpecialSymb()
{
    fseek(program, firstTokenChar, SEEK_SET); // return to first character in Token
    char special = NextChar();
    return search_for_token(special, specialSymb_tokens, SIZE_TOKENSLIST_SPECIALSYMB);
}