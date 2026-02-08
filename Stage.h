#pragma once
#include "Board.h"
#include <chrono>

class Stage
{
private:
    Board board;

    const int totalTimeSeconds;
    const int totalMoles;
    const int moleVisibleTime;
    const int scoreRequired;
    const bool penalizeMisses;
    const bool enableBonus;

    int currentScore;
    int consecutiveHits;
    int molesShown;

    bool stageEnded;
    bool stageWon;
    bool isMoleVisible;

    std::chrono::steady_clock::time_point stageStartTime;
    std::chrono::steady_clock::time_point currentMoleShowTime;

    void ShowNextMole();

public:
    Stage(int boardWidth, int boardLength,
        int totalTime, int moleCount, int moleTime, int scoreReq,
        bool penalize = false, bool bonus = false);

    void Start();
    void ProcessHit(int x, int y);
    void Update();

    int GetScore() const;
    bool IsEnded() const;
    bool IsWon() const;
    const Board& GetBoard() const;
};
