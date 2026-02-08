#include <iostream>
#include <thread>
#include "Phase.h"

int main()
{
    Phase phase(false);
    phase.Start();

    while (!phase.IsEnded())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        phase.Update();

        phase.ProcessHit(0, 0);
    }

    std::cout << "Game Over!\n";
    std::cout << "Total Score: " << phase.GetTotalScore() << "\n";

    if (phase.IsWon())
        std::cout << "Phase Completed!\n";
    else
        std::cout << "You Lost the Phase.\n";

    return 0;
}