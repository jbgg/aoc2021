
#include <stdio.h>
#include "input.h"

int solve(){
 input_t input;
 line_t l;

 if(input_init(input)){
  return 1;
 }

 while(!input_endq(input)){
  if(input_readline(input, l)){
   return 1;
  }

 }

 return 0;
}
