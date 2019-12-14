#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "../include/snake.h"
#include "../include/screen.h"
#include "../include/utilities.h"

game_t game;

int main(void) {
  srand(time(NULL));
  setup_term(); /* Initializes the curses settings and enters curses mode */

  init_game(); /* Creates a snake of length 8 and generates the first food */

  while (TRUE) {
    setup_screen(); /* Draw an empty game frame */

    /* Check if the user wants to change the snake's direction or quit */
    process_input();

    /* Advance the snake's head to its new position */
    advance_head();

    /* Check if the game is over, in which case the program will terminate */
    switch (game_state()) {
      case WON:  terminate_game_session("You win!");
      case LOST: terminate_game_session("You lose!");
      case STILL_PLAYING: break;
    }

    /* If the snake has consumed the food, it will grow by one */
    /* piece. Otherwise, its tail will be advanced accordingly */

    if (food_encountered()) grow_snake();
    else advance_tail();

    /* Draw the rest of the current frame */
    draw_snake();
    if (!food_consumed()) draw_food();

    render(); /* .. and print it */

    /* Generate the next food, if the last one was consumed */
    if (food_consumed()) generate_food();

    /* Finally, apply a small time delay, in order for the snake */
    /* to move with normal velocity and achieve the specified FPS */

    usleep(DELAY);
  }

  return 0;
}
