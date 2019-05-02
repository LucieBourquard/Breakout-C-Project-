# Breakout-C-Project-
To compile it all, you just have to write the commande "make" under the command prompt 
when you are located in the same directory as the whole project itself. 

To launch it you have to type "/BREAKOUT" just after that (still in the same directory)

We made this project, as the school asked it, using a virtual machine that works under Linux.
This is our fist project in C. So there is still much to learn I think!

We also used the virtual machine to do a little bit of JAVA, and I enjoyed it just as much.

The reason for the outstanding number of files is that the graphic library have been made by school teachers.
Since it was the first time we used a graphic library since we began coding, they may have wanted to keep it simple for us to use it.

So, among all these files, the one we entirely wrote are:
- struct.h (containing the description of the chained list structure of the bricks)
- affichage.c & affichage.h (containing all the functions liked to the graphic display of the game)
- initialisation.c & initialisation.h (containing all the function linked to the initialisation of the 
chained lists representing the bricks to break in the game)
- persist.c & persist.h (containing all the functions linked to data persistance,
the "pause" state and the "high score" option)
- breakout.c (containig the code itself, that uses all of the functions in the previous files)
- makefile (to organise the compilation: WE ONLY WROTE THERE THE LINES CONCERNING THE COMPILATION
OF THE PREVIOUS FILES as it also serves to compile all the elements for the graphic library to work)

