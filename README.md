**Introduction**
This grid-based adventure game challenges players to navigate through a grid while collecting coins, finding a hidden key, and unlocking a door to win the game. The player must avoid stepping on a hidden bomb and manage their limited moves carefully. The game offers multiple difficulty levels, each with a different grid size, number of moves, and undos. Hints are provided to help guide the player toward the key and the door.

**Key Features & Game Mechanics**
Grid Navigation: Players can move up, down, left, or right within the grid using keyboard controls (w, a, s, d).
Difficulty Levels: Players can choose between Easy, Medium, and Hard, which affect grid size, remaining moves, and available undos.
Coin Collection: Collect coins scattered across the grid to earn extra points, moves, and undos.
Hints System: Hints are provided to inform the player if they are getting closer to the key or door.
Bomb Hazard: A bomb is randomly placed on the grid; stepping on it results in immediate game over.
Undo Feature: Players can undo their last move if they make a mistake, up to the limit of allowed undos.
Winning Condition: After collecting the key, players must reach the door to unlock it and win the game.

**How to Run the Game**
Compilation: Compile the program using a C++ compiler. For example, using g++:
bash
Copy code
g++ game.cpp -o game
Running: After compiling, run the executable:
bash
Copy code
./game

**Gameplay Instructions:**
Select a difficulty level when prompted: Easy, Medium, or Hard.
Use the following keys to move the player character:
w: Move up
a: Move left
s: Move down
d: Move right
To undo the last move, press u (if undos are available).
Collect coins to earn points and gain extra moves/undos.
Find the key, then proceed to the door to win.


**Sample Output**


Choose difficulty level (Easy, Medium, Hard): Medium
Moves left: 20   Undos left: 4   Score: 0
Coins collected: 0
Your move (w: up, s: down, a: left, d: right, u: undo): d
Hint: You're getting closer to the key.
Hint: You're getting closer to the door.
P   .   .   .   .   #   #   #   .   .   .
#   #   #   #   .   .   .   .   #   #   #
.   .   .   .   .   .   #   #   #   .   .
.
Boom! You stepped on a bomb! Game over.
