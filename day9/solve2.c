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

int solve(){

 hmap_t hmap;

 hmap_init(&hmap);

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
