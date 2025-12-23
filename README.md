**Whack-a-mole game(C++)**
  project description:
This projrct is an implementation of the classic(and physical) whack-a-mole which now is written in C++.
The game is developed as a team project with the goal of practicing basic programming concepts, teamwork, using GitHub, and the base of game logic.
  **Game overview:**
in this game:
* A mole appears randomly in different places(in a matrix).
* The player must react quickly and catch that appeared mole befor it hides again.
* Each successful hit increases the score.
* the game runs for a limited time and has different rounds which require specified score.
  **Technologies used:**
*  language: C++
*  Compiler: GCC/MinGW
*  Platform: console-based application
*  Version control: Git and GitHub
  **Team members:**
Bahar Masoumi
Hasti Golestani
  **Project Structure:**
``` 
Whack-a-Mole/
│
├── main.cpp        // Main game loop
├── game.cpp        // Game logic
├── game.h          // Function declarations
├── README.md       // Project documentation
```
(Structure may evolve during development)
  **How to Compile and Run:**
Using GCC:
```
Bash
g++ main.cpp game.cpp -o whackamole
./whackamole
```
On Windows (MinGW):
```
Bash
g++ main.cpp game.cpp -o whackamole.exe
whackamole.exe
```
  **Note:**
This project is for educational purposes.
Future improvements may include better UI, difficulty levels, and timer-based gameplay.
📄 License
This project is intended for academic use only.
