#ifndef SYNTAX_FILE
#define SYNTAX_FILE

FILE* tokens_file;
FILE* error_file;
char *currentToken;

#define TRUE    1
#define FALSE   0

const char* Comp_Op[] = {"EG_TOKEN", "DIFF_TOKEN", "INFEG_TOKEN", 
					"INF_TOKEN", "SUPEG_TOKEN", "SUP_TOKEN"};
void get_token();
void error(char* message, char** stop_token);
void program();
void libraries();
void constants();
void variables();
void functions();
void Main();
void is_value();
void Insts();
bool Inst();
void list();
void CallFunction();
void condition();
void decision();
void loop();
void expr();
void exprBegin();
void term();
void fact();


#endif