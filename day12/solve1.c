#include <stdio.h>

#include "cave.h"

int solve(){

 p_caves_t caves;

 caves = NULL;
 if(caves_init(&caves)){
  return 1;
 }

 caves_print(caves);

 return 0;
}

