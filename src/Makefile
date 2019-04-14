objects_files = main.o snake.o screen.o
headers_files = snake.h

CC = gcc
FLAGS = -Wall
LIB = -lncurses

snake: $(objects_files)
	$(CC) $(FLAGS) $(LIB) $(objects_files) -o snake

main.o: $(headers_files)

snake.o: $(headers_files)

screen.o: $(headers_files)

run: snake
	./snake

clean:
	@echo "Cleaning up .."
	rm $(objects_files) snake
