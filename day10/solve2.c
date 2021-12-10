#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "input.h"

struct _l_ulong_t {
 unsigned long ul;
 struct _l_ulong_t *next;
};
typedef struct _l_ulong_t *l_ulong_t;

int l_ulong_getbyindex(l_ulong_t l, int index, unsigned long *pul){
 int i;
 if(pul == NULL){
  return 1;
 }
 i = 0;
 while(l != NULL){
  if(i == index){
   pul[0] = l->ul;
   return 0;
  }
  i++;
  l = l->next;
 }
 return 1;
}

int l_ulong_sortadd(l_ulong_t *p, unsigned long ul){
 l_ulong_t l;
 l_ulong_t lprev;
 l_ulong_t lnew;

 if(p == NULL){
  return 1;
 }
 l = p[0];
 lprev = NULL;
 while(l!=NULL && l->ul < ul){
  lprev = l;
  l = l->next;
 }
 lnew = malloc(sizeof(struct _l_ulong_t));
 if(lnew == NULL){
  return 1;
 }
 lnew->ul = ul;
 lnew->next = l;
 if(lprev == NULL){
  p[0] = lnew;
 }else{
  lprev->next = lnew;
 }
 return 0;
}

int l_ulong_print(l_ulong_t l_ul){
 while(l_ul != NULL){
  printf("%llu\n", l_ul->ul);
  l_ul = l_ul->next;
 }
 return 0;
}

int solve(){

 input_t input;
 if(input_init(input)){
  return 1;
 }

 int nlinemax;
 int n;
 char c;

 nlinemax = 0;
 while(!input_endq(input)){
  n = 0;
  while(!input_eol(input)){
   c = input_readchar(input);
   if( c!='(' && c!=')' &&
     c!='[' && c!=']' &&
     c!='{' && c!='}' &&
     c!='<' && c!='>'){
    return 1;
   }
   n++;
  }
  if(n > nlinemax){
   nlinemax = n;
  }
  input_skipline(input);
 }

 input_init(input);

 int i;
 char *l;

 l = malloc(sizeof(char)*(nlinemax+1));
 if(l == NULL){
  return 1;
 }

 unsigned long linepoint;
 int nlinepoints;
 l_ulong_t linepoints;
 linepoints = NULL;
 int illegalq;
 int ni;

 nlinepoints = 0;
 while(!input_endq(input)){
  i = 0;
  illegalq = 0;
  while(!input_eol(input)){
   c = input_readchar(input);
   if( c=='(' || c=='[' || c=='{' || c=='<'){
    l[i] = c;
    i++;
   }else{
    if(i>0 &&
      ((c==')' && l[i-1]=='(') ||
       (c==']' && l[i-1]=='[') ||
       (c=='}' && l[i-1]=='{') ||
       (c=='>' && l[i-1]=='<'))){
     i--;
    }else{
    /* illegal character */
     illegalq = 1;
     break;
    }
   }
  }
  if(illegalq == 0){
   ni = i;
   linepoint = 0;
   for(i=ni-1;i>=0;i--){
    if(l[i] == ')' || l[i] == ']' ||
      l[i] == '}' || l[i] == '>'){
     printf("!");
    }
    if(l[i] == '('){
     linepoint *= 5;
     linepoint += 1;
    }
    if(l[i] == '['){
     linepoint *= 5;
     linepoint += 2;
    }
    if(l[i] == '{'){
     linepoint *= 5;
     linepoint += 3;
    }
    if(l[i] == '<'){
     linepoint *= 5;
     linepoint += 4;
    }
   }
   l_ulong_sortadd(&linepoints, linepoint);
   nlinepoints++;
  }
  input_skipline(input);
 }

 if(l_ulong_getbyindex(linepoints, nlinepoints/2, &linepoint)){
  return 1;
 }
 printf("%llu\n", linepoint);

 return 0;
}
