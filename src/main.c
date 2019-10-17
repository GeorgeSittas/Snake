#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "snake.h"

int score = 0;

int main(void) {
  srand(time(NULL));
  setup_term(); /* Initializes the curses settings and enters curses mode */

  snake_t snake;
  food_t food;

  init_snake(&snake); /* Creates a snake of length 8 */
  init_food(&food);   /* Generates the first food */

  while (TRUE) {
    setup_screen(); /* Draw an empty game frame */

    /* Check if the user wants to change the snake's direction or quit */
    process_input(&snake.direction);

    /* Advance the snake's head to its new position */
    advance_head(&snake);

    /* Check if the game is over, in which case the program will terminate */
    switch (game_state(snake)) {
      case WON:  terminate_game_session("You win!");
      case LOST: terminate_game_session("You lose!");
      case STILL_PLAYING: break;
    }

    /* If the snake has consumed the food, it will grow by one */
    /* piece. Otherwise, its tail will be advanced accordingly */

    if (!food.consumed
      && snake.head->position.row    == food.position.row
      && snake.head->position.column == food.position.column)
    {
      snake.length++;
      food.consumed = TRUE;
      score++;
    }
    else
      advance_tail(&snake);

    /* Draw the rest of the current frame */
    draw_snake(snake);
    if (!food.consumed) draw_food(food);

    render(); /* .. and print it */

    /* Generate the next food, if the last one was consumed */
    if (food.consumed) food = generate_food();

    /* Finally, apply a small time delay, in order for the snake */
    /* to move with normal velocity and achieve the specified FPS */

    usleep(DELAY);
  }

  return 0;
}
