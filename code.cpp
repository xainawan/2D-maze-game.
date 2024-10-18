#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int GRID_SIZE = 5; // Define the grid size (5x5 in this case)

class Cell {
public:
    bool hasKey;
    bool hasDoor;
    bool hasCoin;
    bool hasBomb;

    Cell() : hasKey(false), hasDoor(false), hasCoin(false), hasBomb(false) {}
};

class Player {
public:
    int x, y; // Player's position
    int movesLeft;
    bool hasKey;

    Player(int startX, int startY, int allowedMoves)
        : x(startX), y(startY), movesLeft(allowedMoves), hasKey(false) {}
};

// Function to create a maze (5x5 for simplicity)
void createMaze(Cell maze[GRID_SIZE][GRID_SIZE]) {
    // Place key, door, coins, and bomb randomly
    int keyX = rand() % GRID_SIZE;
    int keyY = rand() % GRID_SIZE;
    maze[keyX][keyY].hasKey = true;

    int doorX = rand() % GRID_SIZE;
    int doorY = rand() % GRID_SIZE;
    maze[doorX][doorY].hasDoor = true;

    // Add some coins
    for (int i = 0; i < 5; i++) {
        int coinX = rand() % GRID_SIZE;
        int coinY = rand() % GRID_SIZE;
        maze[coinX][coinY].hasCoin = true;
    }

    // Add a bomb
    int bombX = rand() % GRID_SIZE;
    int bombY = rand() % GRID_SIZE;
    maze[bombX][bombY].hasBomb = true;
}

// Function to display the grid
void displayGrid(Cell maze[GRID_SIZE][GRID_SIZE], Player& player) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (i == player.x && j == player.y) {
                cout << "P "; // Display player at current position
            }
            else {
                cout << ". "; // Empty space
            }
        }
        cout << endl;
    }
}

// Function to move the player
void movePlayer(Player& player, char direction, Cell maze[GRID_SIZE][GRID_SIZE]) {
    switch (direction) {
    case 'w': // Move up
        if (player.x > 0) player.x--;
        break;
    case 's': // Move down
        if (player.x < GRID_SIZE - 1) player.x++;
        break;
    case 'a': // Move left
        if (player.y > 0) player.y--;
        break;
    case 'd': // Move right
        if (player.y < GRID_SIZE - 1) player.y++;
        break;
    default:
        cout << "Invalid move! Use w/a/s/d to move." << endl;
        return;
    }

    // Check for key, door, or coin
    if (maze[player.x][player.y].hasKey) {
        player.hasKey = true;
        maze[player.x][player.y].hasKey = false; // Remove the key
        cout << "You found the key!" << endl;
    }
    if (maze[player.x][player.y].hasDoor && player.hasKey) {
        cout << "You unlocked the door and escaped!" << endl;
        player.movesLeft = 0; // End the game
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed for random number generation

    Player player(2, 2, 20); // Start player at the center (2,2)
    Cell maze[GRID_SIZE][GRID_SIZE]; // Declare the maze

    // Create the maze
    createMaze(maze);

    while (player.movesLeft > 0) {
        cout << "Moves left: " << player.movesLeft << endl;
        displayGrid(maze, player); // Display the grid with player's position

        char input;
        cout << "Enter move (w=up, a=left, s=down, d=right): ";
        cin >> input;
        movePlayer(player, input, maze); // Move the player based on input

        player.movesLeft--; // Decrease the number of remaining moves
        cout << endl; // Add some space for better readability
    }

    cout << "Game over! You have no more moves left." << endl;

    return 0;
}
