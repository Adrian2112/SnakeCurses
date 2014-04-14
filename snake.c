#include <ncurses.h>
#include "defines.h"
#include "linked_list.h"
#include "snake.h"

void appendSnakePartWithPoint(Snake *snake, Point *position);
int getPositionInBound(int n, int max_bound);

Snake *snake_create(int size)
{
   int i;
   Snake *snake = ll_create_list();

   for (i = 0; i < size; i++) {
     Point *position = malloc(sizeof(Point));
     position->x = i+1;
     position->y = 1;

     appendSnakePartWithPoint(snake, position);
   }

   return snake;
}

void snake_move(Snake *snake, Direction direction, int max_width, int max_height)
{
  ListNode *current_node = snake->head;
  ListNode *next_node = current_node->next;

  // each part copy the position of the next part except last one
  while(next_node != NULL)
  {
    Point *current_snake_part = (Point *)current_node->value;
    Point *next_snake_part = (Point *)next_node->value;

    current_snake_part->x = next_snake_part->x;
    current_snake_part->y = next_snake_part->y;

    current_node = current_node->next;
    next_node = current_node->next;
  }

  int moveX = 0;
  int moveY = 0;

  switch (direction) {
    case RIGHT:
      moveX = 1;
      break;
    case LEFT:
      moveX = -1;
      break;
    case UP:
      moveY = -1;
      break;
    case DOWN:
      moveY = 1;
      break;
  }

  ListNode *snake_tail_node = snake->tail;
  Point *snake_tail_part = (Point *)snake_tail_node->value;

  snake_tail_part->x += moveX;
  snake_tail_part->y += moveY;


  snake_tail_part->x = getPositionInBound(snake_tail_part->x, max_width);
  snake_tail_part->y = getPositionInBound(snake_tail_part->y, max_height);

}

void snake_add_part_to_tail(Snake *snake)
{
  ListNode *snake_tail = snake->head;
  ListNode *pre_tail = snake_tail->next;

  Point *tail_position = (Point *)snake_tail->value;
  Point *pre_tail_position = (Point *)pre_tail->value;

  int x_change = tail_position->x - pre_tail_position->x;
  int y_change = tail_position->y - pre_tail_position->y;

  Point *new_part_position = malloc(sizeof(Point));
  new_part_position->x = tail_position->x;
  new_part_position->y = tail_position->y;

  // moving downwards or upwards
  if (x_change == 0) {
    new_part_position->y += y_change > 0 ? 1 : -1;
  } 
  // moving sidewise
  else 
  {
    new_part_position->x += x_change > 0 ? 1 : -1;
  }

  ListNode *new_part_node = malloc(sizeof(ListNode));
  new_part_node->value = (void *)new_part_position;

  ll_prepend_list_node(snake, new_part_node);
}

/*  private  */

void appendSnakePartWithPoint(Snake *snake, Point *position)
{
     ListNode *node = malloc(sizeof(ListNode));
     node->value = (void *)position;
     ll_append_list_node(snake, node);
}

int getPositionInBound(int n, int max_bound)
{
  // if move beyond min bound move to the max bound
  if (n < 0) {
    n = max_bound;
  }
  // check that dont go over max bound
  else
  {
    n = n % max_bound;
  }

  return n;
}
