#include "amaze.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

static const char OPTIONS[] = {'v', 'r', 'c', 's', 'd'};

int args[5] = {0};
char *infile, *outfile, *mazefile, *drawfile;
int seed = 0, rows = 0, columns = 0;

int option(char);
void processOptions(int, char**);

int main(int argc, char** argv) {
  processOptions(argc, argv);

  // VERSBOSE (author details)
  if (args[option('v')]) {
    printf("Written by Mayank Agarwal\n");
    return 0;
  }

  // SEED RANDOM GENERATOR
  if (!args[option('r')]) seed = 1;

  // MAZE CREATION
  if (args[option('c')]) {
    MAZE* maze = newMAZE(rows, columns);
    buildMAZE(maze, seed);
    FILE* file = fopen(mazefile, "wb");
    saveMAZE(maze, file);
    freeMAZE(maze);
  }

  // SOLVING THE MAZE
  if (args[option('s')]) {
    FILE* file1 = fopen(infile, "rb");
    MAZE *maze = readMAZE(file1);
    solveMAZE(maze);
    FILE* file2 = fopen(outfile, "wb");
    saveMAZE(maze, file2);
    freeMAZE(maze);
  }

  // OUTPUT
  if (args[option('d')]) {
    FILE* file = fopen(drawfile, "rb");
    MAZE *maze = readMAZE(file);
    drawMAZE(maze);
    freeMAZE(maze);
  }
}

/** CODE FOR HANDLING OPTIONS */

int option(char option) {
  for (int i = 0; i < 5; i++) {
    if (OPTIONS[i] == option) return i;
  }
  return -1;
}

void processOptions(int argc, char** argv) {
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-') {
      args[option(argv[i][1])] = 1;
      switch (argv[i][1]) {
        case 'r':
          seed = atoi(argv[i + 1]);
          break;
        case 'd':
          drawfile = argv[i + 1];
          break;
        case 's':
          infile = argv[i + 1];
          outfile = argv[i + 2];
          break;
        case 'c':
          rows = atoi(argv[i + 1]);
          columns = atoi(argv[i + 2]);
          mazefile = argv[i + 3];
      }
    }
  }
}