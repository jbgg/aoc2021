
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

 int nboards;
 boardlist_p_t blist;
 blist = NULL;
 if(input_readboards(input, &blist, &nboards)){
  return 1;
 }

 int n;
 int s;
 int nwin;
 int score;
 nwin = 0;
 input_init(input);
 while(!input_eol(input)){
  if(input_readnumber(input, &n)){
   printf("end??\n");
   return 1;
  }

  boardlist_p_t bp;
  bp = blist;
  while(bp!=NULL){
   if(!board_winq(bp->board)){
    if(board_mark(bp->board, n)){
     board_sumunmarked(bp->board, &s);
     score = s*n;
     nwin++;
    }
   }
   bp = bp->next;
  }

  input_skippunct(input);
 }

 printf("%d\n", score);

 return 0;
}
