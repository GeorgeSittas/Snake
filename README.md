# Snake

Goal for this project is to make a [Snake](https://en.wikipedia.org/wiki/Snake_(video_game_genre)) game in C. The game window looks like this:

![](https://imgur.com/njB0HCL.png)

### Install
```
git clone https://github.com/GeorgeSittas/Snake.git
```

### Prerequisites / Dependencies
This project uses the NCurses C library, so you need to make sure it's already installed in your system.

([how to install the NCurses library in Linux](https://www.ostechnix.com/how-to-install-ncurses-library-in-linux/))

### Usage
#### Starting the game
```
cd Snake
make play
```
#### File cleanup
```
cd Snake
make clean
```

### How to play
- Once the game has started, you can move using the arrow keys. If you want to exit the game, press q or Q.
- The snake food is shown as $ (_capitalism intensifies_).
- The snake teleports to the opposing side uppon hitting a side's wall, maintining its direction of movement.
- If you manage to grow the snake to its maximum length, you win.
- If the snake's head bumps into one of its body pieces, you lose.

### Screen configuration
Two adjacent characters that are located on different lines might be more distant apart than
when they are on the same line<br/>, depending on your terminal window configuration. In that case,
the snake will seem to move faster when moving vertically. If that bothers<br/> you, try adjusting the
line spacing of your terminal window and select whichever one works best for you.
