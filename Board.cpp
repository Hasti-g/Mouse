#include "Board.h"

Board::Board(int w, int l)
    : width(w), length(l), moleVisible(l, std::vector<bool>(w, false)) {
}

void Board::Show(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < length)
        moleVisible[y][x] = true;
}

void Board::Hide()
{
    for (int y = 0; y < length; y++)
        for (int x = 0; x < width; x++)
            moleVisible[y][x] = false;
}

bool Board::IsMoleAt(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= length)
        return false;
    return moleVisible[y][x];
}
