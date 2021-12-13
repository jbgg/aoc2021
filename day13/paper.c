#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "paper.h"

int paper_ismarkedq(paper_t p, int xi, int yi){
 if(xi < 0 || yi < 0){
  return 0;
 }
 if(xi >= p.xmax || yi >= p.ymax){
  return 0;
 }
 if(p.m[xi][yi] == MARKED){
  return 1;
 }
 return 0;
}

int paper_count(paper_t p, unsigned long *n){
 int xi;
 int yi;
 char **m;
 unsigned long count;
 if(n == NULL){
  return 1;
 }
 m = p.m;
 if(m == NULL){
  return 1;
 }
 count = 0;
 for(xi=0;xi<p.xmax;xi++){
  for(yi=0;yi<p.ymax;yi++){
   if(m[xi][yi] == MARKED){
    count++;
   }
  }
 }
 n[0] = count;
 return 0;
}

int paper_fold(paper_t *p){

 int xmax;
 int ymax;
 char **m;
 int xi;
 int yi;
 instr_t *instr;

 if(p == NULL){
  return 1;
 }

 xmax = p->xmax;
 ymax = p->ymax;
 m = p->m;

 instr = p->instr;
 if(instr == NULL){
  return 1;
 }

 int line;
 line = instr->line;


 if(instr->foldxy == FOLDX){
  if(line < 0 || line > xmax){
   return 1;
  }
  for(yi=0;yi<ymax;yi++){
   if(m[line][yi] == MARKED){
    return 1;
   }
  }
  for(xi=0;xi<line;xi++){
   for(yi=0;yi<ymax;yi++){
    if(paper_ismarkedq(p[0], 2*line-xi, yi)){
     m[xi][yi] = MARKED;
    }
   }
  }
  p->xmax = line;
 }else if(instr->foldxy == FOLDY){
  if(line < 0 || line > ymax){
   return 1;
  }
  for(xi=0;xi<xmax;xi++){
   if(m[xi][line] == MARKED){
    return 1;
   }
  }
  for(xi=0;xi<xmax;xi++){
   for(yi=0;yi<line;yi++){
    if(paper_ismarkedq(p[0], xi, 2*line-yi)){
     m[xi][yi] = MARKED;
    }
   }
  }
  p->ymax = line;
 }else{
  return 1;
 } /* if instr->foldxy */

 p->instr = instr->next;
 return 0;
}

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
 for(yi=0;yi<p.ymax;yi++){
  for(xi=0;xi<p.xmax;xi++){
   printf("%c", p.m[xi][yi]);
  }
  printf("\n");
 }
 return 0;
}
