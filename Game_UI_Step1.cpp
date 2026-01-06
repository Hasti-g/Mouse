// Game_UI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

class Stage
{
    public:
    int rows, cols;
    int molecol;
    int currentScore , scoreRequired;
    void display()
    {
        cout << "currentScore: " << currentScore << "\n";
        for (int i = 0; i < rows ; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (j == molecol)
                {
                    cout << "[M] ";
                }
                else
                {
                    cout << "[ ] ";
                }
            }
            cout << "\n";
        }
    }
};

class Game
{
   public:
       int currentPhase , currentStage , totalPhases, stagesPerPhase , currentScore;
       vector<Stage> stages;

       Game (int totalPhases_, int stagesPerPhase_)
       {
           totalPhases = totalPhases_;
           stagesPerPhase = stagesPerPhase_;
           currentPhase = 1;
           currentStage = 0;
           currentScore = 0;
           for (int i = 0; i < stagesPerPhase; i++)
           {
               int stageNumber = i + 1;
               Stage s;
               s.rows = stageNumber;
               s.cols = 3;  
               s.molecol = 0;   
               s.currentScore = 0;
               s.scoreRequired = 50; 
               stages.push_back(s);
           }
       }
       void  CurrentStage()
       {
           if (currentStage < stages.size())
           {
               stages[currentStage].display();
           }
           else
           {
               cout << "No Stage available!\n";
           }
       }
       void goToNextStage()
       {
           currentStage++;
           if (currentStage >= stagesPerPhase)
           {
               currentStage = 0;
               currentPhase = currentPhase + 1;
               if (currentPhase > totalPhases)
               {
                   cout << "Game Finished" << "\n";
               }
               if (currentPhase <= totalPhases)
               {
                   stages.clear();
                   for (int i = 0; i < stagesPerPhase; i++)
                   {
                       int stageNumber = i + 1;
                       Stage s;
                       s.rows = stageNumber;
                       s.cols = 3;
                       s.molecol = 0;
                       s.currentScore = 0;
                       s.scoreRequired = 5;
                       stages.push_back(s);
                   }
               }
           }
       }
};

int main()
{
    int phases = 2;
    int stages = 3;
    Game g(phases, stages);
    while (g.currentPhase <= 2)
    {
        cout << "\n ** CurrentPhase: " << g.currentPhase << " **\n";
        cout << "\n ** CurrentStage: " << g.currentStage << " **\n";
        g.CurrentStage();
        int x;
        do {
            cout << "Enter 10 to go to the next stage: ";
            cin >> x;
        } while (x != 10);
        g.goToNextStage();
    }
    cout << "Game Finished";
    return 0;
}

