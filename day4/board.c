
#include <stdio.h>

#include "board.h"

int board_init(board_t b){
 int i;
 int j;
 for(i=0;i<N;i++){
  b->rowm[i] = 0;
  for(j=0;j<N;j++){
   b->colm[j] = 0;
   b->m[i][j] = 0;
  }
 }
}

void board_print(board_t b){
 int i;
 int j;
 for(i=0;i<N;i++){
  for(j=0;j<N;j++){
   printf("%d ", b->n[i][j]);
  }
  printf("\n");
 }
}

/* return 1 if row or column is filled */
int board_mark(board_t board, int n){
 int i;
 int j;
 for(i=0;i<N;i++){
  for(j=0;j<N;j++){
   if(board->n[i][j] == n){
    board->rowm[i]++;
    board->colm[j]++;
    board->m[i][j] = 1;
    if(board->rowm[i] == N){
     return 1;
    }
    if(board->colm[j] == N){
     return 1;
    }
   }
  }
 }
 return 0;
}
void board_sumunmarked(board_t board, int *s){
 int i;
 int j;
 int ss;

 ss = 0;
 for(i=0;i<N;i++){
  for(j=0;j<N;j++){
   if(board->m[i][j] == 0){
    ss+=board->n[i][j];
   }
  }
 }

 if(s != NULL){
  s[0] = ss;
 }
}
