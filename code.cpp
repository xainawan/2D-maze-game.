
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// Class Cell
class Cell {
public:
    int value;
    Cell* rightNeighbor;
    Cell* belowNeighbor;
    Cell(int inputVal) {
        value = inputVal;
        rightNeighbor = nullptr;
        belowNeighbor = nullptr;
    }
};

// Class Coord (for position)
struct Coord {
public:
    int row;
    int col;
    Coord(int r = 0, int c = 0) {
        row = r;
        col = c;
    }
};

// Build the game board grid
Cell* createGrid(int totalRows, int totalCols) {
    Cell* gridStart = nullptr;
    Cell* rowHead = nullptr;
    Cell* prevRowHead = nullptr;

    for (int r = 0; r < totalRows; ++r) {
        Cell* leftNeighbor = nullptr;
        for (int c = 0; c < totalCols; ++c) {
            Cell* newCell = new Cell(0);
            if (c == 0) rowHead = newCell;
            if (leftNeighbor) leftNeighbor->rightNeighbor = newCell;
            if (prevRowHead) {
                prevRowHead->belowNeighbor = newCell;
                prevRowHead = prevRowHead->rightNeighbor;
            }
            leftNeighbor = newCell;
        }
        prevRowHead = rowHead;
        if (r == 0) gridStart = rowHead;
    }
    return gridStart;
}

// Display the grid with player and key/door positions
void showGrid(Cell* gridStart, int totalRows, int totalCols, const Coord& player, bool hasKey) {
    Cell* row = gridStart;
    int rowNum = 0;
    while (row) {
        Cell* col = row;
        int colNum = 0;
        while (col) {
            if (rowNum == player.row && colNum == player.col) {
                cout << "P   ";
            }
            else {
                if (rowNum == 0 || rowNum == totalRows - 1 || colNum == 0 || colNum == totalCols - 1) {
                    cout << "#   ";
                }
                else {
                    cout << ".   ";
                }
            }
            col = col->rightNeighbor;
            colNum++;
        }
        cout << endl;
        row = row->belowNeighbor;
        rowNum++;
    }
}

// Generate random coordinates
Coord randomCoord(int maxRows, int maxCols) {
    int x = rand() % (maxRows - 2) + 1;
    int y = rand() % (maxCols - 2) + 1;
    return Coord(x, y);
}

// Place coins in random positions
void distributeCoins(Coord coinLocs[], int totalCoins, int maxRows, int maxCols) {
    for (int i = 0; i < totalCoins; ++i) {
        coinLocs[i] = randomCoord(maxRows, maxCols);
    }
}

// Check if a coin exists at the player's position
bool checkCoin(const Coord& player, const Coord coinLocs[], bool pickedCoins[], int totalCoins) {
    for (int i = 0; i < totalCoins; ++i) {
        if (!pickedCoins[i] && player.row == coinLocs[i].row && player.col == coinLocs[i].col) {
            pickedCoins[i] = true;
            return true;
        }
    }
    return false;
}

// Calculate distance between two coordinates
int calcDistance(const Coord& a, const Coord& b) {
    return abs(a.row - b.row) + abs(a.col - b.col);
}

// Give player proximity hints
void provideHint(const Coord& player, const Coord& key, const Coord& door, int prevKeyDist, int prevDoorDist) {
    int currKeyDist = calcDistance(player, key);
    int currDoorDist = calcDistance(player, door);

    if (currKeyDist < prevKeyDist) {
        cout << "Hint: You're getting closer to the key.\n";
    }
    else if (currKeyDist > prevKeyDist) {
        cout << "Hint: You're getting farther from the key.\n";
    }

    if (currDoorDist < prevDoorDist) {
        cout << "Hint: You're getting closer to the door.\n";
    }
    else if (currDoorDist > prevDoorDist) {
        cout << "Hint: You're getting farther from the door.\n";
    }
}

int main() {
    srand(time(0));

    int totalRows, totalCols, remainingMoves, availableUndos;
    string gameLevel;

    cout << "Choose difficulty level (Easy, Medium, Hard): ";
    cin >> gameLevel;

    switch (tolower(gameLevel[0])) {
    case 'e':
        totalRows = totalCols = 10;
        remainingMoves = 24;
        availableUndos = 6;
        break;
    case 'm':
        totalRows = totalCols = 15;
        remainingMoves = 20;
        availableUndos = 4;
        break;
    case 'h':
        totalRows = totalCols = 20;
        remainingMoves = 18;
        availableUndos = 1;
        break;
    default:
        cout << "Invalid input. Defaulting to Easy level.\n";
        totalRows = totalCols = 10;
        remainingMoves = 24;
        availableUndos = 6;
    }

    Cell* grid = createGrid(totalRows, totalCols);

    Coord playerPos(1, 1);
    Coord lastPos = playerPos;
    Coord keyLoc = randomCoord(totalRows, totalCols);
    Coord doorLoc = randomCoord(totalRows, totalCols);
    Coord bombLoc = randomCoord(totalRows, totalCols);

    const int numCoins = 5;
    Coord coinLocs[numCoins];
    bool pickedCoins[numCoins] = { false };
    distributeCoins(coinLocs, numCoins, totalRows, totalCols);

    bool hasKey = false;
    int gameScore = 0;
    int coinsCollected = 0;
    char command;

    int prevKeyDist = calcDistance(playerPos, keyLoc);
    int prevDoorDist = calcDistance(playerPos, doorLoc);

    while (true) {
        if (remainingMoves <= 0) {
            cout << "Game Over: You're out of moves!\n";
            break;
        }

        cout << "Moves left: " << remainingMoves << "\tUndos left: " << availableUndos << "\tScore: " << gameScore << "\n";
        cout << "Coins collected: " << coinsCollected << "\n";
        cout << "Your move (w: up, s: down, a: left, d: right, u: undo): ";
        cin >> command;

        bool playerMoved = false;
        bool validMove = true;

        switch (command) {
        case 'w':
            if (playerPos.row > 1) {
                lastPos = playerPos;
                playerPos.row--;
                playerMoved = true;
            }
            else {
                validMove = false;
            }
            break;
        case 's':
            if (playerPos.row < totalRows - 2) {
                lastPos = playerPos;
                playerPos.row++;
                playerMoved = true;
            }
            else {
                validMove = false;
            }
            break;
        case 'a':
            if (playerPos.col > 1) {
                lastPos = playerPos;
                playerPos.col--;
                playerMoved = true;
            }
            else {
                validMove = false;
            }
            break;
        case 'd':
            if (playerPos.col < totalCols - 2) {
                lastPos = playerPos;
                playerPos.col++;
                playerMoved = true;
            }
            else {
                validMove = false;
            }
            break;
        case 'u':
            if (availableUndos > 0) {
                playerPos = lastPos;
                availableUndos--;
                cout << "Undo successful! Back to the previous position.\n";
            }
            else {
                cout << "No undos left!\n";
            }
            continue;
        default:
            validMove = false;
        }

        if (!validMove) {
            cout << "Invalid move! You hit the border.\n";
        }

        if (playerMoved) {
            remainingMoves--;

            if (checkCoin(playerPos, coinLocs, pickedCoins, numCoins)) {
                coinsCollected++;
                gameScore += 2;
                remainingMoves++;
                availableUndos++;
                cout << "Coin collected! +2 points, +1 move, +1 undo.\n";
            }

            provideHint(playerPos, keyLoc, doorLoc, prevKeyDist, prevDoorDist);

            prevKeyDist = calcDistance(playerPos, keyLoc);
            prevDoorDist = calcDistance(playerPos, doorLoc);
        }

        showGrid(grid, totalRows, totalCols, playerPos, hasKey);

        if (playerPos.row == bombLoc.row && playerPos.col == bombLoc.col) {
            cout << "Boom! You stepped on a bomb! Game over.\n";
            break;
        }

        if (playerPos.row == keyLoc.row && playerPos.col == keyLoc.col && !hasKey) {
            hasKey = true;
            cout << "You found the key! Now head to the door.\n";
        }

        if (hasKey && playerPos.row == doorLoc.row && playerPos.col == doorLoc.col) {
            cout << "Congratulations! You unlocked the door and won the game!\n";
            break;
        }
    }

    delete grid;
    return 0;
}
