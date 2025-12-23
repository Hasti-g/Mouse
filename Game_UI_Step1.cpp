// Game_UI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
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
                    cout << "[M]";
                }
                else
                {
                    cout << "[ ]";
                }
            }
            cout << "\n";
        }
    }
};
int main()
{
    
}

