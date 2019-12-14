#pragma once

#include <ncurses.h> /* This is needed in order to use the bool type */

#define FOOD       '$'
#define WALL       '#'
#define NORTH_HEAD '^'
#define EAST_HEAD  '>'
#define SOUTH_HEAD 'v'
#define WEST_HEAD  '<'
#define SNAKE_BODY 'o'
#define EMPTY      ' '

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

/* The snake is represented as a linked list of snake pieces */
typedef struct snake {
  int length;
  snake_piece_t *head;
  direction_t direction;
} snake_t;

#define COLUMNS 80
#define ROWS    25

typedef struct game {
  snake_t snake;
  food_t food;
  char screen[ROWS][COLUMNS];
  int score;
} game_t;
