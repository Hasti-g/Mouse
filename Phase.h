#pragma once
#include "Stage.h"
#include <vector>

class Phase
{
private:
    std::vector<Stage> stages;
    int currentStage;
    bool phaseEnded;
    bool phaseWon;

public:
    Phase(bool isPhase2 = false);

    void Start();
    void ProcessHit(int x, int y);
    void Update();

    bool IsEnded() const;
    bool IsWon() const;
    int GetTotalScore() const;
};
