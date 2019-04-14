# Snake

### Prerequisites / Dependencies
This project uses the NCurses C library, so you need to make sure it's already installed in your system.

([how to install NCurses](https://www.ostechnix.com/how-to-install-ncurses-library-in-linux/))

### Usage
#### Starting the game
```
cd src
make play
```
#### File cleanup
```
cd src
make clean
```

### How to play
- Once the game has started, you can move using the arrow keys.
- The snake food is shown as $.
- The snake teleports to the opposing side uppon hitting a side's wall, maintining its direction of movement.
- If you manage to grow the snake to its maximum length, you win.
- If the snake head bumps into once of its body pieces, you lose.

### About the screen
