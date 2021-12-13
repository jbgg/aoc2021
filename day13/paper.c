#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "paper.h"

int instr_add(instr_t **ipp, char c, int n){
 if(ipp == NULL){
  return 1;
 }
 if(ipp[0] != NULL){
  return 1;
 }
 ipp[0] = malloc(sizeof(instr_t));
 if(ipp[0] == NULL){
  return 1;
 }
 ipp[0]->foldxy = c;
 ipp[0]->line = n;
 ipp[0]->next = NULL;
 return 0;
}

int paper_init(paper_t *p){
 if(p == NULL){
  return 1;
 }
 input_t input;

 p->m = NULL;
 p->xmax = 0;
 p->ymax = 0;
 p->instr = NULL;

 int xmax;
 int ymax;
 char **m;
 int xi;
 int yi;

 if(input_init(input)){
  return 1;
 }

 xmax = 0;
 ymax = 0;
 int x;
 int y;
 while(!input_endq(input)){
  if(input_readnumber(input, &x)){
   /* is not a number ... */
   break;
  }else{
   /* skip , */
   input_skippunct(input);
   if(input_readnumber(input, &y)){
    return 1;
   }
   input_skipline(input);

   if(x > xmax){
    xmax = x;
   }
   if(y > ymax){
    ymax = y;
   }
  }
 }

 xmax++;
 ymax++;

 m = malloc(sizeof(m[0]) * xmax);
 if(m == NULL){
  return 1;
 }
 for(xi = 0;xi<xmax;xi++){
  m[xi] = malloc(sizeof(m[0][0]) * ymax);
  if(m[xi] == NULL){
   return 1;
  }
  for(yi=0;yi<ymax;yi++){
   m[xi][yi] = NOMARKED;
  }
 }


 char str[6];
 char c;
 int n;

 instr_t **ipp;
 ipp = &(p->instr);

 input_skipblanklines(input);
 while(!input_endq(input)){

  /* skip fold */
  input_readword(input, str, 6, NULL);
  input_skipspace(input);
  /* skip along */
  input_readword(input, str, 6, NULL);
  input_skipspace(input);
  c = input_readchar(input);
  if(c != FOLDX && c != FOLDY){
   return 1;
  }
  if(input_readchar(input) != '='){
   return 1;
  }
  if(input_readnumber(input, &n)){
   return 1;
  }
  input_skipline(input);

  if(instr_add(ipp, c, n)){
   return 1;
  }
  if(ipp[0] == NULL){
   return 1;
  }
  ipp = &(ipp[0]->next);
 }

 p->xmax = xmax;
 p->ymax = ymax;
 p->m = m;

 input_init(input);
 while(!input_endq(input)){
  if(input_readnumber(input, &x)){
   /* is not a number ... */
   break;
  }else{
   /* skip , */
   input_skippunct(input);
   if(input_readnumber(input, &y)){
    return 1;
   }
   input_skipline(input);
   m[x][y] = MARKED;
  }
 }

 return 0;
}

int instr_print(instr_t *p){

 while(p != NULL){
  printf("fold along %c=%d\n", p->foldxy, p->line);
  p = p->next;
 }
}
int paper_print(paper_t p){
 int xi;
 int yi;
 printf("xmax = %d; ymax = %d\n", p.xmax, p.ymax);
 /*
 for(yi=0;yi<p.ymax;yi++){
  for(xi=0;xi<p.xmax;xi++){
   printf("%c", p.m[xi][yi]);
  }
  printf("\n");
 }
 */
 instr_print(p.instr);

 return 0;
}
