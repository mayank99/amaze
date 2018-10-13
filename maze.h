#ifndef __MAZE_INCLUDED__
#define __MAZE_INCLUDED__

#include <stdio.h>
#include "cell.h"

typedef struct maze MAZE;

struct maze {
  int rows;
  int columns;
  CELL ***grid;
};

extern MAZE *newMAZE(int rows, int columns);
extern void buildMAZE(MAZE *maze, int seed);
extern void solveMAZE(MAZE *maze);
extern void saveMAZE(MAZE *maze, FILE *file);
extern MAZE *readMAZE(FILE *file);
extern void drawMAZE(MAZE *maze);
extern void freeMAZE(MAZE *maze);

#endif