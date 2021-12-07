#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "input.h"

struct _pos_t {
 int x;
 int cost;
 struct _pos_t *next;
};

typedef struct _pos_t pos_t;
typedef struct _pos_t *pos_p_t;

int setcost(pos_p_t p, pos_p_t *pp){
 if(pp==NULL){
  return 1;
 }
 int cost;
 int d;
 int x;
 x = p->x;
 cost = 0;
 while(pp[0] != NULL){
  d = pp[0]->x - x;
  cost += d >= 0 ? d : -d;
  pp = &(pp[0]->next);
 }
 p->cost = cost;
 return 0;
}

int newnode(pos_p_t *pp, int x){
 if(pp == NULL){
  return 1;
 }
 pp[0] = malloc(sizeof(pos_t));
 if(pp[0] == NULL){
  return 1;
 }
 pp[0]->x = x;
 pp[0]->cost = 0;
 pp[0]->next = NULL;
 return 0;
}

int solve(){

 input_t input;
 if(input_init(input)){
  return 1;
 }

 pos_p_t p;
 p = NULL;
 int x;
 pos_p_t *next;
 next = &p;
 while(!input_eol(input)){
  if(input_readnumber(input, &x)){
   return 1;
  }
  if(newnode(next, x)){
   return 1;
  }
  next = &(next[0]->next);
  input_skippunct(input);
 }

 int cost = INT_MAX;
 next = &p;
 while(next[0] != NULL){
  if(setcost(next[0], &p)){
   printf("!");
   return 1;
  }
  if(next[0]->cost < cost){
   cost = next[0]->cost;
  }
  next = &(next[0]->next);
 }

 printf("%d\n", cost);

 return 0;
}
