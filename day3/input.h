#ifndef __INPUT_H__
#define __INPUT_H__

#define NBITS 12

struct _input_t {
 char *p;
};
typedef struct _input_t input_t[1];

struct _line_t {
 char b[NBITS+1];
};
typedef struct _line_t line_t[1];

void input_print();
int input_init(input_t);
int input_readline(input_t input, line_t l);

int input_readnumber(input_t input, long *v);
int input_readword(input_t input, char *w, int s);
int input_readbinary(input_t input, char *w, int s);

int input_endq(input_t input);

void input_skipblank(input_t input);
void input_skipspace(input_t input);

#endif /* __INPUT_H__ */
