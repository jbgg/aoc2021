#include <stdio.h>

#include "paper.h"

int solve(){

 paper_t paper;

 if(paper_init(&paper)){
  return 1;
 }

 while(paper.instr != NULL){
  if(paper_fold(&paper)){
   printf("fold failed\n");
   return 1;
  }
 }
 paper_print(paper);

 return 0;
}

