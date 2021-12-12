#include <stdio.h>

#include "cave.h"

int solve(){

 p_caves_t caves;
 unsigned long count;

 caves = NULL;
 if(caves_init(&caves)){
  return 1;
 }

 cave_t *start;
 if(caves_fill(caves)){
  return 1;
 }

 count = 0;
 if(caves_count2(caves, &count)){
  return 1;
 }

 printf("%llu\n", count);

 return 0;
}

