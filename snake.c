#include <ncurses.h>
#include "defines.h"
#include "linked_list.h"

List *snake_create(int size)
{
   int i;
   List *snake = ll_create_list();

   for (i = 0; i < size; i++) {
     Point *snake_part = malloc(sizeof(Point));
     snake_part->x = i+1;
     snake_part->y = 1;

     ListNode *node = malloc(sizeof(ListNode));
     node->value = (void *)snake_part;
     ll_append_list_node(snake, node);
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
