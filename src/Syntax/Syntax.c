#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Syntax.h"

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
	//printf("%s \n", currentToken);
}
void error(char *message, char **stop_token)
{
	bool no_stop = TRUE;
	fprintf(error_file, "syntax error: %s\n", message);
	fflush(error_file);
	//printf("inside error");
	do
	{
		for (int i = 0; stop_token[i] != "\0"; i++)
		{
			if (strcmp(currentToken, stop_token[i]) == 0)
			{
				no_stop = FALSE;
				//printf("leaving error");
				return;
			}
		}
		if (no_stop == TRUE)
			get_token();
	} while (no_stop);
	//printf("leaving error");
}
void program()
{
	get_token();
	if (strcmp(currentToken, "LIBRARIES_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after Libraries", (char *[]){"PV_TOKEN", "\0"});
		libraries();
	}
	else
		error("block libraries missing", (char *[]){"CONST_TOKEN", "VAR_TOKEN", "FUNC_TOKEN", "MAIN_TOKEN", "\0"});
	if (strcmp(currentToken, "CONST_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after Constants", (char *[]){"PV_TOKEN", "\0"});
		constants();
	}else
		error("block constants missing", (char *[]){"VAR_TOKEN", "FUNC_TOKEN", "MAIN_TOKEN", "\0"});
	if (strcmp(currentToken, "VAR_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after Variables", (char *[]){"PV_TOKEN", "\0"});
		variables();
	}else
		error("block variables missing", (char *[]){"FUNC_TOKEN", "MAIN_TOKEN", "\0"});
	if (strcmp(currentToken, "FUNC_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
			error("expecting ':' after Functions", (char *[]){"ID_TOKEN", "MAIN_TOKEN", "\0"});
		else
			get_token();
		do
		{
			functions();
		} while (strcmp(currentToken, "ID_TOKEN") == 0);
	}else
		error("block functions missing", (char *[]){"MAIN_TOKEN", "\0"});
	if (strcmp(currentToken, "MAIN_TOKEN") == 0)
	{
		Main();
		return;
	}
	else
		error("bloc Main missing", (char *[]){"\0"});
}
void libraries()
{
	get_token();
	while (strcmp(currentToken, "LIB_TOKEN") == 0 || strcmp(currentToken, "H_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "DP_TOKEN") != 0)
		{
			error("expecting ':' after LIB/H", (char *[]){"PV_TOKEN", "\0"});
			get_token();
			continue;
		}
		do
		{
			get_token();
			if (strcmp(currentToken, "ID_TOKEN") != 0)
			{
				error("library or header name missing", (char *[]){"PV_TOKEN", "\0"});
				break;
			}
			get_token();
		} while (strcmp(currentToken, "VIR_TOKEN") == 0);
		if (strcmp(currentToken, "PV_TOKEN") != 0)
			error("';' missing in Libraries", (char *[]){"LIB_TOKEN", "H_TOKEN", "CONST_TOKEN", "VAR_TOKEN", "FUNC_TOKEN", "MAIN_TOKEN", "\0"});
		else
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
		{
			error("identifier missing affectation in Constants", (char *[]){"ID_TOKEN", "VAR_TOKEN", "FUNC_TOKEN", "MAIN_TOKEN", "\0"});
			continue;
		}
		get_token();
		is_value();
		//is_value reads next token too
		if (strcmp(currentToken, "PV_TOKEN") != 0)
		{
			error("expecting ';' after affectation in Constants", (char *[]){"ID_TOKEN", "VAR_TOKEN", "FUNC_TOKEN", "MAIN_TOKEN", "\0"});
			continue;
		}
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
			error("expecting ';' after declaration in Variables", (char *[]){"ID_TOKEN", "FUNC_TOKEN", "MAIN_TOKEN", "\0"});
	}
}
//-------FUNC--------------------
void functions()
{
	if (strcmp(currentToken, "ID_TOKEN") != 0)
		error("function's name missing in Functions", (char *[]){"PO_TOKEN", "\0"});
	else
		get_token();
	if (strcmp(currentToken, "PO_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "ID_TOKEN") == 0)
		{
			get_token();
			while (strcmp(currentToken, "VIR_TOKEN") == 0)
			{
				get_token();
				if (strcmp(currentToken, "ID_TOKEN") != 0)
				{
					error("missing argument in function declaration", (char *[]){"PF_TOKEN", "CBO_TOKEN", "\0"});
					break;
				}
				else
					get_token();
			}
		}
		if (strcmp(currentToken, "PF_TOKEN") != 0)
			error("expecting ')' after arguments in function declaration", (char *[]){"CBO_TOKEN", "\0"});
		else
			get_token();
	}
	else
		error("expecting '(' after function's name in Functions", (char *[]){"CBO_TOKEN", "\0"});

	if ((strcmp(currentToken, "CBO_TOKEN") == 0))
	{
		get_token();
		if (strcmp(currentToken, "CONST_TOKEN") == 0)
		{
			get_token();
			if (strcmp(currentToken, "DP_TOKEN") != 0)
				error("expecting ':' after Constants", (char *[]){"PV_TOKEN", "\0"});
			constants();
		}
		if (strcmp(currentToken, "VAR_TOKEN") == 0)
		{
			get_token();
			if (strcmp(currentToken, "DP_TOKEN") != 0)
				error("expecting ':' after Variables", (char *[]){"PV_TOKEN", "\0"});
			variables();
		}
		Insts();
	}
	else
		error("expecting '{' in function declaration", (char *[]){"CBF_TOKEN", "MAIN_TOKEN", "\0"});
	if ((strcmp(currentToken, "CBF_TOKEN") != 0))
		error("expecting '}' at the end of function declaration", (char *[]){"MAIN_TOKEN", "\0"});
	else
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
			error("instruction not clear", (char *[]){"PV_TOKEN", "RETURN_TOKEN", "IF_TOKEN", "FOR_TOKEN", "DO_TOKEN", "WHILE_TOKEN", "\0"});
		if (strcmp(currentToken, "PV_TOKEN") != 0)
			error("expecting ';' at the end of instruction", (char *[]){"RETURN_TOKEN", "IF_TOKEN", "FOR_TOKEN", "DO_TOKEN", "WHILE_TOKEN", "\0"});
		else
			get_token();
	}
	else if (strcmp(currentToken, "RETURN_TOKEN") == 0)
	{
		expr();
		if (strcmp(currentToken, "PV_TOKEN") != 0)
			error("expecting ';' at the end of instruction", (char *[]){"RETURN_TOKEN", "IF_TOKEN", "FOR_TOKEN", "DO_TOKEN", "WHILE_TOKEN", "ID_TOKEN", "\0"});
		else
			get_token();
	}
	else if (strcmp(currentToken, "IF_TOKEN") == 0)
	{
		decision();
	}
	else if (strcmp(currentToken, "FOR_TOKEN") == 0 || strcmp(currentToken, "DO_TOKEN") == 0 || strcmp(currentToken, "WHILE_TOKEN") == 0)
	{
		loop();
	}
	else
		return FALSE;
	return TRUE;
}
//------------------LIST------
void list()
{
	get_token();
	if (strcmp(currentToken, "NUM_TOKEN") != 0 && strcmp(currentToken, "ID_TOKEN") != 0)
		error("expecting index after '[' in instruction", (char *[]){"BF_TOKEN", "AFF_TOKEN", "PV_TOKEN", "\0"});
	else
		get_token();
	if (strcmp(currentToken, "BF_TOKEN") != 0)
		error("expecting ']' after indice in instruction", (char *[]){"AFF_TOKEN", "PV_TOKEN", "\0"});
	else
		get_token();
	if (strcmp(currentToken, "AFF_TOKEN") == 0)
		expr();
	else
		error("instruction missing affectation", (char *[]){"PV_TOKEN", "\0"});
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
					error("argument missing when calling function", (char *[]){"PF_TOKEN", "PV_TOKEN", "\0"});
				get_token();
			}
		}
	}
	else
		error("expecting '(' after function's name", (char *[]){"PF_TOKEN", "PV_TOKEN", "\0"});
	if (strcmp(currentToken, "PF_TOKEN") != 0)
		error("expecting ')' after function's arguments", (char *[]){"PV_TOKEN", "\0"});
	else
		get_token();
}
//-------MAIN--------------------
void Main()
{
	get_token();
	if (strcmp(currentToken, "PO_TOKEN") != 0)
		error("expecting '(' after Main", (char *[]){"PF_TOKEN", "DP_TOKEN", "ID_TOKEN", "RETURN_TOKEN", "IF_TOKEN", "FOR_TOKEN", "DO_TOKEN", "WHILE_TOKEN", "\0"});
	else
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
		error("expecting ')' after Main arguments", (char *[]){"DP_TOKEN", "ID_TOKEN", "RETURN_TOKEN", "IF_TOKEN", "FOR_TOKEN", "DO_TOKEN", "WHILE_TOKEN", "\0"});
	else
		get_token();
	if (strcmp(currentToken, "DP_TOKEN") != 0)
		error("expecting ':' after Main(args)", (char *[]){"ID_TOKEN", "RETURN_TOKEN", "IF_TOKEN", "FOR_TOKEN", "DO_TOKEN", "WHILE_TOKEN", "\0"});
	else
		get_token();
	Insts();
}
//Condition:(exp Comp_Op exp) {logic_op (exp com_op exp)}
void condition()
{
	do
	{
		get_token();
		if (strcmp(currentToken, "PO_TOKEN") == 0)
		{
			expr();
			int i;
			for (i = 0; i < 6; i++)
			{
				if (strcmp(currentToken, Comp_Op[i]) == 0)
					break;
			}
			if (i == 6)
				error("expecting comparaison inside condition", (char *[]){"PF_TOKEN", "CBO_TOKEN", "PV_TOKEN", "\0"});
			else
				expr();
			if (strcmp(currentToken, "PF_TOKEN") != 0)
				error("expecting ')' at the end of each condition", (char *[]){"CBO_TOKEN", "PV_TOKEN", "\0"});
			else
				get_token();
		}
		else
			error("expecting '(' at the start of each condition ", (char *[]){"CBO_TOKEN", "PV_TOKEN", "CBF_TOKEN", "\0"});
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
			error("iteration variable missing in for", (char *[]){"IN_TOKEN", "PO_TOKEN", "CBO_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
		if (strcmp(currentToken, "IN_TOKEN") != 0)
			error("expecting 'in' after iteration variable in for", (char *[]){"PO_TOKEN", "CBO_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
		if (strcmp(currentToken, "PO_TOKEN") == 0)
		{
			get_token();
			if (strcmp(currentToken, "NUM_TOKEN") != 0 && strcmp(currentToken, "ID_TOKEN") != 0)
				error("expecting start of iteration variable in for", (char *[]){"VIR_TOKEN", "PF_TOKEN", "CBO_TOKEN", "CBF_TOKEN", "\0"});
			else
				get_token();
			if (strcmp(currentToken, "VIR_TOKEN") != 0)
				error("expecting ',' in for", (char *[]){"PF_TOKEN", "CBO_TOKEN", "CBF_TOKEN", "\0"});
			else
				get_token();
			if (strcmp(currentToken, "NUM_TOKEN") != 0 && strcmp(currentToken, "ID_TOKEN") != 0)
				error("expecting end of iteration variable in for", (char *[]){"PF_TOKEN", "CBO_TOKEN", "CBF_TOKEN", "\0"});
			else
				get_token();
			if (strcmp(currentToken, "PF_TOKEN") != 0)
				error("expecting ')' befor { in for", (char *[]){"CBO_TOKEN", "CBF_TOKEN", "\0"});
			else
				get_token();
		}
		else
			is_value();
		if (strcmp(currentToken, "CBO_TOKEN") != 0)
			error("missing '{' in for", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
		Insts();
		if (strcmp(currentToken, "CBF_TOKEN") != 0)
			error("missing '}' in for ", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
	} //while
	else if (strcmp(currentToken, "WHILE_TOKEN") == 0)
	{
		condition();
		if (strcmp(currentToken, "CBO_TOKEN") != 0)
			error("missing '{' in while", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
		Insts();
		if (strcmp(currentToken, "CBF_TOKEN") != 0)
			error("missing '}' in while", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
	} //do while
	else if (strcmp(currentToken, "DO_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "CBO_TOKEN") != 0)
			error("missing '{' in do while", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
		Insts();
		//get_token();
		if (strcmp(currentToken, "CBF_TOKEN") != 0)
			error("missing '}' in for", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
		if (strcmp(currentToken, "WHILE_TOKEN") != 0)
			error("missing while in do while", (char *[]){"PV_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			condition();
		if (strcmp(currentToken, "PV_TOKEN") != 0)
			error("missing ';' at the end of do while", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
	}
}
void decision()
{
	condition();
	if (strcmp(currentToken, "CBO_TOKEN") != 0)
		error("expecting '{' after condition in if statement", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
	else
		get_token();
	Insts();
	if (strcmp(currentToken, "CBF_TOKEN") != 0)
		error("expecting '}' at the end of if statement", (char *[]){"ELIF_TOKEN", "ELSE_TOKEN"
																				   "ID_TOKEN",
																	 "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
	else
		get_token();
	if (strcmp(currentToken, "ELIF_TOKEN") == 0)
	{
		condition();
		if (strcmp(currentToken, "CBO_TOKEN") != 0)
			error("expecting '{' after condition in elif statement", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
		Insts();
		if (strcmp(currentToken, "CBF_TOKEN") != 0)
			error("expecting '}' at the end of elif statement", (char *[]){"ELSE_TOKEN", "ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
	}
	if (strcmp(currentToken, "ELSE_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "CBO_TOKEN") != 0)
			error("expecting '{' after else", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
			get_token();
		Insts();
		if (strcmp(currentToken, "CBF_TOKEN") != 0)
			error("expecting '}' at the end of else statement", (char *[]){"ID_TOKEN", "IF_TOKEN", "FOR_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "RETURN_TOKEN", "CBF_TOKEN", "\0"});
		else
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
					error("expecting ']' after indice", (char *[]){"PLUS_TOKEN", "MOINS_TOKEN", "MULT_TOKEN", "MOD_TOKEN", "POWER_TOKEN", "DIV_TOKEN", "\0"});
				else
					get_token();
			}
			else
				error("missing indice after [", (char *[]){"PLUS_TOKEN", "MOINS_TOKEN", "MULT_TOKEN", "MOD_TOKEN", "POWER_TOKEN", "DIV_TOKEN", "\0"});
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
			error("missing ')' in expression", (char *[]){"PV_TOKEN", "CBF_TOKEN", "\0"});
		else
		{
			get_token();
			exprBegin();
		}
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
					error("expecting ']' after indice", (char *[]){"PLUS_TOKEN", "MOINS_TOKEN", "MULT_TOKEN", "MOD_TOKEN", "POWER_TOKEN", "DIV_TOKEN", "\0"});
				else
					get_token();
			}
			else
				error("missing indice after [", (char *[]){"PLUS_TOKEN", "MOINS_TOKEN", "MULT_TOKEN", "MOD_TOKEN", "POWER_TOKEN", "DIV_TOKEN", "\0"});
		}
		return;
	}
	else if (strcmp(currentToken, "PO_TOKEN") == 0)
	{
		expr();
		if (strcmp(currentToken, "PF_TOKEN") != 0)
			error("missing ')' in expression", (char *[]){"PLUS_TOKEN", "MOINS_TOKEN", "MULT_TOKEN", "MOD_TOKEN", "POWER_TOKEN", "DIV_TOKEN", "\0"});
		else
			get_token();
		return;
	}
	else if (strcmp(currentToken, "NUM_TOKEN") == 0)
	{
		get_token();
		return;
	}
	else
		error("unclear expression", (char *[]){"PV_TOKEN", "PLUS_TOKEN", "MOINS_TOKEN", "MULT_TOKEN", "MOD_TOKEN", "POWER_TOKEN", "DIV_TOKEN", "\0"});
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
			error("expecting '<' after list", (char *[]){"\0"});
		do
		{
			get_token();
			if (strcmp(currentToken, "ID_TOKEN") == 0)
				get_token();
			else
				is_value();
		} while (strcmp(currentToken, "VIR_TOKEN") == 0);
		if (strcmp(currentToken, "SUP_TOKEN") != 0)
			error("expecting '>' after list arguments", (char *[]){"PV_TOKEN", "\0"});
		else
			get_token();
	}
	//FILE
	else if (strcmp(currentToken, "FILE_TOKEN") == 0)
	{
		get_token();
		if (strcmp(currentToken, "PO_TOKEN") != 0)
			error("expecting '(' after FILE", (char *[]){"STRING_TOKEN", "VIR_TOKEN", "PV_TOKEN", "PF_TOKEN", "\0"});
		else
			get_token();
		if (strcmp(currentToken, "STRING_TOKEN") != 0)
			error("file directory missing", (char *[]){"VIR_TOKEN", "PV_TOKEN", "PF_TOKEN", "\0"});
		else
			get_token();
		if (strcmp(currentToken, "VIR_TOKEN") != 0)
			error("expecting ',' after file directory", (char *[]){"CHAR_TOKEN", "PF_TOKEN", "PV_TOKEN", "\0"});
		//accesstype
		else
			get_token();
		if (strcmp(currentToken, "CHAR_TOKEN") != 0)
			error("file accesstype missing", (char *[]){"PF_TOKEN", "PV_TOKEN", "\0"});
		else
			get_token();
		if (strcmp(currentToken, "PF_TOKEN") != 0)
			error("expecting ')' after file accesstype", (char *[]){"PV_TOKEN", "\0"});
		else
			get_token();
	}
	else
		error("unknown type of value", (char *[]){"PV_TOKEN", "\0"});
}
void main(int argc, char *argv[])
{
	// open program from given command argument
	tokens_file = fopen("Tokens", "r");
	//tokens_file = fopen(argv[1], "r");
	error_file = fopen("SyntErrors", "a");
	program();
	fclose(tokens_file);
	fclose(error_file);
}
