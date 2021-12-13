#ifndef __PAPER_H__
#define __PAPER_H__

#define NOMARKED '.'
#define MARKED '#'

#define FOLDX 'x'
#define FOLDY 'y'

struct _instr_t {
 char foldxy;
 int line;
 struct _instr_t *next;
};
typedef struct _instr_t instr_t;

struct _paper_t {
 char **m;
 int xmax;
 int ymax;
 instr_t *instr;
};
typedef struct _paper_t paper_t;

int paper_init(paper_t *p);
int paper_print(paper_t p);
int instr_add(instr_t **ipp, char c, int n);

#endif /* __PAPER_H__ */
