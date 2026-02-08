#include <iostream>
#include <fstream>
#include <thread>
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
    }
    else {
        std::cout << "new game started.\n";
    }

    Phase phase(currentPhase == 2);

    for (int i = 0; i < currentStage; i++) {
    }
    phase.Start();

    SaveGame(currentPhase, currentStage + 1);

    return 0;
}
