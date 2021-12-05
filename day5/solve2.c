#include <stdio.h>
#include <stdlib.h>

#include "input.h"

int addpoint(char **n, int i, int j){
 n[i][j]++;
 if(n[i][j] == 2){
  return 1;
 }
 return 0;
}

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
 int xd;
 int yd;
 int temp;

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
   if(y1 == y2){
    /* x1 == x2 && y1 == y2 */
    printf("?");
   }else{
    /* x1 == x2 && y1 != y2 */
    if(y1 > y2){
     temp = y2;
     y2 = y1;
     y1 = temp;
    }
    for(j=y1;j<=y2;j++){
     if(addpoint(n, x1, j)){
      count++;
     }
    }
   }
  }else{
   if(y1 == y2){
    /* x1 != x2 && y1 == y2 */
    if(x1 > x2){
     temp = x2;
     x2 = x1;
     x1 = temp;
    }
    for(i=x1;i<=x2;i++){
     if(addpoint(n, i, y1)){
      count++;
     }
    }
   }else{
    /* x1 != x2 && y1 != y2 */
    if(x1 > x2){
     temp = x2;
     x2 = x1;
     x1 = temp;
     temp = y2;
     y2 = y1;
     y1 = temp;
    }
    if(y2 > y1){
     yd = 1;
    }else{
     yd = -1;
    }
    j=y1;
    for(i=x1;i<=x2;i++){
     if(addpoint(n, i, j)){
      count++;
     }
     j+=yd;
    }

   }
  }
 }

 printf("%d\n", count);

 return 0;
}
