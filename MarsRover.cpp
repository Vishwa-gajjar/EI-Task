#include <bits/stdc++.h>

using namespace std;

// Defining the Command Pattern
class Commands {
public:
    virtual void execute(class MarsRover& rover) = 0;
};

class MoveCommand : public Commands {
public:
    void execute(class MarsRover& rover) override;
};

class TurnLeftCommand : public Commands {
public:
    void execute(class MarsRover& rover) override;
};

class TurnRightCommand : public Commands {
public:
    void execute(class MarsRover& rover) override;
};

// Define the MarsRover class
class MarsRover {
public:
    // Constructor
    MarsRover(int x, int y, char direction, int width, int height, const std::vector<std::pair<int, int>>& obstacles);
    // Commands
    void move();
    void turnLeft();
    void turnRight();
    // Validation
    bool isObstacle(int x, int y);
    bool isValidPosition(int x, int y);
    // Printing Status
    string sendStatusReport();

private:
    int x;
    int y;
    char direction;
    int width;
    int height;
    std::vector<std::pair<int, int>> obstacles;
};

// Constructor - Print initial rover status
MarsRover::MarsRover(int x, int y, char direction, int width, int height, const std::vector<std::pair<int, int>>& obstacles)
    : x(x), y(y), direction(direction), width(width), height(height), obstacles(obstacles) {
        cout << endl << "Initial Rover status --> " << sendStatusReport()<<endl;
    }

// Implementing Move Command
void MarsRover::move() {
    int nextX = x, nextY = y;

    // Calculate the next position based on the current direction
    if (direction == 'N') {
        nextY += 1;
    } else if (direction == 'S') {
        nextY -= 1;
    } else if (direction == 'E') {
        nextX += 1;
    } else if (direction == 'W') {
        nextX -= 1;
    }

    // Check if the next position is within the grid
    if (x >= 0 && x < width && y >= 0 && y < height) {
        // Check if the next position is not an obstacle
        if (!isObstacle(nextX, nextY)) {
            // Update position
            x = nextX;
            y = nextY;
        }
    }
}

bool MarsRover::isObstacle(int x, int y) {
    // Check if the position contains an obstacle
    for (const auto& obstacle : obstacles) {
        if (obstacle.first == x && obstacle.second == y) {
            return true;
        }
    }
    return false;
}

void MarsRover::turnLeft() {
    // Left turn logic
    if (direction == 'N') {
        direction = 'W';
    } else if (direction == 'W') {
        direction = 'S';
    } else if (direction == 'S') {
        direction = 'E';
    } else if (direction == 'E') {
        direction = 'N';
    }
}

void MarsRover::turnRight() {
    // Right turn logic
    if (direction == 'N') {
        direction = 'E';
    } else if (direction == 'E') {
        direction = 'S';
    } else if (direction == 'S') {
        direction = 'W';
    } else if (direction == 'W') {
        direction = 'N';
    }
}

string MarsRover::sendStatusReport() {
    // Generate and return a status report
    string obstacleDetected = isObstacle(x, y) ? "Obstacle detected." : "No obstacles detected.";
    return "Rover Status --> At (" + to_string(x) + ", " + to_string(y) + ") facing " + direction + ". " + obstacleDetected;
}

// Function to control the rover interactively
void controlRover(MarsRover& rover, vector<char> moves) {
    for (char move : moves) {
        if (move == 'M') {
            rover.move();
            cout << "For Move M: " << endl;
            cout << rover.sendStatusReport() << endl;
        } else if (move == 'L') {
            rover.turnLeft();
            cout << "For Move L: " << endl;
            cout << rover.sendStatusReport() << endl;
        } else {
            rover.turnRight();
            cout << "For Move R: " << endl;
            cout << rover.sendStatusReport() << endl;
        } 
    }
}

int main() {
    // Initializing the Rover
    
    // Set grid width and height - Eg: 10 X 10
    int gridWidth, gridHeight;
    cout << "Enter the grid width and height: ";
    cin >> gridWidth >> gridHeight;
    
    // Set initial Position
    int x, y;
    cout << "Enter initial position (x y): ";
    cin >> x >> y;
    
    // Set direction
    char direction;
    cout << "Enter the initial direction (N, S, E, or W): ";
    cin >> direction;
    
    // Set obstacles - Eg: [(2, 2), (3, 5)]
    std::vector<std::pair<int, int>> obstacles;
    int numObstacles;
    cout << "Enter the number of obstacles: ";
    cin >> numObstacles;
    for (int i = 0; i < numObstacles; ++i) {
        int obstacleX, obstacleY;
        cout << "Enter obstacle position (x y) for obstacle" << i + 1 << ": ";
        cin >> obstacleX >> obstacleY;
        obstacles.emplace_back(obstacleX, obstacleY);
    }
    
    // Create Rover Object
    MarsRover rover(x, y, direction, gridWidth, gridHeight, obstacles);

    // Moving the Rover
    cout << endl<< "Enter a list of moves (Enter Q as last move):" << endl;
    vector<char> moves;
    char move;
    while (cin >> move) {
        if (move == 'Q') {
            break;
        }
        if (move == 'M' || move == 'L' || move == 'R') {
            moves.push_back(move);
        } else {
            cout << "Invalid move";
            break;
        }
    }
    controlRover(rover, moves);

    return 0;
}
