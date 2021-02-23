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
		get_token();
		do{
			functions();
		}while(strcmp(currentToken,"ID_TOKEN")==0);
	}
	if(strcmp(currentToken,"MAIN_TOKEN")==0){
		Main();
		return;
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
		get_token();
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
			get_token();
			is_value();
		}
		if(strcmp(currentToken,"PV_TOKEN")==0){
			get_token();
			continue;
		}
		else error("PV_token error");
	}
}
//-------FUNC--------------------
void functions(){
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
		error("PF missing");
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
//------------INSTS-----------
void Insts(){
  while(Inst());
}
//-----------INST------------
bool Inst(){
	if (strcmp(currentToken,"ID_TOKEN")==0){
		get_token();
		if (strcmp(currentToken,"AFF_TOKEN")==0)
			expr();
		else if (strcmp(currentToken,"PO_TOKEN")==0)
			CallFunction();
		else if (strcmp(currentToken,"BO_TOKEN")==0)
			list();
		else error("inst not clear");
		if(strcmp(currentToken,"PV_TOKEN")!=0)
			error("pv missing");
		get_token();
	}else if (strcmp(currentToken,"RETURN_TOKEN")==0){
		get_token();
		if (strcmp(currentToken,"ID_TOKEN")!=0)
			is_value();
		else get_token();
		if(strcmp(currentToken,"PV_TOKEN")!=0)
			error("pv missing");
		get_token();
	}else if(strcmp(currentToken,"IF_TOKEN")==0){
		decision();
	}else if(strcmp(currentToken,"FOR_TOKEN")==0 || strcmp(currentToken,"DO_TOKEN")==0
		|| strcmp(currentToken,"WHILE_TOKEN")==0){
		loop();
		get_token();
	}else return FALSE;
    
	return TRUE;
}

//------------------LIST------
void list(){
	get_token();
	if(strcmp(currentToken,"INT_TOKEN")==0 || strcmp(currentToken,"ID_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"BF_TOKEN")!=0);
			error("BF_TOKEN missing");
		if(strcmp(currentToken,"AFF_TOKEN")!=0)
			expr();
		else  error("AFF_TOKEN missing");
	}else error("indice missing");
}
//-----------CALLFUNCTION-------- start by PO_token already read
void CallFunction(){
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
}


//-------MAIN--------------------	
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
	get_token();
	Insts();
}
//Condition:(exp Comp_Op exp) {logic_op (exp com_op exp)}
void condition(){
	do{
		get_token();
		if(strcmp(currentToken,"PO_TOKEN")!=0)
			error("condition error");
		expr();
		int i;
		for(i = 0; i < 6; i++){
			if(strcmp(currentToken, Comp_Op[i]) == 0)
				break;
		}
		if(i == 6)
			error("condition has no comp op");
		expr();
		if(strcmp(currentToken,"PF_TOKEN")!=0)
			error("')' missing");
		else get_token();
	}while((strcmp(currentToken,"AND_TOKEN")==0) || (strcmp(currentToken,"OR_TOKEN")==0));
}
//Loop: for ID in Value { Insts } 
//      | for ID in (Num|ID, Num|ID) { Insts } 
//      | while (condition ){ Insts } 
//      |   do{ Ints }while (condition);
void loop(){
	//for
	if(strcmp(currentToken,"FOR_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"ID_TOKEN")!=0)
			error("loop for id undeclared");
		get_token();
		if(strcmp(currentToken,"IN_TOKEN")!=0)
			error("loop");
		get_token();
		if(strcmp(currentToken,"PO_TOKEN")==0){
			get_token();
			if(strcmp(currentToken,"INT_TOKEN")!=0 && strcmp(currentToken,"LONG_TOKEN")!=0 && strcmp(currentToken,"ID_TOKEN")!=0)
				error("loop");
			get_token();
			if(strcmp(currentToken,"VIR_TOKEN")!=0)
				error("loop");
			get_token();
			if(strcmp(currentToken,"INT_TOKEN")!=0 && strcmp(currentToken,"LONG_TOKEN")!=0 && strcmp(currentToken,"ID_TOKEN")!=0)
				error("loop");
			get_token();
			if(strcmp(currentToken,"PF_TOKEN")!=0)
				error("loop");
			get_token();
		}else is_value();
		if(strcmp(currentToken,"CBO_TOKEN")!=0)
			error("loop");
		get_token();
		Insts();
		//get_token();
		if(strcmp(currentToken,"CBF_TOKEN")!=0)
			error("loop");
	}//while
	else if(strcmp(currentToken,"WHILE_TOKEN")==0){
		condition();
		if(strcmp(currentToken,"CBO_TOKEN")!=0)
			error("loop");
		get_token();
		Insts();
		//get_token();
		if(strcmp(currentToken,"CBF_TOKEN")!=0)
			error("loop");
	}//do while
	else if(strcmp(currentToken,"DO_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"CBO_TOKEN")!=0)
			error("loop");
		get_token();
		Insts();
		//get_token();
		if(strcmp(currentToken,"CBF_TOKEN")!=0)
			error("looph");
		get_token();
		if(strcmp(currentToken,"WHILE_TOKEN")!=0)
			error("loophh");
		condition();
		if(strcmp(currentToken,"PV_TOKEN")!=0)
			error("loophhh");
	}
}
void decision(){
	condition();
	if(strcmp(currentToken,"CBO_TOKEN")!=0)
		error("{ missing");
	get_token();
	Insts();
	if(strcmp(currentToken,"CBF_TOKEN")!=0)
		error("} missing");
	get_token();
	if(strcmp(currentToken,"ELIF_TOKEN")==0){
		condition();
		if(strcmp(currentToken,"CBO_TOKEN")!=0)
			error("{ missing");
		get_token();
		Insts();
		if(strcmp(currentToken,"CBF_TOKEN")!=0)
			error("} missing");
		get_token();
	}
	if(strcmp(currentToken,"ELSE_TOKEN")==0){
		get_token();
		if(strcmp(currentToken,"CBO_TOKEN")!=0)
			error("{ missing");
		get_token();
		Insts();
		if(strcmp(currentToken,"CBF_TOKEN")!=0)
			error("} missing");
		get_token();
	}
}
//EXPR::=TERM { [+|-] TERM } || callFunction || value
void expr(){
	get_token();
	if (strcmp(currentToken,"ID_TOKEN")==0){
		get_token();
		if (strcmp(currentToken,"PO_TOKEN")==0){
			CallFunction();
		}else if(strcmp(currentToken,"BO_TOKEN")==0){
			get_token();
			if(strcmp(currentToken,"INT_TOKEN")==0 || strcmp(currentToken,"LONG_TOKEN")==0 || strcmp(currentToken,"ID_TOKEN")==0){
				get_token();
				if(strcmp(currentToken,"BF_TOKEN")!=0);
					error("BF_TOKEN missing");
				get_token();
			}else error("indice missing");
		}else exprBegin();
	
	}else if(is_num()){
		get_token();
		exprBegin();
	}
	else if(strcmp(currentToken,"PO_TOKEN")==0){
		expr();
		if(strcmp(currentToken,"PF_TOKEN")!=0)
			error("expression error");
		get_token();
		exprBegin();
	}else is_value();
}
//TERM::=FACT {[*|/|^|%] FACT}
void exprBegin(){
	while((strcmp(currentToken,"MULT_TOKEN")==0) || (strcmp(currentToken,"DIV_TOKEN")==0) 
				|| (strcmp(currentToken,"POWER_TOKEN")==0) || (strcmp(currentToken,"MOD_TOKEN")==0)){
		fact();
	}
	while((strcmp(currentToken,"PLUS_TOKEN")==0) || (strcmp(currentToken,"MOINS_TOKEN")==0)){
		term();
	}
}
void term(){
	do{
		fact();
	}while((strcmp(currentToken,"MULT_TOKEN")==0) || (strcmp(currentToken,"DIV_TOKEN")==0) 
		|| (strcmp(currentToken,"POWER_TOKEN")==0) || (strcmp(currentToken,"MOD_TOKEN")==0));
}
//FACT::=ID | NUM | (EXPR)
void fact(){
	get_token();
	if(strcmp(currentToken,"ID_TOKEN")==0){
		get_token();
		if (strcmp(currentToken,"PO_TOKEN")==0){
			CallFunction();
		}else if(strcmp(currentToken,"BO_TOKEN")==0){
			get_token();
			if(strcmp(currentToken,"INT_TOKEN")==0 || strcmp(currentToken,"LONG_TOKEN")==0 || strcmp(currentToken,"ID_TOKEN")==0){
				get_token();
				if(strcmp(currentToken,"BF_TOKEN")!=0);
					error("BF_TOKEN missing");
				get_token();
			}else error("indice missing");
		}
		return;
	}
	else if(strcmp(currentToken,"PO_TOKEN")==0){
		expr();
		if(strcmp(currentToken,"PF_TOKEN")!=0)
			error("expression error");
		get_token();
		return;
	}
	else if(is_num()){
		get_token();
		return;
	}
	else error("expression");
}
void is_value(){
	//numbers 
	if(is_num() || strcmp(currentToken,"CHAR_TOKEN")==0){
		get_token();
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
		if(accesstype()){
			get_token();
			if(strcmp(currentToken,"PF_token")!=0)
				error("PF_token error");
		}
		else error("accesstype missing");
		get_token();
	}
	else error("unknown type of values");
}
bool is_num(){
	for (int i =0; i<4; i++){
		if(strcmp(currentToken,Num_tokens[i])==0){
			return TRUE;
		}
	}
	return FALSE;
}
bool accesstype(){
	get_token();
	if(strcmp(currentToken,"R_TOKEN")==0 || strcmp(currentToken,"W_TOKEN")==0){
		return TRUE;
	}
	return FALSE;
}
void main(){
	tokens_file = fopen("C:\\Users\\HP\\Desktop\\compila\\tokens.txt", "r");
	program();
	fclose(tokens_file);
}
