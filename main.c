#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h> 
#include <stdbool.h>
#include"header.h"

int main(){
    analyse(head); // lexical analysis 
    printList(head); // print my tokens to a txt file named by default "TOKENFILE"
    
}