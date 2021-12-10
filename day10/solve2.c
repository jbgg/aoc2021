#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "input.h"

int solve(){

 input_t input;
 if(input_init(input)){
  return 1;
 }

 int nlinemax;
 int n;
 char c;

 nlinemax = 0;
 while(!input_endq(input)){
  n = 0;
  while(!input_eol(input)){
   c = input_readchar(input);
   if( c!='(' && c!=')' &&
     c!='[' && c!=']' &&
     c!='{' && c!='}' &&
     c!='<' && c!='>'){
    return 1;
   }
   n++;
  }
  if(n > nlinemax){
   nlinemax = n;
  }
  input_skipline(input);
 }

 input_init(input);

 int i;
 char *l;

 l = malloc(sizeof(char)*(nlinemax+1));
 if(l == NULL){
  return 1;
 }

 unsigned long linepoints;
 int illegalq;
 int ni;

 n = 0;
 while(!input_endq(input)){
  i = 0;
  illegalq = 0;
  while(!input_eol(input)){
   c = input_readchar(input);
   if( c=='(' || c=='[' || c=='{' || c=='<'){
    l[i] = c;
    i++;
   }else{
    if(i>0 &&
      ((c==')' && l[i-1]=='(') ||
       (c==']' && l[i-1]=='[') ||
       (c=='}' && l[i-1]=='{') ||
       (c=='>' && l[i-1]=='<'))){
     i--;
    }else{
    /* illegal character */
     illegalq = 1;
     break;
    }
   }
  }
  if(illegalq == 0){
   ni = i;
   linepoints = 0;
   for(i=ni-1;i>=0;i--){
    if(l[i] == ')' || l[i] == ']' ||
      l[i] == '}' || l[i] == '>'){
     printf("!");
    }
    if(l[i] == '('){
     linepoints *= 5;
     linepoints += 1;
    }
    if(l[i] == '['){
     linepoints *= 5;
     linepoints += 2;
    }
    if(l[i] == '{'){
     linepoints *= 5;
     linepoints += 3;
    }
    if(l[i] == '<'){
     linepoints *= 5;
     linepoints += 4;
    }
   }
   printf("%llu\n", linepoints);
  }

  input_skipline(input);
  n++;
 }

 return 0;
}
