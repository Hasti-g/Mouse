#include "Phase.h"

Phase::Phase(bool isPhase2)
    : currentStage(0), phaseEnded(false), phaseWon(false)
{
    if (isPhase2)
    {
        stages.emplace_back(3, 3, 25, 10, 2, 50, true, true);
        stages.emplace_back(3, 3, 30, 15, 1, 100, true, true);
        stages.emplace_back(3, 3, 35, 20, 1, 150, true, true);
    }
    else
    {
        stages.emplace_back(3, 1, 20, 8, 2, 50, false, false);
        stages.emplace_back(3, 2, 20, 12, 1, 100, false, false);
        stages.emplace_back(3, 3, 25, 20, 1, 150, false, false);
    }
}

void Phase::Start()
{
    currentStage = 0;
    phaseEnded = false;
    phaseWon = false;
    stages[0].Start();
}

void Phase::ProcessHit(int x, int y)
{
    if (!phaseEnded)
        stages[currentStage].ProcessHit(x, y);
}

void Phase::Update()
{
    if (phaseEnded)
        return;

    stages[currentStage].Update();

    if (stages[currentStage].IsEnded())
    {
        if (stages[currentStage].IsWon())
        {
            currentStage++;
            if (currentStage >= (int)stages.size())
            {
                phaseEnded = true;
                phaseWon = true;
            }
            else
            {
                stages[currentStage].Start();
            }
        }
        else
        {
            phaseEnded = true;
            phaseWon = false;
        }
    }
}

bool Phase::IsEnded() const { return phaseEnded; }
bool Phase::IsWon() const { return phaseWon; }

int Phase::GetTotalScore() const
{
    int total = 0;
    for (const auto& stage : stages)
        total += stage.GetScore();
    return total;
}