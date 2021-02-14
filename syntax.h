#ifndef SYNTAX_FILE
#define SYNTAX_FILE

FILE* tokens_file;
char currentToken[20];
void get_token();
void error(char* message);
void program();
void libraries();
void constants();
void variables();
void functions();
void Main();

void insts();
void inst();
void condition();


#endif