/**
 * Created by Mayank Agarwal
 */
#include "cell.h"
#include <stdlib.h>

CELL *newCELLinternal(int row, int column, int value, int right, int bottom) {
  CELL *cell = malloc(sizeof(CELL));
  cell->row = row;
  cell->column = column;
  cell->value = value;
  cell->right = right;
  cell->bottom = bottom;
  // cell->start = 0;
  // cell->end = 0;
  cell->visited = 0;
  return cell;
}

/* constructor for CELL class */
CELL *newCELL(int row, int column, int value) {
  return newCELLinternal(row, column, value, 1, 1);
}

/* writes contents of the cell into a file */
void writeCELL(CELL *cell, FILE *file) {
  fprintf(file, "%d %d %d %d %d %d\n", cell->value, cell->row, cell->column, 0, cell->right, cell->bottom);
}

/* reads contents of a cell from a file */
void readCELL(CELL *cell, FILE *file) {
  fscanf(file, "%d %d %d %d %d %d\n", &cell->value, &cell->row, &cell->column, &cell->visited, &cell->right, &cell->bottom);
}

/* removes the wall between two cells */
void removeCELLwall(CELL *a, CELL *b) {
  if (a->row == b->row) {
    if (a->column == b->column - 1)
      a->right = 0;
    else
      b->right = 0;
  } else {
    if (a->row == b->row - 1)
      a->bottom = 0;
    else
      b->bottom = 0;
  }
}

/* returns 1 if cells are connected (with an open wall) */
int reachableCELL(CELL *a, CELL *b) {
  if (a->row == b->row) {
    if (a->column == b->column - 1 && a->right == 0) return 1;
    if (a->column == b->column + 1 && b->right == 0) return 1;
  } else if (a->column == b->column) {
    if (a->row == b->row - 1 && a->bottom == 0) return 1;
    if (a->row == b->row + 1 && b->bottom == 0) return 1;
  } else {
    return 0;
  }
  return 0;
}