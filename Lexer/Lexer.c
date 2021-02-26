/***** Libraries ******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lexer.h"

//----- Declarations des variables :

const char *programFile = "test.txt";    // "..\\program.cbl"
const char *lexOutput = "lexOutput.txt"; //"..\\program.lex"
const char *lexError = "lexError.txt";   //

int line = 1;

/* Main function */

int main()
{
    program = fopen(programFile, "r");
    output = fopen(lexOutput, "a");
    errors = fopen(lexError, "a");

    if (program == NULL || output == NULL || errors == NULL)
    {
        perror("Error while opening the file");
        exit(1);
    }

    do
    {
        NextChar();

        ignoreWhiteSpaces();
        firstTokenChar = ftell(program) - 1; // keep the position of first Token character
        ignoreComment();

        if (isalpha(currentChar))
        {
            getCurrentWord();

            // if one statement return true, then the condition is verified
            // without verifying the others
            if (isBloc() ||
                isDataType() ||
                isConditionOrLoop() ||
                isIdentifier())
                continue; // skip the other verification functions if token is found
        }
        else if (isdigit(currentChar))
        {
            if (isNumber())
                continue; // skip the other verification functions if token is found
        }
        else if (currentChar == '\'')
        {
            if (isCharacter())
                continue; // skip the other verification functions if token is found
        }
        else if (currentChar == '\"')
        {
            if (isString())
                continue; // skip the other verification functions if token is found
        }
        else
        {
            if (isSpecialSymb() ||
                isOperator())
                continue; // skip the other verification functions if token is found
        }

        if (currentChar != EOF)
        {
            LexError("Invalid Token");
        }
    } while (currentChar != EOF);

    fclose(program);
    fclose(output);
    fclose(errors);
    printf("\n\nFin du programme");
    return 1;
}

//----- Functions -------------- :

char NextChar()
{
    return currentChar = getc(program);
}

void saveToken(const char *token)
{
    //printf("%s_TOKEN\n", token);
    //fprintf(lex, "%s_TOKEN\n", token);
}

void LexError(const char *message)
{

    //fprintf(lex, "Line %d : %s\n", line, message);
    printf("Line %d : %s\n", line, message);
    while (NextChar() != '\n')
        ;
    //exit(1);
}

bool search_for_token(const char *word, const char **list, const char **listName, int size_of_list)
{
    for (int j = 0; j < size_of_list; j++)
    {
        if (strcmp(word, list[j]) == 0)
        {
            saveToken(listName[j]);
            return TRUE;
        }
    }
    return FALSE;
}

// to modify
void getCurrentWord()
{
    fseek(program, firstTokenChar, SEEK_SET); // return to first character in Token

    int len = 0;
    while (isalnum((currentWord[len] = NextChar())) && ++len <= MAXCHAR_WORD)
        ;

    if (len > MAXCHAR_WORD) // if the currentchar isn't alphabet
        LexError("Word doesn't respect the maximum size");

    ungetc(currentWord[len], program); // return back by one caractere in program file

    currentWord[len] = '\0'; // close the currentWord array
    sizeofCurrentWord = len; // keep the size of current word
}

void ignoreWhiteSpaces()
{
    // Ignore blank space, tabulation, newline
    while (currentChar == ' ' ||
           currentChar == '\t' ||
           currentChar == '\n')
    {
        if (currentChar == '\n')
            line++;

        NextChar();
    }
}

void ignoreComment()
{
    if (currentChar != 'c')
        return;

    if ((NextChar() == 'o') && (NextChar() == 'm') && (NextChar() == ':'))
    {
        while (((currentChar = NextChar()) != ';') && currentChar != EOF)
            if (currentChar == EOF)
                LexError("Invalid Comments");

        NextChar(); // ignore ;

        //printf("------- Comment\n");

        ignoreWhiteSpaces();
        firstTokenChar = ftell(program) - 1; // new Token so we keep track for the first character
    }

    fseek(program, firstTokenChar, SEEK_SET); // return to to first read c character
    NextChar();
}

// Valid it works well
bool isBloc()
{
    if (sizeofCurrentWord > SIZE_ELEMENT_BLOC)
        return FALSE;

    return search_for_token(currentWord, bloc_tokens, bloc_tokensName, SIZE_TOKENSLIST_BLOC);
}

bool isDataType()
{
    if (sizeofCurrentWord != SIZE_ELEMENT_DATATYPE)
        return FALSE;

    return search_for_token(currentWord, dataType_tokens, dataType_tokensName, SIZE_TOKENSLIST_DATATYPE);
}

bool isConditionOrLoop()
{
    if (sizeofCurrentWord > SIZE_ELEMENT_CONDITIONLOOP)
        return FALSE;

    return search_for_token(currentWord, conditionloop_tokens, conditionloop_tokensName, SIZE_TOKENSLIST_CONDITIONLOOP);
}

bool isReturn()
{
    if (sizeofCurrentWord != SIZE_OF_RETURN)
        return FALSE;
    if (strcmp(currentWord, "return") != 0)
        return FALSE;

    saveToken("RETURN");
    return TRUE;
}

bool isIdentifier()
{
    saveToken("ID");
    return TRUE;
}

bool isNumber()
{

    // We need to take into consideration - and +
    while (isdigit(NextChar()))
        ;
    if (currentChar == '.')
    {
        while (isdigit(NextChar()))
            ;

        if (currentChar == 'F' || currentChar == 'D')
            saveToken("NUM"); // Float or Double
        else
            LexError("Number not recognized");

        return TRUE;
    }

    if (currentChar == 'L')
    {
        saveToken("NUM"); // LONG
        return TRUE;
    }

    ungetc(currentChar, program); // return back with one char
    saveToken("NUM");             // INT
    return TRUE;
}

bool isString()
{
    while (NextChar() != '\"' && currentChar != EOF && currentChar != '\n')
        ;
    if (currentChar == EOF || currentChar == '\n')
        return FALSE;

    saveToken("STRING");
    return TRUE;
}

bool isCharacter()
{
    if (isalpha(NextChar()))
        if (NextChar() == '\'')
        {
            saveToken("CHAR");
            return TRUE;
        }

    LexError("Invalid Char");
}

bool isOperator()
{
    char operator[3];
    memset(operator, 0, sizeof(operator));

    operator[0] = currentChar;

    if ((operator[1] = NextChar()) != '=')
    {
        ungetc(currentChar, program);
        operator[1] = '\0';
    }

    return search_for_token(operator, operatorSymb_tokens, operatorSymb_tokensName, SIZE_TOKENSLIST_OPERATORSYMB);
}

bool isSpecialSymb()
{
    //
    char special[2];
    special[0] = currentChar;
    special[1] = 0; // close array

    return search_for_token(special, specialSymb_tokens, specialSymb_tokensName, SIZE_TOKENSLIST_SPECIALSYMB);
}