Author Name : Rehan Ayub
Readme Have : The flow Diagram and All the Functioning of the project in the form of report 

Menu setup:
For the menu we have developed two files, one named as menu.cpp
and menu.hpp. Menu.hpp represents all the functions, structure for
the menu and variables initialization; they all are initialized in that file
which then used for developing the menu. Menu.cpp represents all
the working for the menu. We have taken the menu photo from the
internet and then implemented it and developed all the options
required in the menu like Start game, levels, scoreboard and exit.
The challenge we face while developing it is how to link files with each
other and how to call them in the main and in drawing part as well to
font it on the right spot on screen.
Levels Setup:
We have developed the same two files level.hpp and level.cpp.
Level.hpp is for initializing all the variables, functions and structure
which are later used for implementing the levels’ part. Level.cpp

represents the working of the levels. These files are then linked with
the menu as well when the player selects the menu option, they get
open. Enemy numbers are updated for each level as mentioned in the
question. For the continuous part continuously added 2 in enemy
number after each 20 seconds and this thing I implement in main in
the event part.
Counter and Time:
We have developed two variables one named as moves and the other
is time. The same time is used for the two player modes; they both
have shared the common time. Moves variable is placed in the main
game loop just after updating the motion of two players.
Scoring system:
It is the most challenging part of the game. The issue we are facing is
the number of tiles in one move are unable to be calculated and it has
taken over max time. So to correct it we have developed the two
functions and then compared tiles at the end.
Score Board:
For the scoreboard a function is developed in which we develop a file
named as score in which the score is updated in descending order,
and it contains top 5 scores by comparing scores in main each time
and then update accordingly. For descending order, we have
developed a sorting function in which the bubble sorting concept is
used.
Enemy Motion:

A function named move is called in which the speed is increased by
increasing dx and dy by 1.5 for every 20 seconds. Game time is also
implemented and displayed on the screen. And for the motion we
have made a circular name function in which we have assigned angle
and speed and then implement it by using a loop.
End Menu Setup:
For the end menu we have used the same image that we have used
for the main menu and then implement options required and linking
each option with desired function and it is set up at the end after the
game gets over.

Two Player modes:
To complete the two-player mode, I used the same game board for
both players, allowing interaction between them. Each player had
separate position variables (x, y for Player 1 and x2, y2 for Player 2)
and for their motion I have used the variables (dx, dy for player1 and
dx2,dy2 for player2) and independent controls as asked in the part
that is (up , down , left , right arrows for player1 and W,S,A,D for
player2) . I created two trial types using different numbers in the grid
to differentiate it for both the players: 2 for Player 1 and 3 for Player 2.
Then I implemented all the collision rules just after updating the
position of both the players. The main challenge was managing
collisions. If one player touches the other player or their trail while
moving, the player that strikes the tile of the other will die. I used
player1_alive and player2_alive Booleans to track this. I have also
displayed the scores of both players.

A big issue was making sure that I have to implement that if the player
died then the dead player should stop moving. I solved this by
setting their movement values (dx, dy) to zero when they died.
Another issue that is causing the trouble is setting it up in a game
loop. It overlaps both the single mode and double mode too, so I
implemented conditions in game loop separate both modes and it
somehow works.

![Screenshot 2025-06-28 000147](https://github.com/user-attachments/assets/ed8c4512-1568-4338-843e-d3bd090e05ca)
