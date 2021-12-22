/***********************************************************************
 * Homework 5: Maze Solving (queue.c)
 ***********************************************************************/

#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void
queue_initialize (queue_t * queue) {
  queue->front = NULL;
  queue->rear = NULL;
} // queue_initialize

bool
queue_empty (const queue_t * queue) {
  if (queue->front == NULL)
    return true;
  else
    return false;
} // queue_empty

bool
enqueue (queue_t * queue, list_t* path) {
  node_t * new = malloc(sizeof(node_t));
  new->solution = path;
  new->next = NULL;

  if (queue_empty(queue)) { // if queue is empty new is both the head and tail
    queue->front = new;
    queue->rear = new;
    return true;
  } // if
  else { // sets the new node to the rear of the queue
    queue->rear->next = new;
    queue->rear = new;
    return true;
  } // else
  return false;
} // enqueue

list_t*
dequeue (queue_t * queue) {
  assert (!queue_empty(queue));

  node_t * temp = queue->front; // saving the front of the queue to free later
  list_t * save = queue->front->solution;

  queue->front = queue->front->next;

  if (queue->front == NULL)
    queue->rear = NULL;
  
  free(temp);

  return save;
} // dequeue

list_t*
queue_front (const queue_t * queue) {
  assert (!queue_empty(queue));

  return queue->front->solution;
} // queue_front
