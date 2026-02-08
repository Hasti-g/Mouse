#include <iostream>
#include <fstream>
#include "Phase.h"

void SaveGame(int phase, int stage) {
    std::ofstream file("save.txt");
    file << phase << "\n" << stage << "\n";
    file.close();
}

bool LoadGame(int& phase, int& stage) {
    std::ifstream file("save.txt");
    if (file.is_open()) {
        file >> phase >> stage;
        file.close();
        return true;
    }
    return false;
}

int main() {
    int currentPhase = 1; 
    int currentStage = 0; 

    if (LoadGame(currentPhase, currentStage)) {
        std::cout << "from stage " << (currentStage + 1)
                  << " phase " << currentPhase << " continued.\n";
    } else {
        std::cout << "new game started.\n";
    }

    Phase phase(currentPhase == 2);
    
    phase.Start();

    while (!phase.IsEnded()) {
        int x, y;
        std::cout << "\nEnter mole position (x y): ";
        std::cin >> x >> y;

        phase.ProcessHit(x, y);
        phase.Update();

        std::cout << "Current total score: " << phase.GetTotalScore() << "\n";
    }

    std::cout << "\n=== Game Over ===\n";
    std::cout << "Final score: " << phase.GetTotalScore() << "\n";

    SaveGame(currentPhase, currentStage + 1);

    return 0;
}

