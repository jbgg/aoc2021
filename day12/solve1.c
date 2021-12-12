#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "input.h"

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
typedef struct _caves_t caves_t;
typedef struct _caves_t *p_caves_t;

int caves_init(p_caves_t *pp);
int caves_print(p_caves_t p);

int caves_addcaves(p_caves_t *pp, char *n1, char *n2);

int solve(){

 p_caves_t caves;

 caves = NULL;
 if(caves_init(&caves)){
  return 1;
 }

 caves_print(caves);

 return 0;
}

int cave_getid(char *n, int *p, cavetype_t *t){
 if(p == NULL || t == NULL){
  return 1;
 }
 if(strcmp(n, "start") == 0){
  p[0] = STARTID;
  t[0] = SMALL_CAVE;
  return 0;
 }
 if(strcmp(n, "end") == 0){
  p[0] = ENDID;
  t[0] = SMALL_CAVE;
  return 0;
 }
 if(strlen(n) != 2){
  return 1;
 }
 p[0] = GETID(n[0], n[1]);
 if(islower(n[0]) && islower(n[1])){
  t[0] = SMALL_CAVE;
 }else if(isupper(n[0]) && isupper(n[1])){
  t[0] = BIG_CAVE;
 }else{
  return 1;
 }
 return 0;
}

int conn_add(p_conn_t *pp, int idconn){
 while(pp[0] != NULL){
  if(pp[0]->id == idconn){
   return 0;
  }
  pp = &(pp[0]->next);
 }
 pp[0] = malloc(sizeof(pp[0][0]));
 pp[0]->id = idconn;
 pp[0]->next = NULL;
 return 0;
}

int caves_addcave(p_caves_t *pp, int id, cavetype_t t, int idconn){

 while(pp[0] != NULL){
  if(pp[0]->c.id == id && pp[0]->c.type == t){
   conn_add(&pp[0]->c.conn, idconn);
   break;
  }
  pp = &(pp[0]->next);
 }
 if(pp[0] == NULL){
  pp[0] = malloc(sizeof(pp[0][0]));
  pp[0]->c.id = id;
  pp[0]->c.type = t;
  pp[0]->c.conn = NULL;
  pp[0]->next = NULL;
  conn_add(&pp[0]->c.conn, idconn);
 }

 return 0;
}

int caves_addcaves(p_caves_t *pp, char *n1, char *n2){
 if(pp == NULL || n1 == NULL || n2 == NULL){
  return 1;
 }
 int id1;
 int id2;
 cavetype_t t1;
 cavetype_t t2;
 if(cave_getid(n1, &id1, &t1)){
  return 1;
 }
 if(cave_getid(n2, &id2, &t2)){
  return 1;
 }

 caves_addcave(pp, id1, t1, id2);
 caves_addcave(pp, id2, t2, id1);

 return 0;
}

int caves_init(p_caves_t *pp){
 char name1[6];
 char name2[6];
 if(pp == NULL){
  return 1;
 }
 input_t input;
 if(input_init(input)){
  return 1;
 }
 while(!input_endq(input)){
  if(input_readword(input, name1, 6, NULL)){
   return 1;
  }
  /* skip - */
  input_skippunct(input);
  if(input_readword(input, name2, 6, NULL)){
   return 1;
  }
  input_skipline(input);
  /*  */
  if(caves_addcaves(pp, name1, name2)){
   return 1;
  }
 }
 return 0;
}

int printid(int id){
 if(id == STARTID){
  printf("start");
 }else
  if(id == ENDID){
   printf("end");
  }else{
   printf("%c%c %d", id & 0xff, (id >> 8) & 0xff, id);
  }
}

int conn_print(p_conn_t p){
 while(p != NULL){
  printid(p->id);
  printf(",");
  p = p->next;
 }
 return 0;
}
int caves_print(p_caves_t p){
 
 while(p != NULL){
  printid(p->c.id);
  printf(": ");
  conn_print(p->c.conn);
  printf("\n");
  p = p->next;
 }

 return 0;
}
