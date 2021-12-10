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
char hmap_heightq(hmap_t hm, int i, int j){
 int ni;
 int nj;
 char **h;
 ni = hm.ni;
 nj = hm.nj;
 h = hm.h;
 if(i<0 || i>=ni){
  return -1;
 }
 if(j<0 || j>=nj){
  return -1;
 }
 return h[i][j];
}

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
int p_l_lowp_add(l_lowp_t *p_l_lp, int i, int j);
int l_lowp_print(l_lowp_t);

struct _l_int_t {
 int d;
 struct _l_int_t *next;
};
typedef struct _l_int_t *l_int_t;
int p_l_int_add(l_int_t *p_l_lp, int d);
int l_int_print(l_int_t);

int basin_size(hmap_t hm, int i, int j, int *p_s);

int solve(){

 hmap_t hmap;
 l_lowp_t l_lowp;
 l_lowp = NULL;

 hmap_init(&hmap);
 hmap_getlowp(hmap, &l_lowp);

 //l_lowp_print(l_lowp);

 l_int_t l_sizes;
 l_sizes = NULL;

 int size;
 l_int_t *p_l_i;
 l_lowp_t l_lowp_it;

 l_lowp_it = l_lowp;
 p_l_i = &l_sizes;
 while(l_lowp_it != NULL){
  basin_size(hmap, l_lowp_it->lowp.p[0], l_lowp_it->lowp.p[1],
    &size);
  p_l_int_add(p_l_i, size);
  p_l_i = &(p_l_i[0]->next);
  l_lowp_it = l_lowp_it->next;
 }

 l_int_print(l_sizes);

 return 0;
}

struct _l_points_t {
 int p[2];
 struct _l_points_t *next;
};
typedef struct _l_points_t *l_points_t;

int points_add(l_points_t *p_l_points, int i, int j){
 while(p_l_points[0] != NULL){
  if(p_l_points[0]->p[0] == i &&
    p_l_points[0]->p[1] == j){
   return 0;
  }
  p_l_points = &(p_l_points[0]->next);
 }
 p_l_points[0] = malloc(sizeof(struct _l_points_t));
 if(p_l_points[0] == NULL){
  return 1;
 }
 p_l_points[0]->p[0] = i;
 p_l_points[0]->p[1] = j;
 return 0;
}

int l_points_print(l_points_t l_p){
 while(l_p != NULL){
  printf("[%d,%d] ", l_p->p[0], l_p->p[1]);
  l_p = l_p->next;
 }
 printf("\n");
 return 0;
}

int basin_size(hmap_t hm, int i, int j, int *p_s){
 int ii;
 int jj;
 int h0;
 int l;
 l_points_t l_points_it;

 if(p_s == NULL){
  return 1;
 }

 l_points_t l_points[9];
 for(h0=0;h0<9;h0++){
  l_points[h0] = NULL;
 }
 h0 = hm.h[i][j];
 points_add(&l_points[h0], i, j);

 h0++;
 while(h0<=8){
  l_points_it = l_points[h0-1];
  while(l_points_it != NULL){
   ii = l_points_it->p[0];
   jj = l_points_it->p[1];
   if(hmap_heightq(hm, ii-1, jj) == h0){
    points_add(&l_points[h0], ii-1, jj);
   }
   if(hmap_heightq(hm, ii+1, jj) == h0){
    points_add(&l_points[h0], ii+1, jj);
   }
   if(hmap_heightq(hm, ii, jj-1) == h0){
    points_add(&l_points[h0], ii, jj-1);
   }
   if(hmap_heightq(hm, ii, jj+1) == h0){
    points_add(&l_points[h0], ii, jj+1);
   }
   l_points_it = l_points_it->next;
  }
  h0++;
 }

 int size;

 size = 0;
 for(h0=0;h0<9;h0++){
  l_points_it = l_points[h0];
  while(l_points_it != NULL){
   //printf(" [%d,%d] (%d)", l_points_it->p[0], l_points_it->p[1], h0);
   size++;
   l_points_it = l_points_it->next;
  }
 }
 //printf("\n");

 p_s[0] = size ;
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

int p_l_lowp_add(l_lowp_t *p_l_lp, int i, int j){
 p_l_lp[0] = (l_lowp_t)malloc(sizeof(struct _l_lowp_t));
 if(p_l_lp[0] == NULL){
  return 1;
 }
 p_l_lp[0]->lowp.p[0] = i;
 p_l_lp[0]->lowp.p[1] = j;
 return 0;
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

int p_l_int_add(l_int_t *p_l_i, int d){
 p_l_i[0] = (l_int_t)malloc(sizeof(struct _l_int_t));
 if(p_l_i[0] == NULL){
  return 1;
 }
 p_l_i[0]->d = d;
 return 0;
}
int l_int_print(l_int_t l_int){
 l_int_t l_int_it;
 l_int_it = l_int;
 while(l_int != NULL){
  printf("%d\n", l_int->d);
  l_int = l_int->next;
 }
 return 0;
}
