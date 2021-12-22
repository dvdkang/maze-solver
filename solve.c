/***********************************************************************
 * Homework 5: Maze Solving
 ***********************************************************************/

#include "path.h"
#include "maze.h"
#include "queue.h"
#include <stdlib.h>

/* 
   Purpose: Checks whether the given position is the end of the maze or not
   Parameters: position_t endposition, maze_t * maze
   Preconditions: maze is a valid maze
                  position is a valid structure of position
   Postconditions: returns true if the given position has the same values as 
                   the end position, if not return false. 
*/
bool
endchecker (position_t endposition, maze_t * maze) {
  // condition to check the row and col of the position to the row and col
  // of the maze end position. 
  if ((endposition.row == (maze->end).row) &&
      (endposition.col == (maze->end).col))
    return true;
  else
    return false; 
} // endchecker

/* 
   Purpose: Goes through the neighboring positions and if the given position 
            is open or the end, add it to the list and enqueue it, otherwise
            don't do anything to it. 
   Parameters: position_t direction, list_t * check, queue_t * solutions, 
               maze_t * maze
   Preconditions: maze is a valid maze
                  position is a valid structure of position
                  check points to a valid list
                  solutions points to a valid queue structure
   Postconditions: if conditions are matched, new path is added onto the list
                   and is enqueued into the queue. If not then nothing happens. 
*/
void
neighbordetermine (position_t direction, list_t * check,
                   queue_t * solutions, maze_t * maze) {
  // makes sure that the neighboring positions are within the maze
  if (direction.row >= 0 && direction.col >= 0) {
    // condition checks if the cell is open or end so that it would be added
    // as an augmented path
    if (maze->cells[offset(maze, direction)] == OPEN ||
        maze->cells[offset(maze, direction)] == END) {
      check = list_add(direction, check);
      enqueue(solutions, check);
    } // if
  } // if
} // neighbordetermine

/* 
   Purpose: Creates the neighboring positions and lets it run through the 
            neighbordetermine function. 
   Parameters: list_t * check, list_t * path, queue_t * solutions, 
               maze_t * maze
   Preconditions: maze is a valid maze
                  check points to a valid list
                  path points to a valid list
                  solutions points to a valid queue structure
   Postconditions: gives the correct neighboring positions of the path and 
                   runs through the neighbordetermine function. 
*/
void
pathdetermine (list_t * check, list_t * path,
               queue_t * solutions, maze_t * maze) {

  // initializes values for the neighboring positions
  position_t north = {list_front(check).row, list_front(check).col + 1};
  position_t south = {list_front(check).row, list_front(check).col - 1};
  position_t west = {list_front(check).row - 1, list_front(check).col};
  position_t east = {list_front(check).row + 1, list_front(check).col};

  // runs through neighbordetermine to check whether they are valid paths
  neighbordetermine(north, check, solutions, maze);
  neighbordetermine(south, check, solutions, maze);
  neighbordetermine(west, check, solutions, maze);
  neighbordetermine(east, check, solutions, maze);
} // pathdetermine

int
main (void) {
  maze_t * maze = readMaze(stdin);
  // makes sure that if the maze is null then no need to run this program
  if (maze == NULL)
    return 0;
  
  queue_t solutions;
  queue_initialize(&solutions);
  list_t* path = NULL;
  
  path = list_add(maze->start, path); // adding the starting position to list
  
  enqueue(&solutions, path);

  while(!queue_empty(&solutions)) {
    list_t * check = dequeue(&solutions);
    // checks if the given path leads to the end of the maze
    if (endchecker(list_front(check), maze)) {
      list_print_reverse(check);
      return 0;
    } // if
    else {
      // if not equal to the end then check the cell to be visited
      maze->cells[offset(maze, list_front(check))] = VISITED;
      // checking neighboring paths because no end was found yet
      pathdetermine(check, path, &solutions, maze);
    } // else
  } // while

  queue_initialize(&solutions);
  free(maze);
  return 0;
}  // main
