#include <stdio.h>
#include <ctype.h>

#include "input.h"

int check(char *lp, char *l, char *ln, int i){

 char c = l[i];
 if(i>0){
  if(l[i-1] <= c){
   return 0;
  }
 }
 if(isdigit(l[i+1])){
  if(l[i+1] <= c){
   return 0;
  }
 }
 if(lp != NULL){
  if(lp[i] <= c){
   return 0;
  }
 }
 if(ln != NULL){
  if(ln[i] <= c){
   return 0;
  }
 }

 return 1;
}

int solve(){

 input_t input;
 if(input_init(input)){
  return 1;
 }

 int i;
 char *lp;
 char *l;
 char *ln;

 unsigned int sum;

 int k;
 k = 0;

 sum = 0;
 lp = NULL;
 l = input->p;
 input_skipline(input);
 ln = input->p;
 while(l != NULL){

  for(i=0;isdigit(l[i]);i++){
   if(check(lp, l, ln, i)){
    sum += l[i] - '0' + 1;
   }
  }

  lp = l;
  l = ln;
  input_skipline(input);
  if(input_endq(input)){
   /* last line */
   ln = NULL;
  }else{
   ln = input->p;
  }
  k++;
 }

 printf("%d\n", sum);

 return 0;
}
