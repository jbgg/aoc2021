#include <stdio.h>
#include <stdlib.h>

#include "input.h"

int solve(){

 input_t input;
 if(input_init(input)){
  return 1;
 }

 int x1;
 int y1;
 int x2;
 int y2;
 int xmax;
 int ymax;
 int nline;
 nline=0;
 xmax=0;
 ymax=0;
 while(!input_endq(input)){

  input_readnumber(input, &x1);
  input_skippunct(input);
  input_readnumber(input, &y1);

  input_skipblank(input);
  input_skippunct(input);
  input_skipblank(input);

  input_readnumber(input, &x2);
  input_skippunct(input);
  input_readnumber(input, &y2);

  input_skipline(input);

  if(x1 > xmax){
   xmax = x1;
  }
  if(x2 > xmax){
   xmax = x2;
  }
  if(y1 > ymax){
   ymax = y1;
  }
  if(y2 > ymax){
   ymax = y2;
  }

  nline++;
 }

 int i;
 int j;
 char **n;
 n = malloc((xmax+1) * sizeof(char*));
 if(n == NULL){
  return 1;
 }
 for(i=0;i<=xmax;i++){
  n[i] = malloc((ymax+1) * sizeof(char));
  if(n[i] == NULL){
   return 1;
  }
  for(j=0;j<=ymax;j++){
   n[i][j] = 0;
  }
 }

 int count;
 int xb,xu;
 int yb,yu;

 count = 0;
 input_init(input);
 while(!input_endq(input)){
  input_readnumber(input, &x1);
  input_skippunct(input);
  input_readnumber(input, &y1);
  input_skipblank(input);
  input_skippunct(input);
  input_skipblank(input);
  input_readnumber(input, &x2);
  input_skippunct(input);
  input_readnumber(input, &y2);
  input_skipline(input);

  if(x1 == x2){
   if(y1 > y2){
    yb = y2;
    yu = y1;
   }else{
    yb = y1;
    yu = y2;
   }
   for(j=yb;j<=yu;j++){
    n[x1][j]++;
    if(n[x1][j] == 2){
     count++;
    }
   }
  }

  if(y1 == y2){
   if(x1 > x2){
    xb = x2;
    xu = x1;
   }else{
    xb = x1;
    xu = x2;
   }
   for(i=xb;i<=xu;i++){
    n[i][y1]++;
    if(n[i][y1] == 2){
     count++;
    }
   }
  }

 }

 printf("%d\n", count);

 return 0;
}
