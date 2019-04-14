#pragma once

#include <ncurses.h>

#define COLUMNS   80
#define ROWS      25
#define DELAY 100000

#define HORIZONTAL_WALL '-'
#define VERTICAL_WALL   '|'
#define WALL_CORNER     '+'
#define NORTH_HEAD      '^'
#define EAST_HEAD       '>'
#define SOUTH_HEAD      'v'
#define WEST_HEAD       '<'
#define SNAKE_BODY      'o'
#define EMPTY           ' '
#define FOOD            '$'

extern char screen[ROWS][COLUMNS];

typedef enum {STILL_PLAYING, WON, LOST} state_t;
typedef enum {NORTH, EAST, SOUTH, WEST} direction_t;

typedef struct position {
  int row;
  int column;
} position_t;

typedef struct food {
  position_t position;
  bool consumed;
} food_t;

typedef struct snake_piece {
  position_t position;
  struct snake_piece *next;
} snake_piece_t;

/* The snake is represented as a linked list of snake piece positions */
typedef struct snake {
  int length;
  snake_piece_t *head;
  direction_t direction;
} snake_t;

state_t game_state(snake_t);
food_t generate_food(void);

void setup_term(void);
void setup_screen(void);
void draw_food(food_t);
void draw_snake(snake_t);
void render(void);

void init_snake(snake_t *);
void init_food(food_t *);
void process_input(direction_t *);
void advance_head(snake_t *);
void advance_tail(snake_t *);
char head_symbol(direction_t);
void next_position(direction_t, snake_piece_t *, snake_piece_t *);
void terminate_game_session(char *);
