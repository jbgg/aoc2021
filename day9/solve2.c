#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "input.h"

struct _hmap_t {
 int ni; /* number of rows */
 int nj; /* number of columns */
 char **h;
};
typedef struct _hmap_t hmap_t;
int hmap_init(hmap_t *);


struct _lowp_t {
 int p[2]; /* position */
};
typedef struct _lowp_t lowp_t;

struct _l_lowp_t {
 lowp_t lowp;
 struct _l_lowp_t *next;
};
typedef struct _l_lowp_t *l_lowp_t;

int hmap_lowpointq(hmap_t hm, int i, int j);
int hmap_getlowp(hmap_t, l_lowp_t *);
int l_lowp_print(l_lowp_t);

int solve(){

 hmap_t hmap;
 l_lowp_t l_lowp;
 l_lowp = NULL;

 hmap_init(&hmap);
 hmap_getlowp(hmap, &l_lowp);
 l_lowp_print(l_lowp);

 return 0;
}

int p_l_lowp_add(l_lowp_t *p_l_lp, int i, int j){
 p_l_lp[0] = (l_lowp_t)malloc(sizeof(struct _l_lowp_t));
 if(p_l_lp[0] == NULL){
  return 1;
 }
 p_l_lp[0]->lowp.p[0] = i;
 p_l_lp[0]->lowp.p[1] = j;

 return 0;
}

int hmap_getlowp(hmap_t hm, l_lowp_t *p_l_lp){
 int i;
 int j;
 int ni;
 int nj;

 ni = hm.ni;
 nj = hm.nj;

 for(i=0;i<ni;i++){
  for(j=0;j<nj;j++){
   if(hmap_lowpointq(hm, i, j)){
    p_l_lowp_add(p_l_lp, i, j);
    p_l_lp = &(p_l_lp[0]->next);
   }
  }
 }

 return 0;
}

int hmap_init(hmap_t *p_hmap){
 int i;
 int j;
 int ni;
 int nj;
 char c;
 char **h;
 if(p_hmap == NULL){
  return 1;
 }
 input_t input;
 if(input_init(input)){
  return 1;
 }
 /* read ni and nj */
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
 p_hmap->ni = ni;
 p_hmap->nj = nj;
 h = (char**)malloc(sizeof(char*)*ni);
 if(h == NULL){
  return 1;
 }
 for(i=0;i<ni;i++){
  h[i] = (char*)malloc(sizeof(char)*nj);
  if(h[i] == NULL){
   return 1;
  }
 }
 p_hmap->h = h;

 input_init(input);
 i = 0;
 while(!input_endq(input)){
  j = 0;
  if(i >= ni){
   return 1;
  }
  while(!input_eol(input)){
   c = input_readchar(input);
   if(j >= nj || !isdigit(c)){
    return 1;
   }
   h[i][j] = c - '0';
   j++;
  }
  input_skipline(input);
  i++;
 }

 return 0;
}

int hmap_lowpointq(hmap_t hm, int i, int j){
 int ni;
 int nj;
 char **h;
 ni = hm.ni;
 nj = hm.nj;
 h = hm.h;
 if(h == NULL){
  return 0;
 }
 if(i<0 || i>= ni){
  return 0;
 }
 if(j<0 || j>= nj){
  return 0;
 }
 if(i>0){
  if(h[i-1][j] <= h[i][j]){
   return 0;
  }
 }
 if(i<ni-1){
  if(h[i+1][j] <= h[i][j]){
   return 0;
  }
 }
 if(j>0){
  if(h[i][j-1] <= h[i][j]){
   return 0;
  }
 }
 if(j<nj-1){
  if(h[i][j+1] <= h[i][j]){
   return 0;
  }
 }
 return 1;
}

int l_lowp_print(l_lowp_t l_lowp){
 l_lowp_t l_lowp_it;
 l_lowp_it = l_lowp;
 while(l_lowp != NULL){
  printf("[%d,%d]\n", l_lowp->lowp.p[0], l_lowp->lowp.p[1]);
  l_lowp = l_lowp->next;
 }
 return 0;
}
