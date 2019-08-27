object_files = main.o snake.o screen.o
header_files = snake.h

CC = gcc
FLAGS = -Wall
LIB = -lncurses

snake: $(object_files)
	$(CC) $(FLAGS) $(LIB) $(object_files) -o snake

main.o: $(header_files)

snake.o: $(header_files)

screen.o: $(header_files)

play: snake
	./snake

clean:
	@echo "Cleaning up .."
	rm $(object_files) snake
