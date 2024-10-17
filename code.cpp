#include <iostream>
using namespace std;

class Player {
public:
    int x, y; // Player's position

    // Constructor to initialize player's starting position
    Player(int startX, int startY) : x(startX), y(startY) {}
};

// Function to display the grid
void displayGrid(int gridSize, Player* player) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (i == player->x && j == player->y) {
                cout << "P "; // Display player at current position
            } else {
                cout << ". "; // Empty space
            }
        }
        cout << endl;
    }
}

// Function to move the player
void movePlayer(Player* player, char direction, int gridSize) {
    switch (direction) {
        case 'w': // Move up
            if (player->x > 0) player->x--;
            break;
        case 's': // Move down
            if (player->x < gridSize - 1) player->x++;
            break;
        case 'a': // Move left
            if (player->y > 0) player->y--;
            break;
        case 'd': // Move right
            if (player->y < gridSize - 1) player->y++;
            break;
        default:
            cout << "Invalid move! Use w/a/s/d to move." << endl;
    }
}

int main() {
    int gridSize = 5; // Define the grid size (5x5 in this case)
    Player player(2, 2); // Start player at the center (2,2)
    
    int movesLeft = 10; // Number of moves allowed
    while (movesLeft > 0) {
        cout << "Moves left: " << movesLeft << endl;
        displayGrid(gridSize, &player); // Display the grid with player's position
        char input;
        cout << "Enter move (w=up, a=left, s=down, d=right): ";
        cin >> input;
        movePlayer(&player, input, gridSize); // Move the player based on input
        movesLeft--; // Decrease the number of remaining moves
        cout << endl; // Add some space for better readability
    }
    
    cout << "Game over! You have no more moves left." << endl;
    return 0;
}
