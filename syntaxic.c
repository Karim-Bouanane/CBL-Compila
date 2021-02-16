#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "syntax.h"

void get_token(){
	char tmp[20];
	char c = getc(tokens_file);
	int i=0;
	while (c !='\n'){
		tmp[i] = c;
		c = getc(tokens_file);
		i++;
	}
	tmp[i]='\0';
	currentToken = (char *)malloc(i+1);
	strcpy(currentToken, tmp);
	printf("%s \n",currentToken);
	if(strcmp(currentToken,"COM_TOKEN")==0)
		comment();
}
void comment(){
	get_token();
	if(strcmp(currentToken,"DP_TOKEN")!=0)
		error("DP_token error");
	while(strcmp(currentToken,"PV_TOKEN")!=0)
		get_token();
	get_token();
}
void error(char* message){
	printf("syntax error %s",message);
	exit(0);
}
void program(){
	get_token();
	if(strcmp(currentToken,"LIBRARIES_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"DP_TOKEN")!=0)
			error("DP_token error");
		libraries();
	}
	else error("block libraries missing");
	if(strcmp(currentToken,"CONST_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"DP_TOKEN")!=0)
			error("DP_token error");
		constants();
	}
	if(strcmp(currentToken,"VAR_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"DP_TOKEN")!=0)
			error("DP_token error");
		variables();
	}
	if(strcmp(currentToken,"FUNC_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"DP_TOKEN")!=0)
			error("DP_token error");
		functions();
	}
	if(strcmp(currentToken,"MAIN_TOKEN")==0){
		Main();
	}
	else error("bloc main missing");
}
void libraries(){
	get_token();
	while(strcmp(currentToken,"LIB_TOKEN")==0 || strcmp(currentToken,"H_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"DP_TOKEN")!=0)
			error("DP_token error");
		do {
			get_token();
			if(strcmp(currentToken,"ID_TOKEN")!=0)
				error("ID_token error");
			get_token();
		}while(strcmp(currentToken,"VIR_TOKEN")==0);
		if(strcmp(currentToken,"PV_TOKEN")!=0)
			error("pv_token error");
		get_token();
	}
}
void constants(){
	get_token();
	while(strcmp(currentToken,"ID_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"AFF_TOKEN")!=0)
			error("AFF_token error");
		is_value();
		//is_value reads next token too 
		if(strcmp(currentToken,"PV_TOKEN")!=0)
			error("PV_token error");
		get_token();
	}
}
void variables(){
	get_token();
	while(strcmp(currentToken,"ID_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"AFF_TOKEN")==0){
			is_value();
		}
		if(strcmp(currentToken,"PV_TOKEN")==0){
			get_token();
			continue;
		}
		else error("PV_token error");
	}
}
void functions(){	
}
void Main(){
	get_token();
	if(strcmp(currentToken,"PO_TOKEN")!=0)
		error("main error");
	get_token();
	while(strcmp(currentToken,"ID_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"PV_TOKEN")==0){
			get_token();
			continue;
		}
		else break;
	}
	if(strcmp(currentToken,"PF_TOKEN")!=0)
		error("main error");
	//inside main bloc
	insts();
}
void is_value(){
	get_token();
	//numbers 
	if(strcmp(currentToken,"NUM_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"VIR_TOKEN")==0){
			get_token();
			if(strcmp(currentToken,"NUM_TOKEN")!=0)
				error("NUM_token error");
		}
	}
	//strings
	else if(strcmp(currentToken,"ST_TOKEN")==0){
		get_token();
		while (strcmp(currentToken,"ST_TOKEN")!=0)
			get_token();
		get_token();
	}
	//list
	else if(strcmp(currentToken,"LIST_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"INF_TOKEN")!=0)
			error("INF_token error");
		get_token();
		while(strcmp(currentToken,"ID_TOKEN")==0){
			get_token();
			if(strcmp(currentToken,"VIR_TOKEN")==0){
				get_token();
				continue;
			}
			else if(strcmp(currentToken,"SUP_TOKEN")==0){
				get_token();
				break;
			}
		}
	}
	//FILE
	else if(strcmp(currentToken,"FILE_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"PO_TOKEN")!=0)
			error("PO_token error");
		//strings
		get_token();
		if(strcmp(currentToken,"ST_TOKEN")==0){
			get_token();
			while (strcmp(currentToken,"ST_TOKEN")!=0)
				get_token();
		}
		get_token();
		if(strcmp(currentToken,"VIR_TOKEN")!=0)
			error("VIR_token error");
		//accesstype
		get_token();


	}
	else error("unknown type of values");
}
void main(){
	tokens_file = fopen("C:\\Users\\HP\\Desktop\\compila\\tokens.txt", "r");
	program();
	fclose(tokens_file);
}