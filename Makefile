object_files = ./src/main.o ./src/utilities.o ./src/snake.o ./src/screen.o
header_files = ./include/snake_types.h ./include/snake.h \
							 ./include/screen.h ./include/utilities.h

CC = gcc
FLAGS = -Wall
LIB = -lncurses

snake: $(object_files)
	$(CC) $(FLAGS) $(LIB) $(object_files) -o snake

main.o: $(header_files)

utilities.o: $(header_files)

snake.o: $(header_files)

screen.o: $(header_files)

play: snake
	./snake

clean:
	@echo "Cleaning up .."
	rm $(object_files) snake
