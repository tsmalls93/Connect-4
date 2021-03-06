# Connect 4 game with AI

## Building and running with g++
First clone the repo and run the following command in the local repo directory:

```shell
$ g++ -std=c++11 main.cpp AI.cpp MainGame.cpp Board.cpp -o Connect_4
$ ./Connect_4
```

## Building and running with CMake
First clone down the repo and run the following commands in the local repo directory (you will need CMake 3.10 or higher):

```shell
$ cmake -H. -Bbuild
$ cmake --build build -- -j3
$ cd build
$ ./Connect_4
```

## Playing

You will be asked if you want to cheat, and it is probably your only chance at winning.
Yet for it to be fun I recommend saying no. Just key in `y` or `n` and hit enter.

```
Welcome to Connect 4 AI
Your only chance of winning is to play first,
therefore you will make the first move.
Do you want to cheat? y/n
```

Then you will see an ASCII board (sorry I don't make GUIs).
Each slot is represented by `( )`.
The human coin will be represented by an `X` and the computer coin will be an `O`.

```
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
 1  2  3  4  5  6  7
Human's turn!

Enter slot number:
```

Now you will enter a slot of your choice.
Statistically, your only chance at winning is to choose the center slot, so we will key in `4` and hit enter.
You will visually see each slot being scored by the AI.
If you chose to cheat, the scores of the slot will be shown on your turn as well.
Hit `Enter` or `Return` when you are ready for your turn.

```
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )(X)( )( )( )
 1  2  3  4  5  6  7
Computer's turn!

Move 1 has weight -3
Move 7 has weight -3
Move 2 has weight -3
Move 6 has weight -3
Move 3 has weight -1
Move 5 has weight -1
Move 4 has weight 0
Computer chose slot 4
Press Enter
```

You will now see the computer's move applied to the board and the process repeats until the game is over.
Good luck!

```
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )( )( )( )( )
( )( )( )(O)( )( )( )
( )( )( )(X)( )( )( )
 1  2  3  4  5  6  7
Human's turn!

Enter slot number:
```
