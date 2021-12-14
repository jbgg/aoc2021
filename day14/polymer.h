
#ifndef __POLYMER_H__
#define __POLYMER_H__

#define NCOUNT ('Z' - 'A' + 1)

#define TCOUNT_NO 0
#define TCOUNT_YES 1

#define MAXDEPTH 41

struct _tcount_t {
 unsigned long count[NCOUNT];
 char calq;
};
typedef struct _tcount_t tcount_t;

typedef char r_t[3];
typedef unsigned long count_t[NCOUNT];

int tcount_init();

int p_count_r(char c1, char c2, r_t *r, int nr, count_t count, int depth);
int p_count(char *cc, int nc, r_t *r, int nr, count_t count, int depth);

int cc_init(char **pcc, int *pnr);
int cc_print(char *cc, int nc);

int r_match(int c1, int c2, r_t *r, int nr, char *c);
int rr_init(r_t **prr, int *pnr);
int rr_print(r_t *rr, int nr);

#endif /* __POLYMER_H__ */
