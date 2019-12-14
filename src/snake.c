#include <stdlib.h>
#include <ncurses.h>

#include "../include/snake.h"
#include "../include//utilities.h"

void init_game(void) {
  init_snake();

  /* row is in range [1, ROWS-2], column is in range [1, COLUMNS-2] */
  game.food.position.row = 1 + rand() % (ROWS - 2);
  game.food.position.column = 1 + rand() % (COLUMNS - 2);
  game.food.consumed = FALSE;
}

/* Creates the snake, whose initial length is 8 */
void init_snake(void) {

  /* Create the snake's head */
  game.snake.head = malloc(sizeof(snake_piece_t));
  if (!game.snake.head) exit(EXIT_FAILURE);

  game.snake.length                =  8;
  game.snake.head->position.row    = 10;
  game.snake.head->position.column = 10;
  game.snake.direction             = EAST;

  snake_piece_t **tail = &(game.snake.head->next);

  /* Then, create the rest of its body. The initial snake */
  /* length is 8, so 7 more pieces will be appended to it */

  for (int i = 0, col = head_col(); i < 7; i++) {
    *tail = malloc(sizeof(snake_piece_t));
    if (!*tail) exit(EXIT_FAILURE);

    /* Each piece will be added to the left of the last piece that was */
    /* added (every piece will be in the same row as the snake's head) */

    (*tail)->position.row = head_row();
    (*tail)->position.column = --col;
    (*tail)->next = NULL;

    tail = &((*tail)->next);
  }
}

void generate_food(void) {

  /* Makes sure that the food is generated on an unoccupied screen cell */
  do {

    /* row is in range [1, ROWS-2], column is in range [1, COLUMNS-2] */
    game.food.position.row = 1 + rand() % (ROWS - 2);
    game.food.position.column = 1 + rand() % (COLUMNS - 2);

  } while (!is_char_in_screen(food_row(), food_col(), EMPTY));

  game.food.consumed = FALSE;
}

/* Checks whether the user wants to change the snake's direction or quit. */
/* Note: the snake's direction can be changed only if the new direction is */
/* perpendicular to its current direction */

void process_input(void) {
  switch (getch()) {
    case KEY_LEFT:
      if (snake_direction() != EAST) game.snake.direction = WEST;
      break;
    case KEY_RIGHT:
      if (snake_direction() != WEST) game.snake.direction = EAST;
      break;
    case KEY_UP:
      if (snake_direction() != SOUTH) game.snake.direction = NORTH;
      break;
    case KEY_DOWN:
      if (snake_direction() != NORTH) game.snake.direction = SOUTH;
      break;
    case 'Q':
    case 'q':
      terminate_game_session("Ciao!");
      break;
  }
}

/* Advances the snake's head, according to its direction */
void advance_head(void) {
  snake_piece_t *new_head = malloc(sizeof(snake_piece_t));
  if (!new_head) exit(EXIT_FAILURE);

  find_next_position(&new_head);
  new_head->next = game.snake.head;
  game.snake.head = new_head;
}

/* Advances the snake's tail to its next position */
void advance_tail(void) {
  snake_piece_t *piece = game.snake.head;

  /* Find the snake piece that is adjacent to its tail */
  while (piece->next->next != NULL)
    piece = piece->next;

  /* Remove the snake's tail from its body and erase it from the screen */
  snake_piece_t *tail = piece->next;
  piece->next = NULL;
  set_screen(tail->position.row, tail->position.column, EMPTY);
  free(tail);
}

/* Determines the snake head symbol, based on the snake's direction */
char head_symbol(void) {
  switch (snake_direction()) {
    case NORTH: return NORTH_HEAD;
    case SOUTH: return SOUTH_HEAD;
    case  EAST: return EAST_HEAD;
    case  WEST: return WEST_HEAD;
    default: exit(EXIT_FAILURE); /* Should not reach this point */
  }
}

/* Calculates the head's new position, based on the snake's direction */
void find_next_position(snake_piece_t **new_head) {
  (*new_head)->position.row    = head_row();
  (*new_head)->position.column = head_col();

  /* If the snake "hits" a side wall, it will "teleport" to the */
  /* opposing side, while maintining its direction of movement */

  switch (snake_direction()) {
    case NORTH:
      (*new_head)->position.row = (head_row() - 1 == 0)
                                ? ROWS - 2
                                : head_row() - 1;
      break;
    case SOUTH:
      (*new_head)->position.row = 1 + head_row() % (ROWS-2);
      break;
    case EAST:
      (*new_head)->position.column = 1 + head_col() % (COLUMNS-2);
      break;
    case WEST:
      (*new_head)->position.column = (head_col() - 1 == 0)
                                    ? COLUMNS - 2
                                    : head_col() - 1;
      break;
    default: exit(EXIT_FAILURE); /* Should not reach this point */
  }
}

void destroy_snake(void) {
  snake_piece_t *curr = game.snake.head;

  while (curr != NULL) {
    snake_piece_t *to_be_deleted = curr;
    curr = curr->next;
    free(to_be_deleted);
  }
}

/* Checks whether the game has ended, in which case the */
/* appropriate signalling (state) value is returned */

state_t game_state(void) {

  /* Check whether the snake has reached the maximum length */
  if (snake_length() == (ROWS - 2) * (COLUMNS - 2))
    return WON;

  /* Check whether the snake's head has bumped into one of its body pieces */
  for (snake_piece_t *curr = game.snake.head->next;
       curr->next != NULL;
       curr = curr->next)
  {
    if (head_row() == curr->position.row
     && head_col() == curr->position.column) return LOST;
  }

  return STILL_PLAYING;
}
