#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "input.h"

/* energy levels */
struct _e_t {
 int ni;
 int nj;
 unsigned int **d;
};
typedef struct _e_t e_t;

int e_init(e_t *p);

int solve(){

 e_t e;
 if(e_init(&e)){
  return 1;
 }

 return 0;
}
int e_init(e_t *p){
 input_t input;
 int ni;
 int nj;
 int i;

 if(p == NULL){
  return 1;
 }
 if(input_init(input)){
  return 1;
 }
 ni = 0;
 while(!input_endq(input)){
  if(ni == 0){
   nj = 0;
   while(!input_eol(input)){
    input_readchar(input);
    nj++;
   }
  }
  input_skipline(input);
  ni++;
 }
 p->ni = ni;
 p->nj = nj;
 p->d = malloc(sizeof(p->d[0]) * ni);
 if(p->d == NULL){
  return 1;
 }
 for(i=0;i<ni;i++){
  p->d[i] = malloc(sizeof(p->d[0][0]) * nj);
  if(p->d[i] == NULL){
   return 1;
  }
 }
 /* TODO */

 return 0;
}
