#pragma once

#include <ncurses.h> /* This is needed in order to use the bool type */

#include "snake.h"

int food_row(void);
int food_col(void);

int head_row(void);
int head_col(void);

int snake_length(void);
direction_t snake_direction(void);

int score(void);

bool food_encountered(void);
bool food_consumed(void);
void grow_snake(void);

void set_screen(int, int, char);
bool is_char_in_screen(int, int, char);

void terminate_game_session(char *);

/* FPS: number of frames per second (basically the frame printing frequency) */
/* DELAY: time delay needed to achieve the specified FPS (in micro seconds) */

#define SEC_IN_MICROSEC 1000000

#define FPS 10
#define DELAY (SEC_IN_MICROSEC / FPS) /* time = 1 (sec) / frequency */
