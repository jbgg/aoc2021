
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "input.h"

int solve(){

 input_t input;

 if(input_init(input)){
  return 1;
 }

 input_skipline(input);

 boardlist_p_t blist;
 blist = NULL;
 if(input_readboards(input, &blist, NULL)){
  return 1;
 }

 int n;
 int s;
 input_init(input);
 while(1){
  if(input_readnumber(input, &n)){
   printf("end??\n");
   return 1;
  }

  boardlist_p_t bp;
  bp = blist;
  while(bp!=NULL){
   if(board_mark(bp->board, n)){
    board_sumunmarked(bp->board, &s);
    printf("%d\n", s * n);
    return 0;
   }
   bp = bp->next;
  }

  input_skippunct(input);
 }

 return 0;
}
