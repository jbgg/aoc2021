#include <stdio.h>
#include <stdlib.h>

#include "input.h"

/* 
 * 0: 6
 * 1: 2 *
 * 2: 5
 * 3: 5
 * 4: 4 *
 * 5: 5
 * 6: 6
 * 7: 3 *
 * 8: 7 *
 * 9: 6
 */

int solve(){

 input_t input;
 if(input_init(input)){
  return 1;
 }

 int i;
 unsigned int count;
 int size;
 char s[8];
 count = 0;
 while(!input_endq(input)){

  while(input_readchar(input) != '|')
   ;

  for(i=0;i<4;i++){
   input_skipblank(input);
   input_readword(input, s, 8, &size);
   if(size == 2 || size == 3 || size == 4 || size == 7){
    count++;
   }
  }
  input_skipspace(input);
 }

 printf("%d\n", count);

 return 0;
}
