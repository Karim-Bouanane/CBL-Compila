
#ifndef LEXER_H_
#define LEXER_H_

#include <ctype.h>
#include <string.h>
#include <stdio.h>

/***** Définition ******/

#define MAXDIGIT_NUMBER 30
#define MAXCHAR_STRING 100
#define MAXCHAR_WORD 20
#define SIZE_OF_RETURN 6

/***** Déclaration des Variables Globales ******/

char currentWord[MAXCHAR_WORD];
int sizeofCurrentWord;
int firstTokenChar;
char currentChar;

FILE *program;
FILE *output;
FILE *errors;

typedef enum
{
    FALSE,
    TRUE
} bool;

/***** Prototype des Fonctions ******/

char NextChar();

void LexError(const char *message);
void saveToken(const char *token);
void ignoreWhiteSpaces();
void ignoreComment();
void getCurrentWord();

bool search_for_token(const char *word, const char **list, const char **listName, int size_of_list);
bool isBloc();
bool isReturn();
bool isDataType();
bool isConditionOrLoop();
bool isIdentifier();
bool isNumber();
bool isString();
bool isCharacter();
bool isOperator();
bool isSpecialSymb();

/***** Déclarations des Tokens ******/

/* Tokens des mots clés de la structure du programme */
const char *bloc_tokensName[] =
    {"LIBRARIES", "LIB", "H", "CONST", "VAR", "FUNC", "MAIN", "RETURN"};
const char *bloc_tokens[] =
    {"Libraries", "lib", "h", "Constants", "Variables", "Functions", "Main", "return"};

// Size of programStructure_tokens list
#define SIZE_ELEMENT_BLOC 10
#define SIZE_TOKENSLIST_BLOC sizeof(bloc_tokens) / sizeof(bloc_tokens[0])

/* Tokens des type de données */
const char *dataType_tokensName[] =
    {"LIST", "FILE"};
const char *dataType_tokens[] =
    {"list", "FILE"};

// Size of dataType_tokens list
#define SIZE_ELEMENT_DATATYPE 4
#define SIZE_TOKENSLIST_DATATYPE sizeof(dataType_tokens) / sizeof(dataType_tokens[0])

/* Tokens des conditions et des boucles */
const char *conditionloop_tokensName[] =
    {"IF", "ELIF", "ELSE", "WHILE", "DO", "FOR", "IN"};
const char *conditionloop_tokens[] =
    {"if", "elif", "else", "while", "do", "for", "in"};

// Size of conditionLoop_tokens list
#define SIZE_ELEMENT_CONDITIONLOOP 6
#define SIZE_TOKENSLIST_CONDITIONLOOP sizeof(conditionloop_tokens) / sizeof(conditionloop_tokens[0])

/* Tokens des opérateurs arithmétique, comparaison, affectation, logique */
const char *operatorSymb_tokensName[] =
    {"PLUS", "MOINS", "DIV", "MOD", "MULT", "POWER", "EG", "DIFF", "INFEG", "INF", "SUPEG", "SUP", "AFF", "AND", "OR"};
const char *operatorSymb_tokens[] =
    {"+", "-", "/", "%", "*", "^", "==", "!=", "<=", "<", ">=", ">", "=", "&", "|"};

// Size of operatorSymb_tokens list
#define SIZE_TOKENSLIST_OPERATORSYMB sizeof(operatorSymb_tokens) / sizeof(operatorSymb_tokens[0])

/* Tokens des charactères spéciaux */
const char *specialSymb_tokensName[] =
    {"PV", "DP", "VIR", "PO", "PF", "BO", "BF", "CBO", "CBF"};
const char *specialSymb_tokens[] =
    {";", ":", ",", "(", ")", "[", "]", "{", "}"};

// Size of specialSymb_tokens list
#define SIZE_TOKENSLIST_SPECIALSYMB sizeof(specialSymb_tokens) / sizeof(specialSymb_tokens[0])

#endif /* LEXER_H_ */