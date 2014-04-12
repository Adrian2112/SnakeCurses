#include <ncurses.h>
#include <stdio.h>
 
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20
#define TICKRATE 100

#define SNAKE_INITIAL_LENGTH 3

typedef struct SnakePart {
  int x;
  int y;
} SnakePart;

WINDOW *create_world();
void initialize_snake(SnakePart *snake, int snake_size);
void move_snake(WINDOW *window, SnakePart *snake, int snake_size);
 
int main(int argc, char *argv[]) {
 
    WINDOW *world;
    SnakePart snake[SNAKE_INITIAL_LENGTH];
 
    initscr();
    noecho();
    cbreak();
    timeout(TICKRATE);
    keypad(stdscr, TRUE);
    
    refresh();
 
    world = create_world();
    int snake_size = sizeof(snake)/sizeof(SnakePart);
    initialize_snake(snake, snake_size);
 
    box(world, 0 , 0);
 
    move_snake(world, snake, snake_size);

    wrefresh(world);
 
    int ch;
    while ((ch = getch()) != 'q')
    {
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

void move_snake(WINDOW *win, SnakePart *snake, int snake_size)
{
  int i;
  for (i = 0; i < snake_size; i++) {
    mvwaddch(win, snake[i].y, snake[i].x, '#');
  }
}
