
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "input.h"

int input_readboards(input_t, boardlist_p_t*);

int solve(){

 input_t input;

 if(input_init(input)){
  return 1;
 }

 input_skipline(input);

 boardlist_p_t blist;
 blist = NULL;
 if(input_readboards(input, &blist)){
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
  //if(input_eolq(input)){
   //return 1;
  //}
 }

 return 0;
}


int input_readboards(input_t input, boardlist_p_t *blistp){

 boardlist_p_t *bpp;
 boardlist_p_t bp;
 bpp = blistp;

 input_skipblanklines(input);

 while(!input_endq(input)){

  bpp[0] = malloc(sizeof(boardlist_t));
  bp = bpp[0];
  /* boardlist init */
  board_init(bp->board);
  bp->next = NULL;

  /* read board */
  int i;
  int j;
  for(i=0;i<N;i++){
   for(j=0;j<N;j++){
    if(input_readnumber(input, &(bp->board->n[i][j]))){
     return 1;
    }
   }
   input_skipline(input);
  }

  bpp = &(bp->next);
  input_skipblanklines(input);

 } /* while */

 return 0;
}
