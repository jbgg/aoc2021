#include <stdio.h>
#include <stdlib.h>

#include "input.h"

struct _seg_t {
 int s;
 int size;
 int n;
};
typedef struct _seg_t seg_t;

typedef seg_t segs_t[10];

int segs_init(segs_t segs){
 int i;
 for(i=0;i<10;i++){
  segs[i].s = 0;
  segs[i].size = 0;
  segs[i].n = -1;
 }
 return 0;
}

int segs_add(segs_t segs, char *s, int size){
 int i;
 int index;
 if(size<=4){
  index = size-2;
 }else if(size == 5){
  index = 3;
 }else if(size == 6){
  index = 6;
 }else if(size == 7){
  index = 9;
 }else{
  printf("!");
  return 1;
 }
 while(segs[index].size != 0){
  index++;
 }
 segs[index].size = size;
 for(i=0;i<size;i++){
  segs[index].s |= 1 << (s[i] - 'a');
 }
 return 0;
}

int segs_decode(segs_t segs){
 int i;
 int s13;
 int ii;

 segs[0].n = 1; /* size = 2 */
 segs[1].n = 7; /* size = 3 */
 segs[2].n = 4; /* size = 4 */
 segs[9].n = 8; /* size = 7 */

 s13 = (segs[2].s &  ~(segs[0].s));

 for(i=3;i<=5;i++){
  if((segs[i].s | segs[0].s) == segs[i].s){
   segs[i].n = 3;
  }
  if((segs[i].s | s13) == segs[i].s){
   segs[i].n = 5;
  }
 }
 for(i=3;i<=5;i++){
  if(segs[i].n == -1){
   segs[i].n = 2;
   break;
  }
 }

 for(i=6;i<=8;i++){
  if((segs[i].s | segs[2].s) == segs[i].s){
   segs[i].n = 9;
   ii = i;
   break;
  }
 }
 for(i=6;i<=8;i++){
  if(i != ii){
   if((segs[i].s | segs[0].s) == segs[i].s){
    segs[i].n = 0;
    break;
   }
  }
 }
 for(i=6;i<=8;i++){
  if(segs[i].n == -1){
   segs[i].n = 6;
   break;
  }
 }

 /* DEBUG */
 for(i=0;i<10;i++){
  printf("%d(%d), ", segs[i].n, segs[i].size);
 }
 printf("\n");
 return 0;
}

int segs_getn(segs_t segs, char *s, int size, int *ret){

 int i;
 int ss;

 if(size<=4){
  ret[0] = segs[size-2].n;
  return 0;
 }

 if(size==7){
  ret[0] = segs[9].n;
  return 0;
 }

 ss = 0;
 for(i=0;i<size;i++){
  ss |= 1 << (s[i] - 'a');
 }

 if(size==5){
  for(i=3;i<=5;i++){
   if(segs[i].s == ss){
    ret[0] = segs[i].n;
    return 0;
   }
  }
  return 1;
 }

 if(size==6){
  for(i=6;i<=8;i++){
   if(segs[i].s == ss){
    ret[0] = segs[i].n;
    return 0;
   }
  }
  return 1;
 }

 return 1;
}

int solve(){

 input_t input;
 if(input_init(input)){
  return 1;
 }

 int i;
 unsigned int count;
 unsigned int v;
 int vv;
 char s[8];
 int size;
 segs_t segs;
 count = 0;
 while(!input_endq(input)){

  segs_init(segs);

  /* read all numbers */
  for(i=0;i<10;i++){
   input_readword(input, s, 8, &size);
   if(segs_add(segs, s, size)){
    return 1;
   }
   input_skipblank(input);
  }

  /* decode */
  if(segs_decode(segs)){
   return 1;
  }

  /* skip '|' */
  input_skippunct(input);

  /* read numbers after '|' */
  v = 0;
  for(i=0;i<4;i++){
   input_skipblank(input);
   input_readword(input, s, 8, &size);
   v *= 10;
   if(segs_getn(segs, s, size, &vv)){
    printf("!");
    return 1;
   }
   v += vv;
  }

  printf("%d\n", v);

  count += v;
  input_skipspace(input);
 }

 printf("%d\n", count);

 return 0;
}
