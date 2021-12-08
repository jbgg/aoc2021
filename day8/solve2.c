#include <stdio.h>
#include <stdlib.h>

#include "input.h"

/* TODO: change n for size */
struct _seg_t {
 int s;
 int n;
};
typedef struct _seg_t seg_t;

typedef seg_t segs_t[10];

int solve(){

 input_t input;
 if(input_init(input)){
  return 1;
 }

 int i;
 int j;
 unsigned int count;
 int size;
 char s[8];
 int i5;
 int i6;
 int index;
 segs_t segs;
 count = 0;
 while(!input_endq(input)){

  i5 = 3;
  i6 = 6;
  for(i=0;i<10;i++){
   input_readword(input, s, 8, &size);

   if(size <= 4){
    index = size - 2;
   }else if(size==5){
    index = i5;
    i5++;
   }else if(size==6){
    index = i6;
    i6++;
   }else if(size==7){
    index = 9;
   }else{
    printf("!");
   }
   /* save it */
   segs[index].n = size;
   segs[index].s = 0;
   for(j=0;j<size;j++){
    segs[index].s |= 1 << (s[j] - 'a');
   }

   input_skipblank(input);
  }

  input_skippunct(input);

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
