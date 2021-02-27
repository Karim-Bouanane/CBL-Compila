#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "syntax.h"

void get_token()
{
	char tmp[20];
	char c = getc(tokens_file);
	int i = 0;
	while (c != '\n')
	{
		tmp[i] = c;
		c = getc(tokens_file);
		i++;
	}
	tmp[i] = '\0';
	currentToken = (char *)malloc(i + 1);
	strcpy(currentToken, tmp);
	printf("%s \n", currentToken);
}
void error(char *message)
{
	fprintf(error_file, "syntax error: %s\n", message);
	exit(0);
}
void program()
{
	get_token();
	if (strcmp(currentToken, "LIBRARIES_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after Libraries");
		libraries();
	}
	else
		error("block libraries missing");
	if (strcmp(currentToken, "CONST_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after Constants");
		constants();
	}
	if (strcmp(currentToken, "VAR_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after Variables");
		variables();
	}
	if (strcmp(currentToken, "FUNC_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after Functions");
		get_token();
		do
		{
			functions();
		} while (strcmp(currentToken, "ID_TOKEN") == 0);
	}
	if (strcmp(currentToken, "MAIN_TOKEN") == 0)
	{
		Main();
		return;
	}
	else
		error("bloc Main missing");
}
void libraries()
{
	get_token();
	while (strcmp(currentToken, "LIB_TOKEN") == 0 || strcmp(currentToken, "H_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after LIB/H");
		do
		{
			get_token();
			if (strcmp(currentToken, "ID_TOKEN") != 0)
				error("library or header name missing");
			get_token();
		} while (strcmp(currentToken, "VIR_TOKEN") == 0);
		if (strcmp(currentToken, "PV_TOKEN") != 0)
			error("';' missing in Libraries");
		get_token();
	}
}
void constants()
{
	get_token();
	while (strcmp(currentToken, "ID_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "AFF_TOKEN") != 0)
			error("identifier missing affectation in Constants");
		get_token();
		is_value();
		//is_value reads next token too
		if (strcmp(currentToken, "PV_TOKEN") != 0)
			error("expecting ';' after affectation in Constants");
		get_token();
	}
}
void variables()
{
	get_token();
	while (strcmp(currentToken, "ID_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "AFF_TOKEN") == 0)
		{
			get_token();
			is_value();
		}
		if (strcmp(currentToken, "PV_TOKEN") == 0 || strcmp(currentToken, "VIR_TOKEN") == 0)
		{
			get_token();
			continue;
		}
		else
			error("expecting ';' after declaration in Variables");
	}
}
//-------FUNC--------------------
void functions()
{
	if (strcmp(currentToken, "ID_TOKEN") != 0)
		error("function's name missing in Functions");
	get_token();
	if (strcmp(currentToken, "PO_TOKEN") != 0)
		error("expecting '(' after function's name in Functions");
	get_token();
	if (strcmp(currentToken, "ID_TOKEN") == 0)
	{
		get_token();
		while (strcmp(currentToken, "VIR_TOKEN") == 0)
		{
			get_token();
			if (strcmp(currentToken, "ID_TOKEN") != 0)
				error("missing argument in function declaration");
			get_token();
		}
	}
	if (strcmp(currentToken, "PF_TOKEN") != 0)
		error("expecting ')' after arguments in function declaration");
	get_token();
	if ((strcmp(currentToken, "CBO_TOKEN") != 0))
		error("expecting '{' in function declaration");
	get_token();
	if (strcmp(currentToken, "CONST_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after Constants");
		constants();
	}
	if (strcmp(currentToken, "VAR_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after Variables");
		variables();
	}
	Insts();
	if ((strcmp(currentToken, "CBF_TOKEN") != 0))
		error("expecting '}' at the end of function declaration");
	get_token();
}
//------------INSTS-----------
void Insts()
{
	while (Inst())
		;
}
//-----------INST------------
bool Inst()
{
	if (strcmp(currentToken, "ID_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "AFF_TOKEN") == 0)
			expr();
		else if (strcmp(currentToken, "PO_TOKEN") == 0)
			CallFunction();
		else if (strcmp(currentToken, "BO_TOKEN") == 0)
			list();
		else
			error("instruction not clear");
		if (strcmp(currentToken, "PV_TOKEN") != 0)
			error("expecting ';' at the end of instruction");
		get_token();
	}
	else if (strcmp(currentToken, "RETURN_TOKEN") == 0)
	{
		expr();
		if (strcmp(currentToken, "PV_TOKEN") != 0)
			error("expecting ';' at the end of instruction");
		get_token();
	}
	else if (strcmp(currentToken, "IF_TOKEN") == 0)
	{
		decision();
	}
	else if (strcmp(currentToken, "FOR_TOKEN") == 0 || strcmp(currentToken, "DO_TOKEN") == 0 || strcmp(currentToken, "WHILE_TOKEN") == 0)
	{
		loop();
		get_token();
	}
	else
		return FALSE;
	return TRUE;
}

//------------------LIST------
void list()
{
	get_token();
	if (strcmp(currentToken, "NUM_TOKEN") == 0 || strcmp(currentToken, "ID_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "BF_TOKEN") != 0)
			error("expecting ']' after indice in instruction");
		get_token();
		if (strcmp(currentToken, "AFF_TOKEN") == 0)
			expr();
		else
			error("instruction missing affectation");
	}
	else
		error("expecting index after '[' in instruction");
}
//-----------CALLFUNCTION-------- start by PO_token already read
void CallFunction()
{
	if (strcmp(currentToken, "PO_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "ID_TOKEN") == 0)
		{
			get_token();
			while ((strcmp(currentToken, "VIR_TOKEN") == 0))
			{
				get_token();
				if (strcmp(currentToken, "ID_TOKEN") != 0)
					error("argument missing when calling function");
				get_token();
			}
		}
	}
	else
		error("expecting '(' after function's name");
	if (strcmp(currentToken, "PF_TOKEN") != 0)
		error("expecting ')' after function's arguments");
	get_token();
}
//-------MAIN--------------------
void Main()
{
	get_token();
	if (strcmp(currentToken, "PO_TOKEN") != 0)
		error("expecting '(' after Main");
	get_token();
	while (strcmp(currentToken, "ID_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "VIR_TOKEN") == 0)
		{
			get_token();
			continue;
		}
		else
			break;
	}
	if (strcmp(currentToken, "PF_TOKEN") != 0)
		error("expecting ')' after Main arguments");
	get_token();
	if (strcmp(currentToken, "DP_TOKEN") != 0)
		error("expecting ':' after Main(args)");
	//inside main bloc
	get_token();
	Insts();
}
//Condition:(exp Comp_Op exp) {logic_op (exp com_op exp)}
void condition()
{
	do
	{
		get_token();
		if (strcmp(currentToken, "PO_TOKEN") != 0)
			error("expecting '(' at the start of each condition ");
		expr();
		int i;
		for (i = 0; i < 6; i++)
		{
			if (strcmp(currentToken, Comp_Op[i]) == 0)
				break;
		}
		if (i == 6)
			error("expecting comparaison inside condition");
		expr();
		if (strcmp(currentToken, "PF_TOKEN") != 0)
			error("expecting ')' at the end of each condition");
		else
			get_token();
	} while ((strcmp(currentToken, "AND_TOKEN") == 0) || (strcmp(currentToken, "OR_TOKEN") == 0));
}
//Loop: for ID in Value { Insts }
//      | for ID in (Num|ID, Num|ID) { Insts }
//      | while (condition ){ Insts }
//      |   do{ Ints }while (condition);
void loop()
{
	//for
	if (strcmp(currentToken, "FOR_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "ID_TOKEN") != 0)
			error("iteration variable missing in for");
		get_token();
		if (strcmp(currentToken, "IN_TOKEN") != 0)
			error("expecting 'in' after iteration variable in for");
		get_token();
		if (strcmp(currentToken, "PO_TOKEN") == 0)
		{
			get_token();
			if (strcmp(currentToken, "NUM_TOKEN") != 0 && strcmp(currentToken, "ID_TOKEN") != 0)
				error("expecting start of iteration variable in for");
			get_token();
			if (strcmp(currentToken, "VIR_TOKEN") != 0)
				error("expecting ',' in for");
			get_token();
			if (strcmp(currentToken, "NUM_TOKEN") != 0 && strcmp(currentToken, "ID_TOKEN") != 0)
				error("expecting end of iteration variable in for");
			get_token();
			if (strcmp(currentToken, "PF_TOKEN") != 0)
				error("expecting ')' befor { in for");
			get_token();
		}
		else
			is_value();
		if (strcmp(currentToken, "CBO_TOKEN") != 0)
			error("missing '{' in for");
		get_token();
		Insts();
		//get_token();
		if (strcmp(currentToken, "CBF_TOKEN") != 0)
			error("missing '}' in for ");
	} //while
	else if (strcmp(currentToken, "WHILE_TOKEN") == 0)
	{
		condition();
		if (strcmp(currentToken, "CBO_TOKEN") != 0)
			error("missing '{' in while");
		get_token();
		Insts();
		//get_token();
		if (strcmp(currentToken, "CBF_TOKEN") != 0)
			error("missing '}' in while");
	} //do while
	else if (strcmp(currentToken, "DO_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "CBO_TOKEN") != 0)
			error("missing '{' in do while");
		get_token();
		Insts();
		//get_token();
		if (strcmp(currentToken, "CBF_TOKEN") != 0)
			error("missing '}' in for");
		get_token();
		if (strcmp(currentToken, "WHILE_TOKEN") != 0)
			error("missing while in do while");
		condition();
		if (strcmp(currentToken, "PV_TOKEN") != 0)
			error("missing ';' at the end of do while");
	}
}
void decision()
{
	condition();
	if (strcmp(currentToken, "CBO_TOKEN") != 0)
		error("expecting '{' after condition in if statement");
	get_token();
	Insts();
	if (strcmp(currentToken, "CBF_TOKEN") != 0)
		error("expecting '}' at the end of if statement");
	get_token();
	if (strcmp(currentToken, "ELIF_TOKEN") == 0)
	{
		condition();
		if (strcmp(currentToken, "CBO_TOKEN") != 0)
			error("expecting '{' after condition in elif statement");
		get_token();
		Insts();
		if (strcmp(currentToken, "CBF_TOKEN") != 0)
			error("expecting '}' at the end of elif statement");
		get_token();
	}
	if (strcmp(currentToken, "ELSE_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "CBO_TOKEN") != 0)
			error("expecting '{' after else");
		get_token();
		Insts();
		if (strcmp(currentToken, "CBF_TOKEN") != 0)
			error("expecting '}' at the end of else statement");
		get_token();
	}
}
//EXPR::=TERM { [+|-] TERM } || callFunction || value
void expr()
{
	get_token();
	if (strcmp(currentToken, "ID_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "PO_TOKEN") == 0)
		{
			CallFunction();
		}
		else if (strcmp(currentToken, "BO_TOKEN") == 0)
		{
			get_token();
			if (strcmp(currentToken, "NUM_TOKEN") == 0 || strcmp(currentToken, "ID_TOKEN") == 0)
			{
				get_token();
				if (strcmp(currentToken, "BF_TOKEN") != 0)
					error("expecting ']' after indice");
				get_token();
			}
			else
				error("missing indice after [");
		}
		exprBegin();
	}
	else if (strcmp(currentToken, "NUM_TOKEN") == 0)
	{
		get_token();
		exprBegin();
	}
	else if (strcmp(currentToken, "PO_TOKEN") == 0)
	{
		expr();
		if (strcmp(currentToken, "PF_TOKEN") != 0)
			error("missing ')' in expression");
		get_token();
		exprBegin();
	}
	else
		is_value();
}
//TERM::=FACT {[*|/|^|%] FACT}
void exprBegin()
{
	while ((strcmp(currentToken, "MULT_TOKEN") == 0) || (strcmp(currentToken, "DIV_TOKEN") == 0) || (strcmp(currentToken, "POWER_TOKEN") == 0) || (strcmp(currentToken, "MOD_TOKEN") == 0))
	{
		fact();
	}
	while ((strcmp(currentToken, "PLUS_TOKEN") == 0) || (strcmp(currentToken, "MOINS_TOKEN") == 0))
	{
		term();
	}
}
void term()
{
	do
	{
		fact();
	} while ((strcmp(currentToken, "MULT_TOKEN") == 0) || (strcmp(currentToken, "DIV_TOKEN") == 0) || (strcmp(currentToken, "POWER_TOKEN") == 0) || (strcmp(currentToken, "MOD_TOKEN") == 0));
}
//FACT::=ID | NUM | (EXPR)
void fact()
{
	get_token();
	if (strcmp(currentToken, "ID_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "PO_TOKEN") == 0)
		{
			CallFunction();
		}
		else if (strcmp(currentToken, "BO_TOKEN") == 0)
		{
			get_token();
			if (strcmp(currentToken, "NUM_TOKEN") == 0 || strcmp(currentToken, "ID_TOKEN") == 0)
			{
				get_token();
				if (strcmp(currentToken, "BF_TOKEN") != 0)
					error("expecting ']' after indice");
				get_token();
			}
			else
				error("missing indice after [");
		}
		return;
	}
	else if (strcmp(currentToken, "PO_TOKEN") == 0)
	{
		expr();
		if (strcmp(currentToken, "PF_TOKEN") != 0)
			error("missing ')' in expression");
		get_token();
		return;
	}
	else if (strcmp(currentToken, "NUM_TOKEN") == 0)
	{
		get_token();
		return;
	}
	else
		error("unclear expression");
}
void is_value()
{
	//numbers and char
	if (strcmp(currentToken, "NUM_TOKEN") == 0 || strcmp(currentToken, "CHAR_TOKEN") == 0)
	{
		get_token();
	}
	//strings
	else if (strcmp(currentToken, "STRING_TOKEN") == 0)
	{
		get_token();
	}
	//list
	else if (strcmp(currentToken, "LIST_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "INF_TOKEN") != 0)
			error("expecting '<' after list");
		do
		{
			get_token();
			if (strcmp(currentToken, "ID_TOKEN") == 0)
				get_token();
			else
				is_value();
		} while (strcmp(currentToken, "VIR_TOKEN") == 0);
		if (strcmp(currentToken, "SUP_TOKEN") != 0)
			error("expecting '>' after list arguments");
		get_token();
	}
	//FILE
	else if (strcmp(currentToken, "FILE_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "PO_TOKEN") != 0)
			error("expecting '(' after FILE");
		//strings
		get_token();
		if (strcmp(currentToken, "STRING_TOKEN") != 0)
			error("file directory missing");
		get_token();
		if (strcmp(currentToken, "VIR_TOKEN") != 0)
			error("expecting ',' after file directory");
		//accesstype
		get_token();
		if (strcmp(currentToken, "CHAR_TOKEN") != 0)
			error("file accesstype missing");
		get_token();
		if (strcmp(currentToken, "PF_TOKEN") != 0)
			error("expecting ')' after file accesstype");
		get_token();
	}
	else
		error("unknown type of value");
}
void main(int argc, char *argv[])
{
	// open program from given command argument
	tokens_file = fopen(argv[1], "r");
	error_file = fopen("C:\\Users\\HP\\Desktop\\cbl-compila\\error.txt","w");
	//tokens_file = fopen("C:\\Users\\HP\\Desktop\\compila\\token.txt", "r");
	program();
	fclose(tokens_file);
	fclose(error_file);
}
