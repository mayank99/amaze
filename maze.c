#include "maze.h"
#include <stdlib.h>
#include "queue.h"

void srandom(unsigned int);
long int random(void);

/* constructor for MAZE class */
MAZE *newMAZE(int rows, int columns) {
  MAZE *maze = malloc(sizeof(MAZE));
  maze->rows = rows;
  maze->columns = columns;
  maze->grid = malloc(sizeof(CELL *) * rows * columns);
  for (int i = 0; i < rows; i++) {
    maze->grid[i] = malloc(sizeof(CELL *) * columns);
    for (int j = 0; j < columns; j++) {
      maze->grid[i][j] = newCELL(i, j, -1);
    }
  }
  // maze->grid[0][0]->start = 1;
  maze->grid[rows - 1][columns - 1]->right = 0;
  return maze;
}

/* returns neighbor cell based on selection */
CELL *neighborCELL(MAZE *maze, CELL *cell, int select) {
  if (!cell) return 0;
  switch (select) {
    case 0:  // cell on top
      if (cell->row > 0) {
        return maze->grid[cell->row - 1][cell->column];
      }
      break;
    case 1:  // left
      if (cell->column > 0) {
        return maze->grid[cell->row][cell->column - 1];
      }
      break;
    case 2:  // right
      if (cell->column + 1 < maze->columns) {
        return maze->grid[cell->row][cell->column + 1];
      }
      break;
    case 3:  // bottom
      if (cell->row + 1 < maze->rows) {
        return maze->grid[cell->row + 1][cell->column];
      }
      break;
  }
  return 0;
}

/* returns a random unvisited neighbor */
CELL *neighborCELLrandom(MAZE *maze, CELL *cell) {
  // find unvisited neighbors (candidates)
  CELL *candidates[] = {0, 0, 0, 0};
  int number = 0;
  for (int i = 0, j = 0; i < 4; i++) {
    CELL *neighbor = neighborCELL(maze, cell, i);
    if (neighbor && !(neighbor->visited)) {
      candidates[j++] = neighbor;
      number++;
    }
  }

  // return random of those eligible candidates
  if (number > 0) {
    int index = random() % number;
    return candidates[index];
  }
  return 0;
}

// Remove the wall between the current location and a randomly-chosen, unvisited neighbor. Then
// traverse further from the chosen neighbor (and so on) until you find no unvisited neighbors. At
// this point, go back to the previous spot and try again (and so on).
void buildMAZEinternal(MAZE *maze, CELL *cell) {
  CELL *neighbor = 0;
  do {
    neighbor = neighborCELLrandom(maze, cell);
    if (neighbor) {
      neighbor->visited = 1;
      removeCELLwall(cell, neighbor);
      buildMAZEinternal(maze, neighbor);
    }
  } while (neighbor);
}

/* builds a maze using depth-first traversal */
void buildMAZE(MAZE *maze, int seed) {
  srandom(seed);
  CELL *start = maze->grid[0][0];  // Start recursing at 0
  start->visited = 1;
  buildMAZEinternal(maze, start);
}

// Continue searching until the lower right corner is reached. Mark the squares searched with step
// number (mod 10). The upper left corner is always marked with a zero. The solving process stops
// when the lower right-hand corner is reached.
void solveMAZEinternal(MAZE *maze, CELL *start) {
  QUEUE *queue = newQUEUE();
  enqueue(queue, start);
  start->visited = 1;

  while (sizeQUEUE(queue) > 0) {
    CELL *cell = dequeue(queue);
    if (cell->row == maze->rows - 1 && cell->column == maze->columns - 1) break;

    // enqueue unvisited neighbors
    for (int i = 0; i < 4; i++) {
      CELL *neighbor = neighborCELL(maze, cell, i);
      if (neighbor && !(neighbor->visited) && reachableCELL(cell, neighbor)) {
        neighbor->visited = 1;
        neighbor->value = (cell->value + 1) % 10;
        enqueue(queue, neighbor);
      }
    }
  }

  if (queue) freeQUEUE(queue);
}

/* solves a maze using breadth-first traversal */
void solveMAZE(MAZE *maze) {
  CELL *start = maze->grid[0][0];  // Start recursing at 0
  start->value = 0;
  solveMAZEinternal(maze, start);
}

/* saves the current state of the maze to file */
void saveMAZE(MAZE *maze, FILE *file) {
  if (file != 0) {
    fprintf(file, "%d %d\n", maze->rows, maze->columns);
    for (int i = 0; i < maze->rows; i++) {
      for (int j = 0; j < maze->columns; j++) {
        CELL *cell = maze->grid[i][j];
        writeCELL(cell, file);
      }
    }
    fclose(file);
  }
}

/* reads a maze from a file and returns it */
MAZE *readMAZE(FILE *file) {
  if (file != 0) {
    MAZE *maze = malloc(sizeof(MAZE));
    fscanf(file, "%d %d\n", &maze->rows, &maze->columns);
    maze->grid = malloc(sizeof(CELL *) * maze->rows * maze->columns);
    for (int i = 0; i < maze->rows; i++) {
      maze->grid[i] = malloc(sizeof(CELL *) * maze->columns);
      for (int j = 0; j < maze->columns; j++) {
        CELL *cell = newCELL(i, j, -1);
        readCELL(cell, file);
        maze->grid[i][j] = cell;
      }
    }
    fclose(file);
    return maze;
  }
  return 0;
}

/* draws the maze to stdout */
void drawMAZE(MAZE *maze) {
  printf("-");
  for (int i = 0; i < maze->columns; i++) {
    printf("----");
  }
  printf("\n");

  for (int i = 0; i < maze->rows; i++) {
    if (i == 0)
      printf(" ");
    else
      printf("|");
    for (int j = 0; j < maze->columns; j++) {
      CELL *cell = maze->grid[i][j];
      if (cell->value == -1)
        printf("   ");
      else
        printf(" %d ", cell->value);
      if (cell->right)
        printf("|");
      else
        printf(" ");
    }

    printf("\n-");
    for (int j = 0; j < maze->columns; j++) {
      if (maze->grid[i][j]->bottom)
        printf("---");
      else
        printf("   ");
      printf("-");
    }
    printf("\n");
  }
}

/* destructor for MAZE class */
void freeMAZE(MAZE *maze) {
  for (int i = 0; i < maze->rows; i++) {
      for (int j = 0; j < maze->columns; j++) {
        free(maze->grid[i][j]);
      }
      free(maze->grid[i]);
  }
  free(maze->grid);
  free(maze);
}
