#include <stdio.h>
#include <stdlib.h>

#include "input.h"

unsigned int countsum(int d, int s){

 int i;
 unsigned int c;
 c = 1;
 for(i=s;i<=80;i++){
  if(d == 0){
   c += countsum(8, i+1);
   d = 6;
  }else{
   d--;
  }
 }

 return c;
}

int solve(){

 input_t input;
 if(input_init(input)){
  return 1;
 }

 unsigned int count;
 int d;

 count = 0;
 while(input_readnumber(input, &d) == 0){

  count += countsum(d, 1);

  input_skippunct(input);
 }

 printf("%u\n", count);

 return 0;
}
