#include <ncurses.h>
#include <stdlib.h>

#include "snake.h"
#include "utilities.h"

int food_row(void) {
  return game.food.position.row;
}

int food_col(void) {
  return game.food.position.column;
}

int head_row(void) {
  return game.snake.head->position.row;
}

int head_col(void) {
  return game.snake.head->position.column;
}

int snake_length(void) {
  return game.snake.length;
}

direction_t snake_direction(void) {
  return game.snake.direction;
}

int score(void) {
  return game.score;
}

bool food_encountered(void) {
  return (!food_consumed()
        && head_row() == food_row()
        && head_col() == food_col());
}

bool food_consumed(void) {
  return game.food.consumed;
}

void grow_snake(void) {
  game.snake.length++;
  game.food.consumed = true;
  game.score++;
}

void set_screen(int row, int col, char ch) {
  game.screen[row][col] = ch;
}

bool is_char_in_screen(int row, int col, char ch) {
  return (game.screen[row][col] == ch);
}

void terminate_game_session(char *exit_message) {
  endwin(); // Exits the curses mode
  printf("%s\nScore: %d\n", exit_message, game.score);
  destroy_snake();
  exit(EXIT_SUCCESS);
}
