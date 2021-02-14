#ifndef SYNTAX_FILE
#define SYNTAX_FILE

FILE* tokens_file;
char *currentToken;
void get_token();
void comment();
void error(char* message);
void program();
void libraries();
void constants();
void variables();
void functions();
void Main();
void is_value();
void insts();
void inst();
void condition();


#endif