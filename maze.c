#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "maze.h"
#include "position.h"

/* (INTERNAL FUNCTION) Verify the maze parameters have been read correctly and
   are valid (positive) 
   Pre-conditions: None.
   Post-conditions: 
     - Returns 1 when numTokens==2 && height>0 && width>0.
     - Returns 0 and prints an informative message to stderr otherwise.
*/
int
isValidMazeHeader(int numTokens, int height, int width)
{
  if (numTokens != 2)
  {
    fprintf(stderr,"Unable to read height and width from first line");
    return 0;
  }
  
  if (height<=0)
  {
    fprintf(stderr,"height must be positive, received %d\n", height);
    return 0;
  }

  if (width<=0)
  {
    fprintf(stderr,"width must be positive, received %d\n", width);
    return 0;
  }

  return 1;
  
} // isValidMazeHeader



/* Read a maze from the given file stream pointer.
   Produces: maze, pointer to a dynamically allocated maze_t 
   Pre-conditions:
     - stream != NULL
     - stream is open for reading and positioned at the beginning of a properly-
       formatted maze (see accompanying documentation).
   Post-conditions: 
     - maze refers to a maze with the configuration given by stream
     - No cell in maze->cells is marked VISITED.
     - maze == NULL when maze data in stream is improperly formatted
     - Prints an informative error to stderr and aborts the program when memory
       cannot be allocated for the maze and its cells.
   Practica
     - To reclaim the dynamically allocated memory, call freeMaze(maze)
*/
maze_t*
readMaze(FILE* stream)
{
  assert( stream!= NULL );

  int height, width; /* Maze dimensions */
  position_t start = {-1, -1};
  position_t end = {-1, -1};
  
  /* Read and verify header information */
  int numTokens = fscanf(stream, "%d %d ",&height,&width);

  if (!isValidMazeHeader(numTokens,height,width))
    return NULL;
    
  /* Create cell array of the appropriate size */
  cell_t *p_cells = malloc(height*width*sizeof(cell_t));

  if (p_cells==NULL)
  {
    perror("Unable to allocate cell array");
    exit(EXIT_FAILURE);
  }

  /* Create the complete maze structure */
  maze_t* maze = malloc(sizeof(maze_t));

  if (maze==NULL)
  {
    perror("Unable to allocate maze structure");
    free(p_cells); /* Clean up before exit */
    exit(EXIT_FAILURE);
  }

  /* Populate maze structure */
  maze->height = height;
  maze->width = width;
  maze->cells = p_cells;

  /* Loop over all cells, reading and storing data */
  int row, col;
  cell_t* p_cell = p_cells;
  char cellChar;
  for (row=0 ; row<height; row++)
  {
    for (col=0 ; col<width ; col++, p_cell++)
    {
      /* Read next character */
      if ( fscanf(stream,"%c",&cellChar) != 1)
      { /* Verify input read acceptably */
        if (feof(stream))
          fprintf(stderr,"Premature end of input while reading maze");
        else if (ferror(stream))
          perror("Error reading maze");
        freeMaze(maze); /* Clean up before aborting */
        return NULL;
      }
      else
        switch(cellChar)
        {
        case 's': case 'S':
          *p_cell = START;
          start.row = row;
          start.col = col;
          maze->start = start;
          break;
        case 'e': case 'E':
          *p_cell = END;
          end.row = row;
          end.col = col;
          maze->end = end;
          break;
        case ' ':
          *p_cell = OPEN;
          break;
        default:
          *p_cell = BLOCKED;
          break;
        } // switch
    } // for col
    /* Read newline */
    int lineEnd = fgetc(stream);

    if (lineEnd != '\n' && row!=height-1) /* Newline not required in last row */
    {
      if (feof(stream))
        fprintf(stderr,"Premature end of input while reading maze");
      else if (ferror(stream))
        perror("Error reading maze");
      freeMaze(maze); /* Clean up before aborting */
      return NULL;
    }
  } // for row

  if (start.row == -1)
  {
    fprintf(stderr, "Error in maze input: No start position denoted");
    freeMaze(maze);
    return NULL;
  }

  if (end.row == -1)
  {
    fprintf(stderr, "Error in maze input: No end position denoted");
    freeMaze(maze);
    return NULL;
  }
    
  return maze;
} // readMaze


/* Free the dynamically allocated memory associated with a maze_t pointer.
   Pre-conditions: maze is a non-NULL value returned from readMaze.
   Post-conditions: All dynamically allocated memory used by maze is freed
*/
void freeMaze(maze_t * maze)
{
  assert(maze != NULL);

  free(maze->cells);
  free(maze);
}


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
printMaze(const maze_t* maze)
{
  assert(maze != NULL);
  
  int height = maze->height;
  int width = maze->width;
  cell_t * p_cell = maze->cells;
  char ch;
  
  for(int row=0 ; row<height ; row++)
  {
    for (int col=0 ; col<width ; col++, p_cell++)
    {
      switch (*p_cell)
      {
      case OPEN:    ch=' '; break;
      case BLOCKED: ch='X'; break;
      case VISITED: ch='.'; break;
      case START:   ch='@'; break;
      case END:     ch='$'; break;
      default:      ch='?'; break; /* Included in case someone changes cell_t */
      }
      printf("%c",ch);
    }
    printf("\n");
  }
}
      
/* Get the offset for a position in the given maze
 *
 * Preconditions:
 *   maze points to a valid maze_t struct
 *   0 <= position.row < maze->height
 *   0 <= position.col < maze->width
 * Postconditions:
 *   Returns width*row + col
 * Practica:
 *   Assumes positions represent a height*width contiguous block of memory in
 *   row-major order
 */
int
offset(const maze_t* maze, position_t position)
{
  assert( position.row >= 0);
  assert( position.col >= 0);
  assert( position.row < maze->height);
  assert( position.col < maze->width);

  return maze->width * position.row  +  position.col;
}
