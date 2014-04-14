#include "linked_list.h"

typedef List Snake;

Snake *snake_create(int size);
void snake_move(Snake *snake, Direction direction);
void snake_add_part_to_tail(Snake *snake);
