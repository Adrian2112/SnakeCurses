#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include "linked_list.h"
 
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20
#define TICKRATE 300

#define SNAKE_INITIAL_LENGTH 3

typedef enum Direction { UP, DOWN, RIGHT, LEFT } Direction;

typedef struct Point {
  int x;
  int y;
} Point;

WINDOW *create_world();

List *create_snake(void);
void move_snake(WINDOW *window, List *snake, Direction direction);
Direction direction_for_key(int ch);

Point new_food_position(void);
 
int main(int argc, char *argv[]) {
    WINDOW *world;
    List *snake;
    Point food_point;
    Direction direction = RIGHT;

    srand(time(NULL));
 
    // ncurses initialization
    initscr();
    noecho();
    cbreak();
    timeout(TICKRATE);
    keypad(stdscr, TRUE);
    curs_set(0);
    
    refresh();
 
    //initialize world
    world = create_world();
    box(world, 0 , 0);

    wrefresh(world);

    // initialize snake
    snake = create_snake();

    food_point = new_food_position();
 
    int ch;
    while ((ch = getch()) != 'q')
    {
      move_snake(world, snake, direction);
      mvwaddch(world, food_point.y, food_point.x, 'O');
      wrefresh(world);
      if(ch != ERR) {
        direction = direction_for_key(ch);
      }
    }
 
    ll_free_list(snake);
    delwin(world);
 
    endwin();
 
    return 0;
 
}

WINDOW *create_world()
{
  int offsetX = (COLS - WORLD_WIDTH) / 2;
  int offsetY = (LINES - WORLD_HEIGHT) / 2;

  return newwin(WORLD_HEIGHT, WORLD_WIDTH, offsetY, offsetX);
}

List *create_snake(void){
   int i;
   List *snake = ll_create_list();

   for (i = 0; i < SNAKE_INITIAL_LENGTH; i++) {
     Point *snake_part = malloc(sizeof(Point));
     snake_part->x = i+1;
     snake_part->y = 1;

     ListNode *node = malloc(sizeof(ListNode));
     node->value = (void *)snake_part;
     ll_append_list_node(snake, node);
   }

   return snake;
}

void move_snake(WINDOW *win, List *snake, Direction direction)
{
  wclear(win);
  box(win, 0 , 0);

  ListNode *current_node = snake->head;
  ListNode *next_node = current_node->next;

  // each part copy the position of the next part except last one
  while(next_node != NULL)
  {
    Point *current_snake_part = (Point *)current_node->value;
    Point *next_snake_part = (Point *)next_node->value;

    current_snake_part->x = next_snake_part->x;
    current_snake_part->y = next_snake_part->y;
    mvwaddch(win, current_snake_part->y, current_snake_part->x, '#');

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
  mvwaddch(win, snake_tail_part->y, snake_tail_part->x, '#');

  wrefresh(win);
}

Direction direction_for_key(int ch)
{
  switch(ch) {
    case KEY_UP: 
    case 'k':
      return UP;
    case KEY_DOWN: case 'j':
      return DOWN;
    case KEY_RIGHT: case 'l':
      return RIGHT;
    default:
      return LEFT;
  }
}

Point new_food_position()
{
  Point food_position;
  food_position.x = (rand() % WORLD_WIDTH-1) + 1;
  food_position.y = (rand() % WORLD_HEIGHT-1) + 1;

  return food_position;
}
