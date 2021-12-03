#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "input.h"

extern char _input[];

int input_readline(input_t input, line_t l){
 if(input_readword(input, l->w, 13)){
  return 1;
 }
 input_skipspace(input);
 return 0;
}

void input_print(){
 char *p;
 p = _input;
 while(p[0] != 0){
  if(p[0] == '\n'){
   printf("\n");
  }else{
   printf("%c", p[0]);
  }
  p++;
 }
}

int input_init(input_t input){
 input->p = _input;
 return 0;
}

int input_readnumber(input_t input, long *v){
 char *q;
 if(v == NULL){
  return 1;
 }
 errno = 0;
 v[0] = strtol(input->p, &q, 10);
 if(errno != 0 || input->p == q){
  return 1;
 }
 input->p = q;
 return 0;
}

/* s is the total size of word (including '\0') */
int input_readword(input_t input, char *w, int s){
 if(w == NULL){
  return 1;
 }
 int i;
 char c;
 i=0;
 do{
  c = input->p[0];
  if(isalnum(c)){
   if(i<s-1){
    w[i] = c;
   }else{
    w[0] = 0;
    return 1;
   }
  }else{
   w[i] = 0;
   return 0;
  }
  i++;
  input->p++;
 }while(1);
 /* unreached */
 return 1;
}


int input_endq(input_t input){
 if(input->p[0] == 0){
  return 1;
 }
 return 0;
}
void input_skipblank(input_t input){
 while(isblank(input->p[0])){
  input->p++;
 }
}
void input_skipspace(input_t input){
 while(isspace(input->p[0])){
  input->p++;
 }
}
