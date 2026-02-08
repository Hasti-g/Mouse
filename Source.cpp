#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <conio.h>
#include <fstream>

using namespace std;

/* ===== Utility ===== */
void ClearScreen() {
    system("cls");
}

void DrawBackground(int phase, int stage) {
    ClearScreen();
    cout << R"(
=========================================
        WHACK  THE  MOUSE
=========================================

             /\_/\ 
    __,---,__/ o o )
  /  _      ) =ø= /
 /  / \    /  .--'
(  (   )  /
 \  \_/  /
  '._   /
     """" 

-----------------------------------------
 Phase : )" << phase << R"(     Stage : )" << stage << R"(
-----------------------------------------

)";
}

/* ===== Board ===== */
class Board {
    int width, length;
    vector<vector<bool>> mole;
public:
    Board(int w, int l) : width(w), length(l), mole(l, vector<bool>(w, false)) {}

    void Hide() {
        for (int y = 0; y < length; y++)
            for (int x = 0; x < width; x++)
                mole[y][x] = false;
    }

    void Show(int x, int y) { mole[y][x] = true; }

    void Display() const {
        for (int y = 0; y < length; y++) {
            for (int x = 0; x < width; x++)
                cout << (mole[y][x] ? "[M] " : "[ ] ");
            cout << "\n";
        }
    }

    int CoordToNumber(int x, int y) const {
        y = length - 1 - y;
        return y * width + x + 1;
    }

    int W() const { return width; }
    int H() const { return length; }
};

/* ===== Stage ===== */
class Stage {
    Board board;
    int displays, requiredScore, moleTimeMs;
    int score = 0, combo = 0;
    bool penalizeWrong, bonusForCombo;

public:
    Stage(int w, int l, int d, int req, int t, bool pen, bool bonus)
        : board(w, l), displays(d), requiredScore(req),
        moleTimeMs(t), penalizeWrong(pen), bonusForCombo(bonus) {
    }

    bool Play(int phaseNum, int stageNum) {
        DrawBackground(phaseNum, stageNum);
        this_thread::sleep_for(chrono::seconds(2));

        mt19937 gen(random_device{}());
        uniform_int_distribution<> dx(0, board.W() - 1);
        uniform_int_distribution<> dy(0, board.H() - 1);

        for (int i = 0; i < displays; i++) {
            ClearScreen();
            board.Hide();

            int mx = dx(gen), my = dy(gen);
            board.Show(mx, my);

            cout << "Phase " << phaseNum << " | Stage " << stageNum << "\n";
            cout << "Display " << i + 1 << " / " << displays << "\n\n";

            board.Display();
            cout << "\nEnter cell (numpad): ";

            int correct = board.CoordToNumber(mx, my);
            int input = -1, passed = 0;

            while (passed < moleTimeMs) {
                if (_kbhit()) {
                    char c = _getch();
                    if (c >= '1' && c <= '9') {
                        input = c - '0';
                        cout << input << "\n";
                        break;
                    }
                }
                this_thread::sleep_for(chrono::milliseconds(50));
                passed += 50;
            }

            if (input == correct) {
                score += 10;
                if (bonusForCombo) {
                    combo++;
                    if (combo == 3) {
                        score += 20;
                        combo = 0;
                        cout << "BONUS +20\n";
                    }
                }
                cout << "Hit! +10\n";
            }
            else {
                cout << "Miss! Mole was at " << correct << "\n";
                combo = 0;
                if (penalizeWrong) score -= 10;
            }

            cout << "Score: " << score << "\n";
            this_thread::sleep_for(chrono::milliseconds(800));
        }

        cout << "\n--- End of Stage ---\n";
        cout << "Your score: " << score << "\n";
        cout << "Required score: " << requiredScore << "\n";

        if (!penalizeWrong && score < requiredScore) {
            cout << "Game Over!\n";
            return false;
        }

        cout << "Stage Passed!\n";
        return true;
    }

    int GetScore() const { return score; }
};

/* ===== Phase ===== */
class Phase {
    vector<Stage> stages;
    int phaseNumber;

public:
    Phase(int num) : phaseNumber(num) {
        if (num == 1) {
            stages.emplace_back(3, 1, 8, 50, 2000, false, false);
            stages.emplace_back(3, 2, 12, 100, 2000, false, false);
            stages.emplace_back(3, 3, 23, 200, 2000, false, false);
        }
        else {
            stages.emplace_back(3, 3, 8, 50, 2000, true, true);
            stages.emplace_back(3, 3, 14, 100, 1500, true, true);
            stages.emplace_back(3, 3, 25, 200, 1000, true, true);
        }
    }

    bool Play() {
        for (size_t i = 0; i < stages.size(); i++) {
            if (!stages[i].Play(phaseNumber, i + 1))
                return false;

            if (i + 1 < stages.size()) {
                cout << "\nNext stage in 2 seconds...\n";
                this_thread::sleep_for(chrono::seconds(2));
            }
        }
        return true;
    }

    int Score() const {
        int sum = 0;
        for (const auto& s : stages)
            sum += s.GetScore();
        return sum;
    }
};

/* ===== main ===== */
int main() {
    string name;
    cout << "Enter your name: ";
    getline(cin, name);

    int totalScore = 0;

    Phase phase1(1);
    if (!phase1.Play()) {
        totalScore = phase1.Score();
    }
    else {
        totalScore += phase1.Score();
        Phase phase2(2);
        phase2.Play();
        totalScore += phase2.Score();
    }

    ClearScreen();
    cout << "GAME OVER\n";
    cout << "Final Score: " << totalScore << "\n";

    ofstream file("leaderboard.txt", ios::app);
    file << name << " " << totalScore << "\n";
    file.close();

    cout << "Score saved.\n";
    return 0;
}
