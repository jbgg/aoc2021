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

 int points;

 n = 0;
 points = 0;
 while(!input_endq(input)){
  i = 0;
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
     if(c==')'){
      points += 3;
     }
     if(c==']'){
      points += 57;
     }
     if(c=='}'){
      points += 1197;
     }
     if(c=='>'){
      points += 25137;
     }
     break;
    }
   }
  }
  input_skipline(input);
  n++;
 }

 printf("%d\n", points);

 return 0;
}
