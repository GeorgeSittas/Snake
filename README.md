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
- If you manage to reach the snake's maximum length, you win.
- If the snake head bumps into once of its body pieces, you lose.

### Screen configuration
Two adjacent characters that are located on different lines, are more distant than when they are on the same line, that’s why the snake moves faster when moving vertically. If that annoys you, you can try adjusting the line spacing of your terminal window and select whichever one works best for you.
