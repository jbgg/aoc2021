#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cave.h"
#include "input.h"

#define PATH_MAXLENGTH (256)

int caves_count2_r(p_caves_t p, cave_t *path[PATH_MAXLENGTH],
  int index, int smallrepq){

 int ret;
 int i;
 int validq;
 int smallrepqq;
 cave_t *c;

 c = path[index];
 conn_t *conn;

 if(c->id == ENDID){
  return 1;
 }

 if(index == (PATH_MAXLENGTH - 1)){
  /* !! */
  return 0;
 }
 ret = 0;
 conn = c->conn;
 while(conn != NULL){
  validq = 1;
  smallrepqq = smallrepq;
  if(conn->p->type == SMALL_CAVE){
   if(conn->p->id == STARTID){
    validq = 0;
   }else{
    for(i=0;i<=index;i++){
     if(path[i]->id == conn->p->id){
      if(smallrepq == 0){
       smallrepqq = 1;
      }else{
       validq = 0;
      }
      break;
     }
    }
   } /* if STARTID */
  } /* if SMALL_CAVE */
  if(validq){
   path[index+1] = conn->p;
   ret += caves_count2_r(p, path, index+1, smallrepqq);
  }
  conn = conn->next;
 }
 return ret;
}

int caves_count2(p_caves_t p, unsigned long *c){
 if(c == NULL){
  return 1;
 }
 cave_t *path[PATH_MAXLENGTH];
 p_cave_t q;
 if(caves_findbyid(p, STARTID, &q)){
  return 1;
 }

 path[0] = q;
 c[0] = caves_count2_r(p, path, 0, 0);
 return 0;
}

int caves_count_r(p_caves_t p, cave_t *path[PATH_MAXLENGTH], int index){

 int ret;
 cave_t *c;
 c = path[index];
 conn_t *conn;

 if(c->id == ENDID){
  return 1;
 }

 if(index == (PATH_MAXLENGTH - 1)){
  /* !! */
  return 0;
 }
 int i;
 int validq;
 ret = 0;
 conn = c->conn;
 while(conn != NULL){
  validq = 1;
  if(conn->p->type == SMALL_CAVE){
   for(i=0;i<=index;i++){
    if(path[i]->id == conn->p->id){
     validq = 0;
     break;
    }
   }
  }
  if(validq){
   path[index+1] = conn->p;
   ret += caves_count_r(p, path, index+1);
  }
  conn = conn->next;
 }
 return ret;
}

int caves_count(p_caves_t p, unsigned long *c){
 if(c == NULL){
  return 1;
 }
 cave_t *path[PATH_MAXLENGTH];
 p_cave_t q;
 if(caves_findbyid(p, STARTID, &q)){
  return 1;
 }

 path[0] = q;
 c[0] = caves_count_r(p, path, 0);
 return 0;
}

int caves_findbyid(p_caves_t p, int id, p_cave_t *q){
 if(q == NULL){
  return 1;
 }
 while(p!=NULL){
  if(p->c.id == id){
   q[0] = &(p->c);
   return 0;
  }
  p = p->next;
 }
 return 1;
}

int caves_fill(p_caves_t p){
 p_caves_t pinit;
 conn_t *conn;
 cave_t *q;
 pinit = p;
 while(p != NULL){
  conn = p->c.conn;
  while(conn != NULL){
   if(caves_findbyid(pinit, conn->id, &q)){
    return 1;
   }
   conn->p = q;
   conn = conn->next;
  }
  p = p->next;
 }
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
 pp[0]->p = NULL;
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
  printid(p->p->id);
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
