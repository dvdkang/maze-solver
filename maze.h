/* Set of functions to read and print a maze data structure */

#ifndef __MAZE_H__
#define __MAZE_H__

#include "position.h"
#include <stdio.h>

typedef /* Various states a maze cell may be in */
enum cell { OPEN, BLOCKED, VISITED, START, END }
  cell_t;

/* Maze structure with dimensions height x width. Maze cells are a height*width
   contiguous block of memory in row-major order (offset = width*row + col). */
typedef struct maze {
  int height;
  int width;
  position_t start;
  position_t end;
  cell_t* cells;
} maze_t;


/* Read a maze from the given file stream pointer.
   Produces: p_maze, pointer to a dynamically allocated maze_t 
   Pre-conditions:
     - stream != NULL
     - stream is open for reading and positioned at the beginning of a properly-
       formatted maze (see accompanying documentation).
   Post-conditions: 
     - p_maze refers to a maze with the configuration given by stream
     - No cell in p_maze->cells is marked VISITED.
     - p_maze == NULL when maze data in stream is improperly formatted
     - Prints an informative error to stderr and aborts the program when memory
       cannot be allocated for the maze and its cells.
   Practica
     - To reclaim the dynamically allocated memory, call freeMaze(p_maze)
*/
maze_t*
readMaze(FILE* stream);

/* Print a maze visualization to standard output
   Pre-condition: maze points to a valid maze_t structure
   Post-condition: 
     A maze->height x maze->width representation of the maze is printed to
     stdout, with the following cell->char mappings:
       open   ' '
       blocked X
       visited .
       start   @
       end     $
*/
void
printMaze(const maze_t* maze);

/* Free the dynamically allocated memory associated with a maze_t pointer.
   Pre-conditions: maze is a non-NULL value returned from readMaze.
   Post-conditions: All dynamically allocated memory used by maze is freed
*/
void
freeMaze(maze_t* maze);

/* Get the offset for a position in the given maze
 *
 * Preconditions:
 *   maze points to a valid maze_t struct
 *   0 <= position.row < maze->height [verified]
 *   0 <= position.col < maze->width [verified]
 * Postconditions:
 *   Returns width*row + col
 * Practica:
 *   Assumes positions represent a height*width contiguous block of memory in
 *   row-major order
 */
int
offset(const maze_t* maze, position_t position);

#endif
