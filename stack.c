#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "da.h"

struct stack {
  DA *array;
  int debug;
  void (*display)(void *, FILE *);
};

STACK *newSTACK(void) {
  STACK *items = malloc(sizeof(STACK));
  assert(items != 0);
  items->array = newDA();
  items->debug = 0;
  return items;
}

void setSTACKdisplay(STACK *items, void (*d)(void *, FILE *)) {
  items->display = d;
  setDAdisplay(items->array, d);
}

void setSTACKfree(STACK *items, void (*f)(void *)) {
  setDAfree(items->array, f);
}

void push(STACK *items, void *value) {
  insertDA(items->array, sizeDA(items->array), value);
}

void *pop(STACK *items) {
  assert(sizeDA(items->array) > 0);
  return removeDA(items->array, sizeDA(items->array) - 1);
}

void *peekSTACK(STACK *items) {
  assert(sizeDA(items->array) > 0);
  return getDA(items->array, sizeDA(items->array) - 1);
}

void displaySTACK(STACK *items, FILE *fp) {
  if (items->debug == 0) {
    fprintf(fp, "|");
    for (int i = sizeDA(items->array) - 1; i >= 0; i--) {
      items->display(getDA(items->array, i), fp);
      if (i != 0) fprintf(fp, ",");
    }
    fprintf(fp, "|");
  } else {
    debugDA(items->array, items->debug - 1);
    displayDA(items->array, fp);
  }
}

int debugSTACK(STACK *items, int level) {
  int temp = items->debug;
  items->debug = level;
  return temp;
}

void freeSTACK(STACK *items) {
  freeDA(items->array);
  free(items);
}

int sizeSTACK(STACK *items) { return sizeDA(items->array); }