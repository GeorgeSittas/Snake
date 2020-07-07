#include <ncurses.h>

#include "snake.h"
#include "screen.h"
#include "utilities.h"

// Initializes the cursor session settings
void setup_term(void) {
  newterm(NULL, stdout, stdin); // Initializes the screen (curses mode)
  noecho(); // Prevents the input characters from showing up
  curs_set(FALSE); // Makes the cursor invisible
  keypad(stdscr, TRUE); // Enables reading of function keys (eg. arrow keys)
  timeout(1); // Sets an input timer of 1 msec (to keep the snake in motion)
}

// Draws an empty game frame
void setup_screen(void) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (i == 0 || i == ROWS-1)
        set_screen(i, j, WALL);
      else if (j == 0 || j == COLUMNS-1)
        set_screen(i, j, WALL);
      else
        set_screen(i, j, EMPTY);
    }
  }

  set_screen(0, 0, WALL);
  set_screen(ROWS-1, COLUMNS-1, WALL);
  set_screen(0, COLUMNS-1, WALL);
  set_screen(ROWS-1, 0, WALL);
}

void draw_food(void) {
  set_screen(food_row(), food_col(), FOOD);
}

void draw_snake(void) {

  // First, draw the snake's head, based on its current direction
  set_screen(head_row(), head_col(), head_symbol());

  // Then, print the rest of the snake's body
  for (snake_piece_t *curr = game.snake.head->next;
       curr != NULL;
       curr = curr->next)
    set_screen(curr->position.row, curr->position.column, SNAKE_BODY);
}

// Prints the game screen -- a game frame
void render(void) {

  /* mvaddch() forms the frame on a buffer window,
   * before it's printed on the actual game window
   */

  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLUMNS; j++)
      mvaddch(i, j, game.screen[i][j]);

  // Prints the buffer window's contents to the game window
  refresh();
}
