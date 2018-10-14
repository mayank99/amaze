/**
 * Created by Mayank Agarwal
 */
#ifndef __CELL_INCLUDED__
#define __CELL_INCLUDED__

#include <stdio.h>

struct cell {
  int value;

  // position in maze
  int row;
  int column;

  // special flags
  int visited;

  // wall info
  int right;
  int bottom;
};

typedef struct cell CELL;

extern CELL *newCELL(int rows, int columns, int value);
extern void readCELL(CELL *cell, FILE *file);
extern void writeCELL(CELL *cell, FILE *file);
extern int reachableCELL(CELL *a, CELL *b);
extern void removeCELLwall(CELL *a, CELL *b);
// extern void freeCELL(CELL *);
// extern CELL *newCELLinternal(int x, int y, int value, int right, int bottom);

#endif