#include <stdio.h>
#include <stdlib.h>

#include "input.h"

#define NDAYS 256
#define VMAX 8
unsigned long cc[NDAYS+1][VMAX+1];
#define CP_NO 0
#define CP_YES 1
char cp[NDAYS+1][VMAX+1];

unsigned long countsum(int d, int s){

 int i;
 unsigned long c;
 if(s <= NDAYS){
  if(cp[s][d] == CP_NO){
   /* compute it */
   c = 1;
   for(i=s+d;i<=NDAYS;i+=7){
    c += countsum(8, i+1);
   }
   cc[s][d] = c;
   cp[s][d] = CP_YES;
  }else if(cp[s][d] == CP_YES){
   /* already computed */
   return cc[s][d];
  }
 }else{
  /* s > NDAYS */
  return 0;
 }
 return c;
}

int solve(){

 input_t input;
 if(input_init(input)){
  return 1;
 }
 int i;
 int j;

 for(i=0;i<=NDAYS;i++){
  for(j=0;j<=VMAX;j++){
   cp[i][j] = CP_NO;
  }
 }

 unsigned long countbyd[9];
 for(i=0;i<=8;i++){
  countbyd[i] = countsum(i, 0);
 }

 unsigned long count;
 int d;

 count = 0;
 while(input_readnumber(input, &d) == 0){
  count += countbyd[d];
  input_skippunct(input);
 }

 printf("%llu\n", count);

 return 0;
}
