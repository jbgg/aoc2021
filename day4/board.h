#ifndef __BOARD_H__
#define __BOARD_H__

#define N 5

#include "input.h"

struct _board_t {
 /* n saves the numbers in the board */
 int n[N][N];
 /* m saves marked numbers */
 int m[N][N];
 /* rowl counts numbers marked in a row */
 int rowm[N];
 /* colm counts numbers marked in a column */
 int colm[N];
 /* winq is 1 if already won */
 int winq;
};
typedef struct _board_t board_t[1];
typedef struct _board_t *board_p_t;

struct _boardlist_t {
 board_t board;
 struct _boardlist_t *next;
};
typedef struct _boardlist_t boardlist_t[1];
typedef struct _boardlist_t *boardlist_p_t;

int board_init(board_t);
int input_readboards(input_t input, boardlist_p_t *blistp, int *nb);
int board_winq(board_t b);
void board_print(board_t);
int board_mark(board_t board, int n);
void board_sumunmarked(board_t board, int *s);

#endif /* __BOARD_H__ */
