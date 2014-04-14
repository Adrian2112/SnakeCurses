#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include "linked_list.h"
#include "defines.h"
#include "snake.h"
 
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20
#define TICKRATE 300

#define SNAKE_INITIAL_LENGTH 3

WINDOW *create_world();

Direction direction_for_key(int ch);
int are_points_equal(Point a, Point b);
void draw_snake(WINDOW *, List *snake);

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
    snake = snake_create(SNAKE_INITIAL_LENGTH);

    food_point = new_food_position();
 
    int ch;
    while ((ch = getch()) != 'q')
    {
      wclear(world);
      box(world, 0 , 0);

      snake_move(snake, direction);

      Point *snake_head = (Point *)snake->tail->value;
      if (are_points_equal(food_point, *snake_head)) {
        food_point = new_food_position();
        snake_add_part_to_tail(snake);
      }

      // draw elements
      mvwaddch(world, food_point.y, food_point.x, 'O');
      draw_snake(world, snake);

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

int are_points_equal(Point a, Point b)
{
  if (a.x == b.x && a.y == b.y) {
    return 1;
  }

  return 0;
}

void draw_snake(WINDOW *win, List *snake)
{
  ListNode *snake_part = snake->head;

  while(snake_part != NULL)
  {
    Point *snake_part_position = (Point *)snake_part->value;
    mvwaddch(win, snake_part_position->y, snake_part_position->x, '#');

    snake_part = snake_part->next;
  }
}
