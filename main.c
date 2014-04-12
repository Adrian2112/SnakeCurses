#include <ncurses.h>
 
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20

WINDOW *create_world();
 
int main(int argc, char *argv[]) {
 
    WINDOW *world;
 
    initscr();
    noecho();
    cbreak();
    timeout(TICKRATE);
    keypad(stdscr, TRUE);
    
    refresh();
 
    world = create_world();
 
    box(world, 0 , 0);
 
    wrefresh(world);
 
    getch();
 
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
