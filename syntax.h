#ifndef SYNTAX_FILE
#define SYNTAX_FILE

FILE* tokens_file;
char *currentToken;

const char* Comp_Op[] = {"EG_TOKEN", "DIFF_TOKEN", "INFEG_TOKEN", 
					"INF_TOKEN", "SUPEG_TOKEN", "SUP_TOKEN"};
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
void loop();
void expr();
void term();
void fact();


#endif