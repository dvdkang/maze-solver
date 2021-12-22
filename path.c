/***********************************************************************
 * Homework 5: Maze Solving (path.c)
 ***********************************************************************/

#include "path.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

list_t *
list_add (position_t position, list_t* current) {
  list_t * added = malloc(sizeof(list_t));
  if (added == NULL) {
    perror("Memory allocation failure for added");
  } // if
  added->next = current; // adds new position to the head of the list
  added->position = position; 
  return added;
} // list_add

position_t
list_front (list_t* current) {
  assert(current != NULL);
  return current->position;
} // list_front

void
list_print_reverse (list_t* list) {
  list_t * next = NULL;
  list_t * current = list;
  list_t * temp = NULL;
  // swapping out the entire list to be reversed 
  while (current != NULL) {
    next = current->next;
    current->next = temp;
    temp = current;
    current = next;
  } // while
  list_t * reverse = temp;
  // prints out all the positions of the reversed list
  while (reverse != NULL) {
    printf("%d,%d\n", (reverse->position).row, (reverse->position).col);
    reverse = reverse->next;
  } // while

  free(current);
  free(temp);
  free(reverse);
} // list_print_reverse

void
list_free (list_t * list) {
  list_t * next; 
  for (list_t ** current = &list; *current != NULL; *current = next) {
    next = (*current)->next;
    free(&((*current)->position));
    *current = NULL;
  } // for
} // list_free
