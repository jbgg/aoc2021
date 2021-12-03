
#include <stdio.h>
#include "input.h"

void line_getbinary(line_t l, int *o){
 if(o == NULL){
  return;
 }
 int i;
 int ret;
 ret = 0;
 for(i=0;i<NBITS;i++){
  ret <<= 1;
  if(l->b[i] == '1'){
   ret |= 1;
  }
 }
 o[0] = ret;
}

int criteriaq(line_t l, char c[NBITS], int bi){
 int i;
 for(i=0;i<bi;i++){
  if(l->b[i] != c[i]){
   return 0;
  }
 }
 return 1;
}

int solve(){
 input_t input;
 line_t l;

 int bi; /* bit index */
 /* *_c saves the criteria */
 char o_c[NBITS] = {0, };
 char co2_c[NBITS] = {0, };
 /* *_cc is for counting '0' and '1' */
 int o_cc;
 int co2_cc;

 /* first bit */
 bi = 0;
 o_cc = 0;
 co2_cc = 0;
 if(input_init(input)){
  return 1;
 }
 while(!input_endq(input)){
  if(input_readline(input, l)){
   return 1;
  }
  if(l->b[bi] == '1'){
   o_cc++;
  }else{
   o_cc--;
  }
 }

 /* save criteria for index bi=0 */
 if(o_cc >= 0){
  o_c[bi] = '1';
 }else{
  o_c[bi] = '0';
 }
 /* using o_cc for co2 (because first bit) */
 if(o_cc >= 0){
  co2_c[bi] = '0';
 }else{
  co2_c[bi] = '1';
 }

 /* *_n is used for counting the numbers verifying criteria */
 int o_n;
 int co2_n;
 /* *_lasti is the index such that only one number left */
 int o_lasti = NBITS;
 int co2_lasti = NBITS;

 /* for bi=1,...,NBITS-1  */
 bi++;
 while(bi<NBITS){
  o_n=0;
  co2_n=0;
  o_cc = 0;
  co2_cc = 0;
  input_init(input);
  while(!input_endq(input)){
   /* don't check errors because it has been checked it before */
   input_readline(input, l);
   if(bi < o_lasti){
    /* if one left */
    if(criteriaq(l, o_c, bi)){
     /* if this number verifies criteria */
     o_n++;
     if(l->b[bi] == '1'){
      o_cc++;
     }else{
      o_cc--;
     }
    }
   }
   if(bi < co2_lasti){
    /* if one left */
    if(criteriaq(l, co2_c, bi)){
     /* if this number verifies criteria */
     co2_n++;
     if(l->b[bi] == '1'){
      co2_cc++;
     }else{
      co2_cc--;
     }
    }
   }
  }
  if(o_n == 1){
   /* one number left */
   o_lasti = bi;
  }else{
   /* otherwise save the criteria for current bit index */ 
   if(o_cc >= 0){
    o_c[bi] = '1';
   }else{
    o_c[bi] = '0';
   }
  }
  if(co2_n == 1){
   /* one number left */
   co2_lasti = bi;
  }else{
   /* otherwise save the criteria for current bit index */ 
   if(co2_cc >= 0){
    co2_c[bi] = '0';
   }else{
    co2_c[bi] = '1';
   }
  }
  bi++;
 }
 
 /* o and co2 are the rating */
 int o;
 int co2;

 o_n=0;
 co2_n=0;
 input_init(input);
 while(!input_endq(input)){
  input_readline(input, l);
   if(criteriaq(l, o_c, o_lasti)){
    /* if this number verifies criteria */
    o_n++;
    /* read binary number to o */
    line_getbinary(l, &o);
   }
   if(criteriaq(l, co2_c, co2_lasti)){
    /* if this number verifies criteria */
    co2_n++;
    /* read binary number to co2 */
    line_getbinary(l, &co2);
   }
 }

 if(o_n != 1 || co2_n != 1){
  /* there is no solution :( */
  printf("!!\n");
 }else{
  printf("%d\n", o*co2);
 }

 return 0;
}
