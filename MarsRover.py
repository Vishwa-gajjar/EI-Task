# Define the Command Pattern
class Command:
    def execute(self, rover):
        pass

class MoveCommand(Command):
    def execute(self, rover):
        rover.move()

class TurnLeftCommand(Command):
    def execute(self, rover):
        rover.turn_left()

class TurnRightCommand(Command):
    def execute(self, rover):
        rover.turn_right()

# Define the MarsRover class
class MarsRover:
    def __init__(self, x, y, direction, grid, obstacles):
        self.x = x
        self.y = y
        self.direction = direction
        self.grid = grid
        self.obstacles = obstacles

    def move(self):
        # Calculate the next position based on the current direction
        next_x, next_y = self.calculate_next_position()

        # Check if the next position is within the grid
        if self.is_valid_position(next_x, next_y):
            # Check if the next position is not an obstacle
            if not self.is_obstacle(next_x, next_y):
                self.x = next_x
                self.y = next_y

    def turn_left(self):
        # Implement left turn logic
        if self.direction == 'N':
            self.direction = 'W'
        elif self.direction == 'W':
            self.direction = 'S'
        elif self.direction == 'S':
            self.direction = 'E'
        elif self.direction == 'E':
            self.direction = 'N'

    def turn_right(self):
        # Implement right turn logic
        if self.direction == 'N':
            self.direction = 'E'
        elif self.direction == 'E':
            self.direction = 'S'
        elif self.direction == 'S':
            self.direction = 'W'
        elif self.direction == 'W':
            self.direction = 'N'

    def is_valid_position(self, x, y):
        # Check if the position is within the grid
        return 0 <= x < self.grid.width and 0 <= y < self.grid.height

    def is_obstacle(self, x, y):
        # Check if the position contains an obstacle
        return (x, y) in [(obstacle.x, obstacle.y) for obstacle in self.obstacles]

    def calculate_next_position(self):
        # Calculate the next position based on the current direction
        next_x, next_y = self.x, self.y
        if self.direction == 'N':
            next_y += 1
        elif self.direction == 'S':
            next_y -= 1
        elif self.direction == 'E':
            next_x += 1
        elif self.direction == 'W':
            next_x -= 1
        return next_x, next_y

    def send_status_report(self):
        # Generate and return a status report
        obstacle_detected = "Obstacle detected." if self.is_obstacle(self.x, self.y) else "No obstacles detected."
        return f"Rover is at ({self.x}, {self.y}) facing {self.direction}. {obstacle_detected}"

# Define the Grid and Obstacles using Composite Pattern
class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height

class Obstacle:
    def __init__(self, x, y):
        self.x = x
        self.y = y

# Function to take user input and control the rover interactively
def control_rover(rover):
    while True:
        print("Rover Commands:")
        print("1. Move (M)")
        print("2. Turn Left (L)")
        print("3. Turn Right (R)")
        print("4. Quit (Q)")
        
        user_input = input("Enter a command: ").upper()
        
        if user_input == 'M':
            move_command = MoveCommand()
            move_command.execute(rover)
        elif user_input == 'L':
            turn_left_command = TurnLeftCommand()
            turn_left_command.execute(rover)
        elif user_input == 'R':
            turn_right_command = TurnRightCommand()
            turn_right_command.execute(rover)
        elif user_input == 'Q':
            break
        
        final_position = (rover.x, rover.y, rover.direction)
        status_report = rover.send_status_report()
        print(f"Current Position: {final_position}")
        print(status_report)

# Client code
if __name__ == "__main__":
    grid = Grid(10, 10)
    starting_position = (0, 0)
    starting_direction = 'N'
    obstacles = [Obstacle(2, 2), Obstacle(3, 5)]

    rover = MarsRover(starting_position[0], starting_position[1], starting_direction, grid, obstacles)

    control_rover(rover)
