/* Queue data structure for storing partial solutions to the maze problem */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

#include "path.h"

/* List-backed Queue consists of nodes, each of which has a reference to a
 * solution (path), as well as the next node inthe queue.
 */
typedef struct node {
  list_t * solution;
  struct node * next;
} node_t;

/* Queue structure contains references to the front and rear nodes for easy
 * insertion at the end and deletion from the front */
typedef struct queue {
  node_t * front;
  node_t * rear;
} queue_t;

/* Initialize a queue data structure
 * 
 * Preconditions:
 *   queue != NULL
 *   queue points to a valid queue structure
 * Postconditions:
 *   queue_empty(queue) == true
 */
void
queue_initialize (queue_t * queue);

/* Determine whether a queue is empty
 * 
 * Preconditions:
 *   queue != NULL
 *   queue points to a valid queue structure
 *   queue_initialize(queue) has been called at some point
 * Postconditions:
 *   Returns true when queue_initialize has been called on the given queue and
 *   both enqueue and dequeue have been called the same number of times
 */
bool
queue_empty (const queue_t * queue);

/* Insert a solution at the rear of a queue
 * 
 * Preconditions:
 *   queue != NULL
 *   queue points to a valid queue structure
 *   initialize(queue) has been called at some point
 * Postconditions:
 *   Returns whether the item was successfully inserted. 
 *   When true, queue_empty(queue)==false and path appears at the end of
 *     the queue
 *   Only the reference path is stored; no deep copy is made and the queue is not 
 *     responsible for managing any memory associated with path
 */
bool
enqueue (queue_t * queue, list_t* path);

/* Remove and return the item at the front of the queue
 *
 * Preconditions:
 *   queue != NULL
 *   queue points to a valid queue structure
 *   queue_initialize(queue) has been called at some point
 *   queue_empty(queue) is false [verified]
 * Postconditions:
 *   Returns the item at the front of the queue (i.e., the remaining item least
 *     recently enqueued)
 *   The item has been removed from the queue
 */
list_t*
dequeue (queue_t * queue);

/* Return the solution at the front of the queue
 *
 * Preconditions:
 *   queue != NULL
 *   queue points to a valid queue structure
 *   queue_initialize(queue) has been called at some point
 *   queue_empty(queue) is false [verified]
 * Postconditions:
 *   Returns the item at the front of the queue (i.e., the remaining item least
 *     recently enqueued)
 *   queue is unaltered
 */
list_t*
queue_front (const queue_t * queue);

#endif
