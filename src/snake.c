#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "snake.h"

/* Creates the snake, whose initial length is 8 */
void init_snake(snake_t *snake) {

  /* Create the snake's head */
  snake->head = malloc(sizeof(snake_piece_t));
  if (!snake->head) exit(EXIT_FAILURE);

  snake->length                =  8;
  snake->head->position.row    = 10;
  snake->head->position.column = 10;
  snake->direction             = EAST;

  snake_piece_t **tail = &(snake->head->next);

  /* Then, create the rest of its body. The initial snake */
  /* length is 8, so 7 more pieces will be appended to it */

  for (int i = 0, col = snake->head->position.column; i < 7; i++) {
    *tail = malloc(sizeof(snake_piece_t));
    if (!*tail) exit(EXIT_FAILURE);

    /* Each piece will be added to the left of the last piece that was */
    /* added (every piece will be in the same row as the snake's head) */

    (*tail)->position.row = snake->head->position.row;
    (*tail)->position.column = --col;
    (*tail)->next = NULL;

    tail = &((*tail)->next);
  }
}

/* Generates the first food */
void init_food(food_t *food) {

  /* row is in range [1, ROWS-2], column is in range [1, COLUMNS-2] */
  food->position.row = 1 + rand() % (ROWS - 2);
  food->position.column = 1 + rand() % (COLUMNS - 2);
  food->consumed = FALSE;
}

/* Advances the snake's head, according to its direction */
void advance_head(snake_t *snake) {
  snake_piece_t *new_head = malloc(sizeof(snake_piece_t));
  if (!new_head) exit(EXIT_FAILURE);

  next_position(snake->direction, snake->head, new_head);
  new_head->next = snake->head;
  snake->head    = new_head;
}

/* Advances the snake's tail to its next position */
void advance_tail(snake_t *snake) {
  snake_piece_t *piece = snake->head;

  /* Find the snake piece that is adjacent to its tail */
  while (piece->next->next)
    piece = piece->next;

  /* Remove the snake's tail from its body and erase it from the screen */
  snake_piece_t *tail = piece->next;
  piece->next = NULL;
  screen[tail->position.row][tail->position.column] = EMPTY;
  free(tail);
}

/* Returns a new food instance */
food_t generate_food(void) {
  food_t new_food;

  /* Makes sure that the food is generated on an unoccupied screen cell */
  do {
    init_food(&new_food);
  } while (screen[new_food.position.row][new_food.position.column] != EMPTY);

  return new_food;
}

/* Determines the snake head symbol, based on the snake's direction */
char head_symbol(direction_t dir) {
  switch (dir) {
    case NORTH: return NORTH_HEAD;
    case SOUTH: return SOUTH_HEAD;
    case  EAST: return EAST_HEAD;
    case  WEST: return WEST_HEAD;
    default: exit(EXIT_FAILURE); /* Should not reach this point */
  }
}

/* Checks whether the user wants to change the snake's direction or quit. */
/* Note: the snake's direction can be changed only if the new direction is */
/* perpendicular to its current direction */

void process_input(direction_t *direction) {
  switch (getch()) {
    case KEY_LEFT:
      if (*direction != EAST) *direction = WEST;
      break;
    case KEY_RIGHT:
      if (*direction != WEST) *direction = EAST;
      break;
    case KEY_UP:
      if (*direction != SOUTH) *direction = NORTH;
      break;
    case KEY_DOWN:
      if (*direction != NORTH) *direction = SOUTH;
      break;
    case QUIT:
      terminate_game_session("Ciao!");
      break;
  }
}

/* Calculates the head's new position, based on the snake's direction */
void next_position(direction_t dir, snake_piece_t *head,
                    snake_piece_t *new_head) {
  int temp;

  new_head->position.row    = head->position.row;
  new_head->position.column = head->position.column;

  /* If the snake "hits" a side wall, it will "teleport" to the */
  /* opposing side, while maintining its direction of movement */

  switch (dir) {
    case NORTH:
      temp = head->position.row - 1;
      new_head->position.row =  (temp == 0) ? ROWS - 2 : temp;
      break;
    case SOUTH:
      new_head->position.row = 1 + head->position.row % (ROWS-2);
      break;
    case EAST:
      new_head->position.column = 1 + head->position.column % (COLUMNS-2);
      break;
    case WEST:
      temp = head->position.column - 1;
      new_head->position.column = (temp == 0) ? COLUMNS - 2 : temp;
      break;
    default: exit(EXIT_FAILURE); /* Should not reach this point */
  }
}

/* Checks whether the game has ended, in which case the */
/* appropriate signalling (state) value is returned */

state_t game_state(snake_t snake) {

  /* Check whether the snake has reached the maximum length */
  if (snake.length == (ROWS - 2) * (COLUMNS - 2))
    return WON;

  /* Check whether the snake's head has bumped into one of its body pieces */
  for (snake_piece_t *temp = snake.head->next; temp->next; temp = temp->next)
    if (snake.head->position.row == temp->position.row
      && snake.head->position.column == temp->position.column)
      return LOST;

  return STILL_PLAYING;
}

void terminate_game_session(char *exit_message) {
  endwin(); /* Exits the curses mode */
  printf("%s\n", exit_message);
  exit(EXIT_SUCCESS);
}
