#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h> 
#include <stdbool.h>
#include"header.h"

void append(struct Node** head_ref,char new_data[]) 
{ 
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
    struct Node *last = *head_ref;
    strcpy(new_node->data,new_data); 
    new_node->next = NULL; 
  
    if (*head_ref == NULL) 
    { 
       *head_ref = new_node; 
       return; 
    }   
    while (last->next != NULL) 
        last = last->next; 
    last->next = new_node; 
    return;     

}
void printList(struct Node *node) 
{ 
  FILE * fp;
  fp = fopen("TOKENFILE.txt","w+");
  while (node != NULL) 
  { 
     fprintf(fp,"%s\n", node->data); 
     node = node->next; 
  } 
  fclose(fp);
}
bool isNumber(char *s)
{
    for (int i = 0; i < strlen(s); i++){
        if (isdigit(s[i]) == 0){
            return false;
    		}
}
    return true;
}
void verifictaion_function(char *verification){

if(strcmp(verification,"=")==0){
	          	verification[0]='\0';
             strcpy(verification, "ASSIGN_TOKEN");
 }
 else if(strcmp(verification,"const")==0){
 		verification[0]='\0';
             strcpy(verification, "CONST_TOKEN");
 }
 else if(strcmp(verification,"var")==0){
 	verification[0]='\0';
              strcpy(verification, "VAR_TOKEN");

 }

 else if(strcmp(verification,"end")==0){verification[0]='\0';
            strcpy(verification,"END_TOKEN");

 }
 else if (strcmp(verification,"if")==0){verification[0]='\0';
             strcpy(verification, "IF_TOKEN");

   }


 else if(strcmp(verification,"while")==0){verification[0]='\0';
             strcpy(verification, "WHILE_TOKEN");

   }

 else if(strcmp(verification,"do")==0){verification[0]='\0';
              strcpy(verification,"DO_TOKEN");

   }

 else if (strcmp(verification,";")==0){verification[0]='\0';
              strcpy(verification, "SEMI_COLON_TOKEN");

     }

 else if(strcmp(verification,".")==0){verification[0]='\0';
              strcpy(verification,"PT_TOKEN");

     }

 else if(strcmp(verification,"+")==0){verification[0]='\0';
              strcpy(verification,"PLUS_TOKEN");

             }
 else if(strcmp(verification,"-")==0){verification[0]='\0';
              strcpy(verification, "MOINS_TOKEN");

             }
 else if(strcmp(verification,"*")==0){verification[0]='\0';
              strcpy(verification,"MULT_TOKEN");

             }
 else if(strcmp(verification,"/")==0){verification[0]='\0';
            strcpy(verification,"DIV_TOKEN");

             }
 else if(strcmp(verification,",")==0){verification[0]='\0';
             strcpy(verification,"COMMA_TOKEN");
             }

 else if(strcmp(verification,"Functions")==0){verification[0]='\0';
              strcpy(verification,"FUNC_TOKEN");

             }
  else if(strcmp(verification,"Libraries")==0){verification[0]='\0';
              strcpy(verification,"LIBRARIES_TOKEN");

             }
  else if(strcmp(verification,"lib")==0){verification[0]='\0';
              strcpy(verification,"LIB_TOKEN");

             }
  else if(strcmp(verification,"H")==0){verification[0]='\0';
              strcpy(verification,"H_TOKEN");

             }
   else if(strcmp(verification,"Constants")==0){verification[0]='\0';
              strcpy(verification,"CONSTANTS_TOKEN");

             } 
    else if(strcmp(verification,"Variables")==0){verification[0]='\0';
              strcpy(verification,"VARIABLE_TOKEN");

             }  
    else if(strcmp(verification,"Main")==0){verification[0]='\0';
              strcpy(verification,"MAIN_TOKEN");

             }
    else if(strcmp(verification,"int")==0){verification[0]='\0';
              strcpy(verification,"INT_TOKEN");

             }
    else if(strcmp(verification,"float")==0){verification[0]='\0';
              strcpy(verification,"FLOAT_TOKEN");

             }      
    else if(strcmp(verification,"double")==0){verification[0]='\0';
              strcpy(verification,"DOUBLE_TOKEN");

             }
    else if(strcmp(verification,"char")==0){verification[0]='\0';
              strcpy(verification,"CHAR_TOKEN");

             }
    else if(strcmp(verification,"long")==0){verification[0]='\0';
              strcpy(verification,"LONG_TOKEN");

             }
    else if(strcmp(verification,"list")==0){verification[0]='\0';
              strcpy(verification,"LIST_TOKEN");

             }
    else if(strcmp(verification,"File")==0){verification[0]='\0';
              strcpy(verification,"FILE_TOKEN");

             }
    else if(strcmp(verification,"or")==0){verification[0]='\0';
              strcpy(verification,"OR_TOKEN");

             }
    else if(strcmp(verification,"and")==0){verification[0]='\0';
              strcpy(verification,"AND_TOKEN");

             }
    else if(strcmp(verification,"%")==0){verification[0]='\0';
              strcpy(verification,"MODULO_TOKEN");

             }
    else if(strcmp(verification,"*")==0){verification[0]='\0';
              strcpy(verification,"MULT_TOKEN");

             }
    else if(strcmp(verification,"^")==0){verification[0]='\0';
              strcpy(verification,"POWER_TOKEN");

             }
    else if(strcmp(verification,"==")==0){verification[0]='\0';
              strcpy(verification,"EG_TOKEN");

             }
    else if(strcmp(verification,"elif")==0){verification[0]='\0';
              strcpy(verification,"ELIF_TOKEN");

             }
    else if(strcmp(verification,"else")==0){verification[0]='\0';
              strcpy(verification,"ELSE_TOKEN");

             }
    else if(strcmp(verification,"While")==0){verification[0]='\0';
              strcpy(verification,"WHILE_TOKEN");

             }
    else if(strcmp(verification,"do")==0){verification[0]='\0';
              strcpy(verification,"DO_TOKEN");

             }
    else if(strcmp(verification,"for")==0){verification[0]='\0';
              strcpy(verification,"FOR_TOKEN");

             }
    else if(strcmp(verification,"in")==0){verification[0]='\0';
              strcpy(verification,"IN_TOKEN");

             }
    else if(strcmp(verification,"Com")==0){verification[0]='\0';
              strcpy(verification,"COM_TOKEN");

             }
 else if(strcmp(verification,"<")==0){verification[0]='\0';
              strcpy(verification, "INF_TOKEN");
 }
 else if(strcmp(verification,"<=")==0){verification[0]='\0';
              strcpy(verification, "INFEG_TOKEN");
             }
 else if(strcmp(verification,">=")==0){verification[0]='\0';
              strcpy(verification, "SUPEG_TOKEN");

             }
 else if(strcmp(verification,">")==0){verification[0]='\0';
             strcpy(verification, "SUP_TOKEN");

             }
 else if(strcmp(verification,"!=")==0){verification[0]='\0';
              strcpy(verification, "DIFF_TOKEN");

 }
 else if(strcmp(verification,"(") ==0){verification[0]='\0';
              strcpy(verification, "OPEN_PAR_TOKEN");

             }
 else if(strcmp(verification,")")==0){verification[0]='\0';
              strcpy(verification,"CLOSE_PAR_TOKEN");

             }
  else if(strcmp(verification,"{")==0){verification[0]='\0';
              strcpy(verification,"OPEN_ACOLADE_TOKEN");

             }
  else if(strcmp(verification,":")==0){verification[0]='\0';
              strcpy(verification,"COLON_TOKEN");

             }
  else if(strcmp(verification,"}")==0){verification[0]='\0';
              strcpy(verification,"CLOSE_ACOLADE_TOKEN");

             }
  else if(strcmp(verification,"_")==0){verification[0]='\0';
              strcpy(verification,"DASH_TOKEN");

             }           
 else if(strcmp(verification,"EOF")==0){verification[0]='\0';
             strcpy(verification,"FIN_TOKEN");
 }
//  else if(strcmp(verification,"")==0){verification[0]='\0';
//              strcpy(verification, "Hello");
//  }

 else {
     if(isNumber(verification)){verification[0]='\0';
       strcpy(verification,  "NUM_TOKEN");
     }
     else{verification[0]='\0';
       strcpy(verification, "ID_TOKEN");
     }
}

}


