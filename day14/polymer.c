#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "polymer.h"
#include "input.h"

tcount_t tcount[NCOUNT][NCOUNT][MAXDEPTH];

int tcount_init(){
 int i;
 int j;
 int k;
 int m;
 for(i=0;i<NCOUNT;i++){
  for(j=0;j<NCOUNT;j++){
   for(m=0;m<MAXDEPTH;m++){
    for(k=0;k<NCOUNT;k++){
     tcount[i][j][m].count[k] = 0;
    }
    tcount[i][j][m].calq = TCOUNT_NO;
   }
  }
 }
}

int r_match(int c1, int c2, r_t *r, int nr, char *c){
 int i;
 for(i=0;i<nr;i++){
  if(c1 == r[i][0] && c2 == r[i][1]){
   c[0] = r[i][2];
   return 1;
  }
 }
 return 0;
}

int p_count_r(char c1, char c2, r_t *r, int nr, count_t count, int depth){
 int i;
 char c;
 if(depth == 0){
  return 0;
 }
 if(tcount[c1][c2][depth].calq != TCOUNT_NO){
  for(i=0;i<NCOUNT;i++){
   count[i] = tcount[c1][c2][depth].count[i];
  }
  return 0;
 }
 count_t l1;
 count_t l2;
 for(i=0;i<NCOUNT;i++){
  count[i] = 0;
  l1[i] = 0;
  l2[i] = 0;
 }
 if(r_match(c1, c2, r, nr, &c)){
  count[c]++;
  if(p_count_r(c1, c, r, nr, l1, depth-1)){
   return 1;
  }
  if(p_count_r(c, c2, r, nr, l2, depth-1)){
   return 1;
  }
  for(i=0;i<NCOUNT;i++){
   count[i] += l1[i] + l2[i];
  }
 }
 for(i=0;i<NCOUNT;i++){
  tcount[c1][c2][depth].count[i] = count[i];
 }
 tcount[c1][c2][depth].calq = TCOUNT_YES;
 return 0;
}

int p_count(char *cc, int nc, r_t *r, int nr, count_t count, int depth){
 int i;
 int j;
 count_t l;
 if(count == NULL){
  return 0;
 }
 for(i=0;i<NCOUNT;i++){
  count[i] = 0;
 }
 for(i=0;i<nc;i++){
  count[cc[i]]++;
 }
 for(i=0;i<nc-1;i++){
  if(p_count_r(cc[i], cc[i+1], r, nr, l, depth)){
   return 1;
  }
  for(j=0;j<NCOUNT;j++){
   count[j] += l[j];
  }
 }
 return 0;
}

int cc_init(char **pcc, int *pnc){
 input_t input;
 int nc;
 int i;
 char c;
 if(input_init(input)){
  return 1;
 }
 nc = 0;
 while(!input_eol(input)){
  c = input_readchar(input);
  if(!isupper(c)){
   return 1;
  }
  nc++;
 }
 pcc[0] = malloc(sizeof(pcc[0][0]) * nc);
 if(pcc[0] == NULL){
  return 1;
 }
 if(input_init(input)){
  return 1;
 }
 i = 0;
 while(!input_eol(input)){
  c = input_readchar(input);
  if(!isupper(c)){
   return 1;
  }
  pcc[0][i] = c - 'A';
  i++;
 }
 pnc[0] = nc;
 return 0;
}

int rr_init(r_t **prr, int *pnr){
 int nr;
 int i;
 char c;
 input_t input;
 if(input_init(input)){
  return 1;
 }
 input_skipline(input);
 input_skipline(input);
 nr = 0;
 while(!input_endq(input)){
  input_skipline(input);
  nr++;
 }
 prr[0] = malloc(sizeof(prr[0][0]) * nr);
 if(prr[0] == NULL){
  return 1;
 }
 if(input_init(input)){
  return 1;
 }
 input_skipline(input);
 input_skipline(input);
 i = 0;
 while(!input_endq(input)){
  c = input_readchar(input);
  if(!isupper(c)){
   return 1;
  }
  prr[0][i][0] = c - 'A';
  c = input_readchar(input);
  if(!isupper(c)){
   return 1;
  }
  prr[0][i][1] = c - 'A';
  input_skipspace(input);
  input_skippunct(input);
  input_skipspace(input);
  c = input_readchar(input);
  if(!isupper(c)){
   return 1;
  }
  prr[0][i][2] = c - 'A';
  input_skipline(input);
  i++;
 }
 pnr[0] = nr;
 return 0;
}

int rr_print(r_t *rr, int nr){
 int i;
 for(i=0;i<nr;i++){
  printf("[%d][%d] -> [%d]\n", rr[i][0], rr[i][1], rr[i][2]);
 }
 return 0;
}

int cc_print(char *cc, int nc){
 int i;
 for(i=0;i<nc;i++){
  printf("[%d]", cc[i]);
 }
 printf("\n");
 return 0;
}
