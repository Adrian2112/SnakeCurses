#include <ncurses.h>
#include "defines.h"
#include "linked_list.h"

void appendSnakePartWithPoint(List *snake, Point *position);

List *snake_create(int size)
{
   int i;
   List *snake = ll_create_list();

   for (i = 0; i < size; i++) {
     Point *position = malloc(sizeof(Point));
     position->x = i+1;
     position->y = 1;

     appendSnakePartWithPoint(snake, position);
   }

   return snake;
}

void snake_move(List *snake, Direction direction)
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
}

void snake_add_part_to_tail(List *snake)
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

void appendSnakePartWithPoint(List *snake, Point *position)
{
     ListNode *node = malloc(sizeof(ListNode));
     node->value = (void *)position;
     ll_append_list_node(snake, node);
}
