OBJ_DIR = ./src
INC_DIR = ./include

OBJS = $(OBJ_DIR)/main.o  $(OBJ_DIR)/snake.o \
       $(OBJ_DIR)/screen.o $(OBJ_DIR)/utilities.o

CFLAGS = -Wall -I$(INC_DIR)
LIB = -lncurses
CC = gcc

EXEC = snake

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) $(LIB) $(OBJS) -o $(EXEC)

.SILENT: $(OBJS) # Silence implicit rule output
.PHONY: clean

play: $(EXEC)
	@./$(EXEC)

clean:
	@echo "Cleaning up .."
	@rm -f $(OBJS) $(EXEC)
