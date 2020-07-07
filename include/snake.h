#pragma once

#include <ncurses.h>

#include "snake_types.h"

#define FOOD       '$'
#define WALL       '#'
#define NORTH_HEAD '^'
#define EAST_HEAD  '>'
#define SOUTH_HEAD 'v'
#define WEST_HEAD  '<'
#define SNAKE_BODY 'o'
#define EMPTY      ' '

extern game_t game;

void init_game(void);
void init_snake(void);
void generate_food(void);
void process_input(void);
void advance_head(void);
void advance_tail(void);
char head_symbol(void);
void find_next_position(snake_piece_t **);
void destroy_snake(void);
state_t game_state(void);
