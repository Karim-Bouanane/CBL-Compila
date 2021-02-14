#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "syntax.h"

void get_token(){
	fgets(currentToken,100,tokens_file);
}
void error(char* message){
	printf("%s",message);
	exit(0);
}
void program(){
	get_token();
	if(strcmp(currentToken,"LIBRARIES_TOKEN")==0):
		libraries();
	else error("block libraries missing");
	if(strcmp(currentToken,"CONST_TOKEN")==0):
		constansts();
	if(strcmp(currentToken,"VAR_TOKEN")==0):
		variables();
	if(strcmp(currentToken,"FUNC_TOKEN")==0):
		functions();
	if(strcmp(currentToken,"MAIN_TOKEN")==0):
		Main();
	else error("bloc main missing");
}

void main(){
	tokens_file = fopen("C:\\Users\\HP\\Desktop\\compila\\tokens.txt", "r");
	program();
	fclose(tokens_file);
}