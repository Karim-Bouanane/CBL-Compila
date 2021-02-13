#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h> 
#include <stdbool.h>
#include"header.h"
void analyse(){
   char character,big_string[100],nom[100];
   int c=0,pos=0;
   FILE* fp;
   char symbols[13]= {'=','+',',',';','.','-','*','/',':','<','>',':'};
   fp = fopen("prog.txt","r");
   while(character!=EOF){
       int b=0;
       character = fgetc(fp);
       if((character >='a' && character<='z') || (character>='A' && character<='Z') || isdigit(character)!=0){
        big_string[pos++]=character;
        c=1;
    }
       else{
           if(c==1){  //big string est pleine
            strcpy(nom,big_string);
            //printf("%s\n",big_string);
            verifictaion_function(big_string);  
            append(&head,big_string);
            memset(big_string,0,100);
            memset(nom,0,100);
            pos=0;
            c=0;
           }
           if(character=='(' || character==')' || character=='{' || character=='}'){
                            char stock[100];
                            stock[0]=character;
                            //printf("%s\n",stock);
                            verifictaion_function(stock);
                            append(&head,stock);
                            memset(stock,0,100);
                    }
            for(int i=0;i<strlen(symbols);i++){
                if(character == symbols[i]){
                    char stock[100];
                    stock[0]=character;
                    character = fgetc(fp);
                    for(int j=0;j<strlen(symbols);j++){
                        if(character == symbols[j] && character!=';'){
                            stock[1] = character;
                            //printf("%s\n",stock);
                            verifictaion_function(stock);
                            append(&head,stock);
                            memset(stock,0,100);
                            b=1;
                        }
                    }
                    if(b!=1){
                            character = ungetc(character,fp);
                            //printf("%s\n",stock);
                            verifictaion_function(stock);
                            append(&head,stock);
                            memset(stock,0,100);
                            
                    }
                }
            }
   }
}
append(&head,"EOF_TOKEN");
}