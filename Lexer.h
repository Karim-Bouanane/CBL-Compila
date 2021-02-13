
typedef enum
{
    FALSE,
    TRUE
} bool;

/***** Prototype des Fonctions ******/

/***** Déclarations des Tokens ******/

/* Tokens des mots clés de la structure du programme */
const char *programStructure_tokensName[] =
    {"LIBRARIES", "CONSTANTS", "VARIABLES", "FUNCTIONS", "MAIN"};
const char *programStructure_tokens[] =
    {"Libraries", "Constants", "Variables", "Functions", "Main"};

// Size of programStructure_tokens list
#define SIZE_TOKENSLIST_PROGRAMTOKENS sizeof(programStructure_tokens) / sizeof(programStructure_tokens[0])

/* Tokens des type de données */
const char *dataType_tokensName[] =
    {"INT", "FLOAT", "STRING", "DOUBLE", "CHAR", "LONG", "LIST", "FILE"};
const char *dataType_tokens[] =
    {"int", "float", "string", "double", "char", "long", "list", "FILE"};

// Size of dataType_tokens list
#define SIZE_TOKENSLIST_DATATYPE sizeof(dataType_tokens) / sizeof(dataType_tokens[0])

/* Tokens des opérateurs arithmétique, comparaison, affectation, logique */
const char *operatorSymb_tokensName[] =
    {"PLUS", "MOINS", "DIV", "MODULO", "MULT", "POWER", "EG", "DIFF", "INFEG", "INF", "SUPEG", "SUP", "ASSIGN", "AND", "OR"};
const char *operatorSymb_tokens[] =
    {"+", "-", "/", "%", "*", "^", "==", "!=", "<=", "<", ">=", ">", "=", "and", "or"};

// Size of operatorSymb_tokens list
#define SIZE_TOKENSLIST_OPERATORSYMB sizeof(operatorSymb_tokens) / sizeof(operatorSymb_tokens[0])

/* Tokens des charactères spéciaux */
const char *specialSymb_tokensName[] =
    {"SEMI_COLON", "COLON", "COMMA", "DASH", "PT", "OPEN_PAR", "CLOSE_PAR"};
const char *specialSymb_tokens[] =
    {";", ":", ",", "_", ".", "(", ")"};

// Size of specialSymb_tokens list
#define SIZE_TOKENSLIST_SPECIALSYMB sizeof(operatorSymb_tokens) / sizeof(operatorSymb_tokens[0])
