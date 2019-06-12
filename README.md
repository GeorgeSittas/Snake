# Snake

The snake game window looks like this:

![What the actual game looks like](https://i.imgur.com/Oxw4hcy.png)

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
- Once the game has started, you can move using the arrow keys. If you want to exit the game, press q.
- The snake food is shown as $.
- The snake teleports to the opposing side uppon hitting a side's wall, maintining its direction of movement.
- If you manage to grow the snake to its maximum length, you win.
- If the snake's head bumps into one of its body pieces, you lose.

### Screen configuration
Two adjacent characters that are located on different lines might be more distant apart than
when they are on the same line, depending on your terminal window configuration. In that case,
the snake will seem to move faster when moving vertically. If that bothers you, try adjusting the
line spacing of your terminal window and select whichever one works best for you.
