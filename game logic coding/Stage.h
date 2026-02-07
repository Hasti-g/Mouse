#pragma once
#include"Board.h"
#include<chrono>

class GameStage
{
private:
	Board board;
	const int totalTimeSeconds;
	const int totalMoles;
	const int moleVisibleTime;
	const int scoreRequired;
	const bool penaliseMisses;
	const bool enableBonus;

	int currentScore;
	int consectiveHits;
	int molesShown;
	bool stageEnd;
	bool stageWon;

	std::chrono::steady_clock::time_point stageStartTime;
	std::chrono::steady_clock::time_point currentMoleHideTime;
	bool isMoleVisible;

	void ShowNextMole();

public:
	GameStage(int boardWidth, int BoardLength,
		int totalTime, int moleCount, int moleTime, int scoreReq,
		bool penalize = false, bool bonus = false);

	void Start();
	void ProccessHit(int x, int y, bool isCorrect);
	void Update();
	int getScore() const;
	bool IsEnded() const;
	bool IsWon() const;
	const Board& GetBorad() const;
};
