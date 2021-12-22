/* Routines for a linked list describing a solution to the maze (in reverse
   order). Items in the list are integers representing the position within the
   maze. */

#ifndef __PATH_H__
#define __PATH_H__

#include "position.h"

typedef struct list {
  position_t position;
  struct list * next;
} list_t;


/* Add the given position to the front of a list
 *
 * Produces:
 *   added
 * Preconditions:
 *   current is NULL or points to a valid list_t
 * Postconditions:
 *   added is a newly allocated list_t with
 *     added->next = current
 *     added->position = position 
 *   or added is NULL if memory allocation fails
 */
list_t * 
list_add ( position_t position, list_t* current);


/* Get the front of the list (the most recently added item)
 * 
 * Preconditions:
 *   current points to a valid list
 *   current != NULL [verified]
 * Postconditions:
 *   Returns the position in the node at the front of the list
 */
position_t
list_front (list_t* current);


/* Prints the given list in reverse order, with each position in "row,col" form
 * followed by a newline. The last position printed also includes a newline.
 * 
 * Pattern (example):
 *   0,14
 *   1,14
 *   1,13
 *   (etc)
 */
void
list_print_reverse ( list_t* list);

/* Releases all the memory associated with the list.
 *
 * Preconditions:
 *   [No additional.]
 * Preferences:
 *   The list is singly connected (that is, there are no other references to 
 *     the nodes in this list
 * Postconditions:
 *   Every node in the list is freed
 */
void
list_free ( list_t* list);

#endif

