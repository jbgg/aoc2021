
#ifndef __CAVE_H__
#define __CAVE_H__

#define STARTID (-1)
#define ENDID (1)
#define GETID(_c1,_c2) ((_c1) | ((_c2) << 8))

enum _cavetype_t {
 SMALL_CAVE,
 BIG_CAVE
};
typedef enum _cavetype_t cavetype_t;

struct _conn_t {
 int id;
 struct _cave_t *p;
 struct _conn_t *next;
};
typedef struct _conn_t conn_t;
typedef struct _conn_t *p_conn_t;

struct _cave_t {
 int id;
 conn_t *conn;
 cavetype_t type;
};

struct _caves_t {
 struct _cave_t c;
 struct _caves_t *next;
};
typedef struct _cave_t cave_t;
typedef struct _cave_t *p_cave_t;
typedef struct _caves_t caves_t;
typedef struct _caves_t *p_caves_t;

int cave_getid(char *n, int *p, cavetype_t *t);
int conn_add(p_conn_t *pp, int idconn);
int caves_addcave(p_caves_t *pp, int id, cavetype_t t, int idconn);
int caves_addcaves(p_caves_t *pp, char *n1, char *n2);
int caves_init(p_caves_t *pp);
int printid(int id);
int conn_print(p_conn_t p);
int caves_print(p_caves_t p);
int caves_findbyid(p_caves_t p, int id, p_cave_t *q);

int caves_fill(p_caves_t p);
int caves_count(p_caves_t p, unsigned long *c);

#endif /* __CAVE_H__ */
