#include <unistd.h>
#include <ncurses.h>

#include "snake.h"

/* Initializes the cursor session settings */
void setup_term(void) {
  newterm(NULL, stdout, stdin); /* Initializes the screen (curses mode) */
  noecho(); /* Prevents the input characters from showing up */
  curs_set(FALSE); /* Makes the cursor invisible */
  keypad(stdscr, TRUE); /* Enables reading of function keys (eg. arrow keys) */
  timeout(1); /* Sets an input timer of 1 msec (to keep the snake in motion) */
}

/* Draws an empty game frame */
void setup_screen(void) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (i == 0 || i == ROWS-1)
        screen[i][j] = HORIZONTAL_WALL;
      else if (j == 0 || j == COLUMNS-1)
        screen[i][j] = VERTICAL_WALL;
      else
        screen[i][j] = EMPTY;
    }
  }

  screen[0][0] = screen[ROWS-1][COLUMNS-1] = WALL_CORNER;
  screen[0][COLUMNS-1] = screen[ROWS-1][0] = WALL_CORNER;
}

void draw_food(food_t food) {
  screen[food.position.row][food.position.column] = FOOD;
}

void draw_snake(snake_t snake) {
  int head_row = snake.head->position.row;
  int head_col = snake.head->position.column;

  /* First, draw the snake's head, based on its current direction */
  screen[head_row][head_col] = head_symbol(snake.direction);

  /* Then, print the rest of the snake's body */
  for (snake_piece_t *curr = snake.head->next; curr; curr = curr->next)
    screen[curr->position.row][curr->position.column] = SNAKE_BODY;
}

/* Prints the game screen -- a game frame */
void render(void) {
  /* mvaddch() forms the frame on a buffer window, */
  /* before it's printed on the actual game window */

  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLUMNS; j++)
      mvaddch(i, j, screen[i][j]);

  /* Prints the buffer window's contents to the game window */
  refresh();
}
