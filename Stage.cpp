#include "Stage.h"
#include <random>

Stage::Stage(int boardWidth, int boardLength,
             int totalTime, int moleCount, int moleTime, int scoreReq,
             bool penalize, bool bonus)
    : board(boardWidth, boardLength),
      totalTimeSeconds(totalTime),
      totalMoles(moleCount),
      moleVisibleTime(moleTime),
      scoreRequired(scoreReq),
      penalizeMisses(penalize),
      enableBonus(bonus),
      currentScore(0),
      consecutiveHits(0),
      molesShown(0),
      stageEnded(false),
      stageWon(false),
      isMoleVisible(false) {}

void Stage::Start()
{
    currentScore = 0;
    consecutiveHits = 0;
    molesShown = 0;
    stageEnded = false;
    stageWon = false;
    isMoleVisible = false;

    board.Hide();
    stageStartTime = std::chrono::steady_clock::now();
    ShowNextMole();
}

void Stage::ShowNextMole()
{
    if (molesShown >= totalMoles)
        return;

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> disX(0, board.GetWidth() - 1);
    std::uniform_int_distribution<> disY(0, board.GetLength() - 1);

    int x = disX(gen);
    int y = disY(gen);

    board.Hide();
    board.Show(x, y);

    isMoleVisible = true;
    currentMoleShowTime = std::chrono::steady_clock::now();
    molesShown++;
}

void Stage::ProcessHit(int x, int y)
{
    if (!isMoleVisible || stageEnded)
        return;

    if (board.IsMoleAt(x, y))
    {
        currentScore += 10;

        if (enableBonus)
        {
            consecutiveHits++;
            if (consecutiveHits >= 3)
            {
                currentScore += 10;
                consecutiveHits = 0;
            }
        }
    }
    else
    {
        if (penalizeMisses)
            currentScore -= 10;

        consecutiveHits = 0;
    }

    board.Hide();
    isMoleVisible = false;

    if (molesShown < totalMoles)
        ShowNextMole();
}

void Stage::Update()
{
    if (stageEnded)
        return;

    auto now = std::chrono::steady_clock::now();
    int stagePassed =
        std::chrono::duration_cast<std::chrono::seconds>(now - stageStartTime).count();

    if (stagePassed >= totalTimeSeconds)
    {
        stageEnded = true;
        stageWon = (currentScore >= scoreRequired);
        board.Hide();
        return;
    }

    if (isMoleVisible)
    {
        int molePassed =
            std::chrono::duration_cast<std::chrono::seconds>(now - currentMoleShowTime).count();

        if (molePassed >= moleVisibleTime)
        {
            board.Hide();
            isMoleVisible = false;

            if (penalizeMisses)
                currentScore -= 10;

            consecutiveHits = 0;

            if (molesShown < totalMoles)
                ShowNextMole();
        }
    }
}

int Stage::GetScore() const { return currentScore; }
bool Stage::IsEnded() const { return stageEnded; }
bool Stage::IsWon() const { return stageWon; }
const Board& Stage::GetBoard() const { return board; }