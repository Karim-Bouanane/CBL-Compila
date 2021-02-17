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
-------FUNC--------------------
void functions(){
	get_token();
	if(strcmp(currentToken,"ID_TOKEN")!=0)
		error("id missing");
	get_token();
	if(strcmp(currentToken,"PO_TOKEN")!=0)
		error("PO missing");
	get_token();
	if(strcmp(currentToken,"ID_TOKEN")==0){
		get_token();
		while(strcmp(currentToken,"VIR_TOKEN")==0){
			get_token();
			if(strcmp(currentToken,"ID_TOKEN")!=0)
				error("ID missing");
			get_token();
		}
	}
	if(strcmp(currentToken,"PF_TOKEN")!=0)
		error("PO missing");
	get_token();
	if((strcmp(currentToken,"CBO_TOKEN")!=0))
		error("CBO missing");
	get_token();
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
	Insts();
	if((strcmp(currentToken,"CBF_TOKEN")!=0))
		error("CBF missing");
	printf("bloc function compiled succefuly");
	get_token();	
}
------------INSTS-----------
void Insts(){
  while(Inst());
  get_token();
}
-----------INST------------
bool Inst(){
	if (strcmp(currentToken,"IDF_TOKEN")==0){
		CallFunction();
	}else if (strcmp(currentToken,"Return_TOKEN")==0){
		is_value();
	}else if(strcmp(currentToken,"IF_TOKEN")==0){
		decision();
	}else if(strcmp(currentToken,"FOR_TOKEN")==0){
		Loop();
	}else return FALSE;
    
	return TRUE;
}
-----------CALLFUNCTION--------
void CallFunction(){
		get_token();
		if (strcmp(currentToken,"PO_TOKEN")==0){
			get_token();
			if(strcmp(currentToken,"ID_TOKEN")==0){
				get_token();
				while((strcmp(currentToken,"VIR_TOKEN")==0)){
					get_token();
					if(strcmp(currentToken,"ID_TOKEN")!=0)
						error("id missing");
					get_token();
				}
			}
		}
		else error("PO missing");
		if (strcmp(currentToken,"PF_TOKEN")!=0)
			error("PF missing");
		get_token();
		if(strcmp(currentToken,"PV_TOKEN")==0){
			get_token();
			//continue;
		}
				
	}

-------MAIN--------------------	
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
	get_token();
	if(strcmp(currentToken,"DP_TOKEN")!=0)
		error("main error");
	//inside main bloc
	insts();
}
//Condition:(exp Comp_Op exp) {logic_op (exp com_op exp)}
void condition(){
	do{
		get_token();
		if(strcmp(currentToken,"PO_TOKEN")!=0)
			error("condition error");
		exp();
		for(int i = 0; i < 6; i++){
			if(strcmp(currentToken, Comp_Op[i]) == 0)
				break;
		}
		if(i == 6)
			error("condition has no comp op");
		exp();
		if(strcmp(currentToken,"PF_TOKEN")!=0)
			error("')' missing");
		else get_token();
	}while((strcmp(currentToken,"AND_TOKEN")==0) || (strcmp(currentToken,"OR_TOKEN")==0));
}
//Loop: for ID in Value { Insts } 
//      | for ID in (Num, Num) { Insts } 
//      | while (condition ){ Insts } 
//      |   do{ Ints }while (condition);
void loop(){
	//for
	get_token();
	if(strcmp(currentToken,"FOR_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"ID_TOKEN")!=0)
			error("loop for id undeclared")
		get_token();
		if(strcmp(currentToken,"IN_TOKEN")!=0)
			error("loop");
		get_token();
		if(strcmp(currentToken,"PO_TOKEN")==0){
			get_token();
			if(strcmp(currentToken,"NUM_TOKEN")!=0)
				error("loop");
			get_token();
			if(strcmp(currentToken,"VIR_TOKEN")!=0)
				error("loop");
			get_token();
			if(strcmp(currentToken,"NUM_TOKEN")!=0)
				error("loop");
			get_token();
			if(strcmp(currentToken,"PF_TOKEN")!=0)
				error("loop");
			get_token();
		}else is_value();
		if(strcmp(currentToken,"CBO_TOKEN")!=0)
			error("loop");
		insts();
		//get_token();
		if(strcmp(currentToken,"CBF_TOKEN")!=0)
			error("loop");
	}//while
	else if(strcmp(currentToken,"WHILE_TOKEN")==0){
		condition();
		if(strcmp(currentToken,"CBO_TOKEN")!=0)
			error("loop");
		insts();
		//get_token();
		if(strcmp(currentToken,"CBF_TOKEN")!=0)
			error("loop");
	}//do while
	else if(strcmp(currentToken,"DO_TOKEN")==0){
		if(strcmp(currentToken,"CBO_TOKEN")!=0)
			error("loop");
		insts();
		//get_token();
		if(strcmp(currentToken,"CBF_TOKEN")!=0)
			error("loop");
		get_token();
		if(strcmp(currentToken,"WHILE_TOKEN")!=0)
			error("loop");
		condition();
		if(strcmp(currentToken,"PV_TOKEN")!=0)
			error("loop");
	}
}
//EXPR::=TERM { [+|-] TERM } || callFunction || value
void expr(){
	get_token();
	//callFunction();
	do{
		Term();
	}while((strcmp(currentToken,"PLUS_TOKEN")==0) || (strcmp(currentToken,"MOINS_TOKEN")==0));
	is_value();
}
//TERM::=FACT {[*|/|^|%] FACT}
void term(){
	do{
		Fact();
		get_token();
	}while((strcmp(currentToken,"MULT_TOKEN")==0) || (strcmp(currentToken,"DIV_TOKEN")==0) 
		|| (strcmp(currentToken,"POWER_TOKEN")==0) || (strcmp(currentToken,"MOD_TOKEN")==0));
}
//FACT::=ID | NUM | (EXPR)
void fact(){
	get_token();
	if(strcmp(currentToken,"ID_TOKEN")==0)
		return;
	else if(strcmp(currentToken,"PO_TOKEN")==0){
		exp();
		if(strcmp(currentToken,"PF_TOKEN")!=0)
			error("expression error");
		return;
	}
	else if(strcmp(currentToken,"NUM_TOKEN")==0)
		return;
	else error("expression");
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
