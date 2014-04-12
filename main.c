#include <ncurses.h>
#include <stdio.h>
 
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20
#define TICKRATE 300

#define SNAKE_INITIAL_LENGTH 3

typedef enum Direction { UP, DOWN, RIGHT, LEFT } Direction;

typedef struct SnakePart {
  int x;
  int y;
} SnakePart;

WINDOW *create_world();
void initialize_snake(SnakePart *snake, int snake_size);
void move_snake(WINDOW *window, SnakePart *snake, int snake_size, Direction direction);
 
int main(int argc, char *argv[]) {
 
    WINDOW *world;
    SnakePart snake[SNAKE_INITIAL_LENGTH];
    Direction direction = RIGHT;
 
    // ncurses initialization
    initscr();
    noecho();
    cbreak();
    timeout(TICKRATE);
    keypad(stdscr, TRUE);
    
    refresh();
 
    //initialize world
    world = create_world();
    box(world, 0 , 0);

    wrefresh(world);

    // initialize snake
    int snake_size = sizeof(snake)/sizeof(SnakePart);
    initialize_snake(snake, snake_size);
 
    int ch;
    while ((ch = getch()) != 'q')
    {
      move_snake(world, snake, snake_size, direction);
      if(ch != ERR) {
        switch(ch) {
          case KEY_UP:
            direction = UP;
            break;
          case KEY_DOWN:
            direction = DOWN;
            break;
          case KEY_RIGHT:
            direction = RIGHT;
            break;
          case KEY_LEFT:
            direction = LEFT;
            break;
          default:
            break;
        }
      }
    }
 
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

void initialize_snake(SnakePart *snake, int snake_size){
   int i;
   for (i = 0; i < snake_size; i++) {
     snake[i].x = i+1;
     snake[i].y = 1;
   }
}

void move_snake(WINDOW *win, SnakePart *snake, int snake_size, Direction direction)
{
  wclear(win);
  box(win, 0 , 0);

  int i;
  // each part copy the position of the next part except last one
  for (i = 0; i < snake_size - 1; i++) {
    snake[i].x = snake[i+1].x;
    snake[i].y = snake[i+1].y;
    mvwaddch(win, snake[i].y, snake[i].x, '#');
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

  int last_part_index = snake_size - 1;
  snake[last_part_index].x += moveX;
  snake[last_part_index].y += moveY;
  mvwaddch(win, snake[last_part_index].y, snake[last_part_index].x, '#');

  wrefresh(win);
}
