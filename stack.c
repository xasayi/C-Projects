#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack* create_stack(void){
  struct stack* e_stack = malloc(sizeof(struct stack));
  if (e_stack == NULL){
    return NULL;
  }
  else{
    e_stack -> size = 0;
    e_stack -> top = NULL;
    return e_stack;
  }
}

void delete_stack(struct stack* s){
  if (s != NULL){
    struct stack_entry* t = s -> top;
    struct stack_entry* ne;
    while (t != NULL){
      ne = t -> next;
      free(t);
      t = ne;
    }
  free(ne);
  }
  free(s);
}
double pop(struct stack* s){
  if (s == NULL){
    return 0;
  }
  else{
    struct stack_entry* t = s -> top;
    if (t == NULL){
      return 0;
    }
    else{
      double r = (double)(t -> value);
      s -> size--;
      s -> top = t -> next;
      free(t);
      return r;
    }
  }
}

int push(struct stack* s, double e){
  struct stack_entry* helper = (struct stack_entry*)malloc(sizeof(struct stack_entry));
  if (helper == NULL || s == NULL){
    return -1;
  }
  struct stack_entry* new_e = (struct stack_entry*)malloc(sizeof(struct stack_entry));
  s -> size++;
  new_e -> value = e;
  new_e -> next = s -> top;
  s -> top = new_e;
  free(helper);
  return 0;
}
