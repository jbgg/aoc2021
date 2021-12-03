
#include <stdio.h>
#include "input.h"

int solve(){
 int i;
 input_t input;
 line_t l;
 int c[NBITS] = {0,};
 int grate;
 int erate;
 int pc;

 if(input_init(input)){
  return 1;
 }
 while(!input_endq(input)){
  if(input_readline(input, l)){
   return 1;
  }
  for(i=0;i<NBITS;i++){
   if(l->b[i] == '1'){
    c[i]++;
   }else{ /* l->b[i] == '0' */
    c[i]--;
   }
  }
 }

 for(i=0;i<NBITS;i++){
  if(c[i] == 0){
   printf("!\n");
   return 1;
  }
 }

 grate = 0;
 erate = 0;
 for(i=0;i<NBITS;i++){
  grate <<=1;
  erate <<=1;
  if(c[i]>0){
   grate |= 1;
  }else{
   erate |= 1;
  }
 }

 pc = grate*erate;
 printf("%d\n", pc);
 return 0;
}
