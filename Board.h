#pragma once
#include <vector>

class Board
{
private:
    int width, length;
    std::vector<std::vector<bool>> moleVisible;

public:
    Board(int w, int l);
    void Show(int x, int y);
    void Hide();
    bool IsMoleAt(int x, int y) const;
    int GetWidth() const { return width; }
    int GetLength() const { return length; }
};
