#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "input.h"

#define FLASHED (-1)

/* energy levels */
struct _e_t {
 int ni;
 int nj;
 int **d;
};
typedef struct _e_t e_t;

int e_init(e_t *p);
int e_print(e_t p);
int e_step(e_t *p, unsigned int *n);
int e_incresearound(e_t *p, int ci, int cj);

int solve(){

 e_t e;
 int step;
 unsigned int n;
 unsigned int count;

 if(e_init(&e)){
  return 1;
 }
 count = 0;
 for(step=0;step<100;step++){
  e_step(&e, &n);
  count += n;
 }
 printf("%d\n", count);

 return 0;
}
int e_init(e_t *p){
 input_t input;
 int ni;
 int nj;
 int i;
 int j;
 int c;

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
 input_init(input);
 i = 0;
 while(!input_endq(input)){
  if(i>=ni){
   return 1;
  }
  j = 0;
  while(!input_eol(input)){
   if(j>=nj){
    return 1;
   }
   c = input_readchar(input);
   if(!isdigit(c)){
    return 1;
   }
   p->d[i][j] = c - '0';
   j++;
  }
  input_skipline(input);
  i++;
 }

 return 0;
}

int e_print(e_t e){
 int i;
 int j;
 for(i=0;i<e.ni;i++){
  for(j=0;j<e.nj;j++){
   printf("%c", e.d[i][j] > 9 ? 'X' : '0' + e.d[i][j]);
  }
  printf("\n");
 }
 return 0;
}

int e_step(e_t *p, unsigned int *n){
 int i;
 int j;
 int ni;
 int nj;
 int count;
 if(n == NULL){
  return 1;
 }
 n[0] = 0;

 ni = p->ni;
 nj = p->nj;

 /* increasing 1 */
 for(i=0;i<ni;i++){
  for(j=0;j<nj;j++){
   p->d[i][j]++;
  }
 }

 /* flashing */
 do{
  count = 0;
  for(i=0;i<ni;i++){
   for(j=0;j<nj;j++){
    if(p->d[i][j] != FLASHED &&
      p->d[i][j] > 9){
     e_incresearound(p, i, j);
     p->d[i][j] = FLASHED;
     count++;
    } /* if */
   } /* for j */
  } /* for i */
  n[0] += count;
 }while(count>0);

 /* setting 0 energy level for flashed */
 for(i=0;i<ni;i++){
  for(j=0;j<nj;j++){
   if(p->d[i][j] == FLASHED){
    p->d[i][j] = 0;
   }
  }
 }

 return 0;
}

int e_incresearound(e_t *p, int ci, int cj){
 int i;
 int j;
 int i0;
 int i1;
 int j0;
 int j1;
 int ni;
 int nj;

 ni = p->ni;
 nj = p->nj;

 /* 
  * xxx
  * xCx
  * xxx
  */
 i0 = ci>0 ? ci-1 : ci;
 i1 = ci<ni-1 ? ci+1 : ci;
 j0 = cj>0 ? cj-1 : cj;
 j1 = cj<nj-1 ? cj+1 : cj;
 for(i=i0;i<=i1;i++){
  for(j=j0;j<=j1;j++){
   if(i != ci || j != cj){
    if(p->d[i][j] != FLASHED){
     p->d[i][j]++;
    }
   }
  }
 }

 return 0;
}
