
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
 //c_co2[bi] = c_o[bi];

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

 int o_n;
 int o_lasti = NBITS;

 int co2_n;
 int co2_lasti = NBITS;

 /*  */
 bi++;
 while(bi<NBITS){
  o_n=0;
  o_cc = 0;
  co2_n=0;
  co2_cc = 0;
  input_init(input);
  while(!input_endq(input)){
   if(input_readline(input, l)){
    return 1;
   }
   if(bi < o_lasti){
    if(criteriaq(l, o_c, bi)){
     /* this line verifies criteria */
     o_n++;
     if(l->b[bi] == '1'){
      o_cc++;
     }else{
      o_cc--;
     }
    }
   }
   if(bi < co2_lasti){
    if(criteriaq(l, co2_c, bi)){
     /* this line verifies criteria */
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
   o_lasti = bi;
  }else{
   if(o_cc >= 0){
    o_c[bi] = '1';
   }else{
    o_c[bi] = '0';
   }
  }

  if(co2_n == 1){
   co2_lasti = bi;
  }else{
   if(co2_cc >= 0){
    co2_c[bi] = '0';
   }else{
    co2_c[bi] = '1';
   }
  }

  bi++;
 }
 
 int o;
 int co2;

 o_n=0;
 co2_n=0;
 input_init(input);
 while(!input_endq(input)){
  if(input_readline(input, l)){
   return 1;
  }
   if(criteriaq(l, o_c, o_lasti)){
    /* this line verifies criteria */
    o_n++;
    /* read binary to o */
    line_getbinary(l, &o);
   }
   if(criteriaq(l, co2_c, co2_lasti)){
    /* this line verifies criteria */
    co2_n++;
    /* read binary to o */
    line_getbinary(l, &co2);
   }
 }


 printf("%d\n", o*co2);

 return 0;
}
