#include <stdio.h>

#include "polymer.h"

int solve(){

 char *cc;
 int nc;
 r_t *rr;
 int nr;
 int i;
 count_t count;
 int imin;
 int imax;

 cc = NULL;
 nc = 0;
 rr = NULL;
 nr = 0;

 if(cc_init(&cc, &nc)){
  return 1;
 }
 //cc_print(cc,nc);

 if(rr_init(&rr, &nr)){
  return 1;
 }
 //rr_print(rr,nr);
 
 for(i=0;i<NCOUNT;i++){
  count[i] = 0;
 }
 if(p_count(cc, nc, rr, nr, count, 10)){
  return 1;
 }

 imin = 0;
 imax = 0;
 for(i=0;i<NCOUNT;i++){
  if(count[imin] == 0 && count[i] != 0){
   imin = i;
  }
  if(count[i] != 0){
   if(count[i] < count[imin]){
    imin = i;
   }
  }
  if(count[i] > count[imax]){
   imax = i;
  }
 }

 printf("%llu\n", count[imax] - count[imin]);

 return 0;
}
