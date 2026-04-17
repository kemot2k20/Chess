# CLASS DESCRIPTIONS

### `Game`
This class is responsible for managing the gameplay flow and communicating with the user.
The `Game::gameLoop()` method is the main game loop, which uses the UI to display the current state of the board.

### `GameHelper'
`GameHelper` contains a set of utility methods used by the `Game` class. 
Examples include: checking for checkmate or stalemate, returning all possible moves in a given position, and validating the legality of a move.

### `Player`
Contains player attributes such as: player name, a boolean indicating if the player is an AI, and the color of the player's pieces.

### `UI`
This class handles rendering the current chess position to the console and reading user input for moves in UCI format.

---

# ADDITIONAL INFORMATION

- **Making a move:** Enter your move in UCI format (e.g., `e2e4`).
- **Exiting the game:** Type `quit` in the move input prompt to exit.
- **Game Modes:** You can change the game mode (e.g., Player vs Player, Player vs AI) in the `main.cpp` file.
- **AI Difficulty:** There are 5 bot difficulty levels available, corresponding to the search depth of the algorithm. Lower depths result in faster, but less accurate play.
