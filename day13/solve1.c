#include <stdio.h>

#include "paper.h"

int solve(){

 paper_t paper;

 if(paper_init(&paper)){
  return 1;
 }
 paper_print(paper);
 if(paper_fold(&paper)){
  printf("fold failed\n");
  return 1;
 }
 paper_print(paper);

 unsigned long count;
 if(paper_count(paper, &count)){
  printf("count failed\n");
  return 1;
 }
 printf("%d\n", count);

 return 0;
}

