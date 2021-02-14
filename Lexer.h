/***** Définition ******/

#define MAXDIGIT_NUMBER 30
#define MAXCHAR_STRING 100

typedef enum
{
    FALSE,
    TRUE
} bool;

/***** Prototype des Fonctions ******/

char NextChar();
void LexError();
void saveToken();
void ignoreComment();
void ignoreWhiteSpaces();
bool search_for_token();
bool isBloc();
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
    {"LIBRARIES", "CONSTANTS", "VARIABLES", "FUNCTIONS", "MAIN"};
const char *bloc_tokens[] =
    {"Libraries", "Constants", "Variables", "Functions", "Main"};

// Size of programStructure_tokens list
#define SIZE_ELEMENT_BLOC sizeof(bloc_tokens[0])
#define SIZE_TOKENSLIST_BLOC sizeof(bloc_tokens) / sizeof(bloc_tokens[0])

/* Tokens des type de données */
const char *dataType_tokensName[] =
    {"INT", "FLOAT", "STRING", "DOUBLE", "CHAR", "LONG", "LIST", "FILE"};
const char *dataType_tokens[] =
    {"int", "float", "string", "double", "char", "long", "list", "FILE"};

// Size of dataType_tokens list
#define SIZE_ELEMENT_DATATYPE sizeof(dataType_tokens[0])
#define SIZE_TOKENSLIST_DATATYPE sizeof(dataType_tokens) / sizeof(dataType_tokens[0])

/* Tokens des conditions et des boucles */
const char *conditionloop_tokensName[] =
    {"IF", "ELIF", "WHILE", "DO", "FOR", "IN"};
const char *conditionloop_tokens[] =
    {"if", "elif", "while", "do", "for", "in"};

// Size of dataType_tokens list
#define SIZE_ELEMENT_CONDITIONLOOP sizeof(conditionloop_tokens[0])
#define SIZE_TOKENSLIST_CONDITIONLOOP sizeof(conditionloop_tokens) / sizeof(conditionloop_tokens[0])

/* Tokens des opérateurs arithmétique, comparaison, affectation, logique */
const char *operatorSymb_tokensName[] =
    {"PLUS", "MOINS", "DIV", "MODULO", "MULT", "POWER", "EG", "DIFF", "INFEG", "INF", "SUPEG", "SUP", "ASSIGN", "AND", "OR"};
const char *operatorSymb_tokens[] =
    {"+", "-", "/", "%", "*", "^", "==", "!=", "<=", "<", ">=", ">", "=", "&", "|"};

// Size of operatorSymb_tokens list
#define SIZE_ELEMENT_OPERATORSYMB sizeof(operatorSymb_tokens[0])
#define SIZE_TOKENSLIST_OPERATORSYMB sizeof(operatorSymb_tokens) / sizeof(operatorSymb_tokens[0])

/* Tokens des charactères spéciaux */
const char *specialSymb_tokensName[] =
    {"SEMI_COLON", "COLON", "COMMA", "DASH", "PT", "OPEN_PAR", "CLOSE_PAR"};
const char *specialSymb_tokens[] =
    {";", ":", ",", "_", ".", "(", ")"};

// Size of specialSymb_tokens list
#define SIZE_ELEMENT_SPECIALSYMB sizeof(specialSymb_tokens[0])
#define SIZE_TOKENSLIST_SPECIALSYMB sizeof(specialSymb_tokens) / sizeof(specialSymb_tokens[0])
