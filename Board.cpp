#include "Board.hpp"
#include <iostream>

#include <cmath>
using namespace std;
App::Board::Board(Location<int, int> ScreenSize)
    : CELL_SIZE{ScreenSize.first / x_SIZE, ScreenSize.second / y_SIZE}
{
    int GridSize = x_SIZE * y_SIZE;
    vector<Cell> MATRIX(GridSize, Cell::Dead);
    GRID = MATRIX;

}
void App::Board::UPDATE()
{
    vector<Cell> MATRIX(GRID);
    for (int i = 0; i < Board::y_SIZE; ++i)
    {
        for (int j = 0; j < x_SIZE; ++j)
        {
            if (GRID[j + x_SIZE * i] == Cell::Alive)
            {
                if (COUNT_NEIGHBOORS({j,i}) < 2 || COUNT_NEIGHBOORS({j, i}) > 3)
                {
                    MATRIX[j + x_SIZE * i] = Cell::Dead;
                }
                if (COUNT_NEIGHBOORS({j, i}) == 7)
                {
                    MATRIX[j + x_SIZE * i] = Cell::Virus;
                  

                }
                if (Virus_COUNT_NEIGHBOORS({j, i}) == 1)
                {
                    MATRIX[j + x_SIZE * i] = Cell::Virus;
                    
                }
            }
            if (GRID[j + x_SIZE * i] == Cell::Dead)
            {
                if (Virus_COUNT_NEIGHBOORS({j, i}) == 2)
                {
                    MATRIX[j + x_SIZE * i] = Cell::Dead;
                }
                if (COUNT_NEIGHBOORS({j, i}) == 3)
                {
                    MATRIX[j + x_SIZE * i] = Cell::Alive;
                }
            }
            if (GRID[j + x_SIZE * i] == Cell::Virus)
            {
                if (Virus_COUNT_NEIGHBOORS({j, i}) == 2)
                {
                    MATRIX[j + x_SIZE * i] = Cell::Alive;
                }
                if (Virus_COUNT_NEIGHBOORS({j, i}) < 2)
                {
                    MATRIX[j + x_SIZE * i] = Cell::Alive;
                }
                int random= rand() % 4+1;
                if (random==1) {
                    MATRIX[j + x_SIZE * i] = Cell::Dead;
                }
                else {
                    MATRIX[j + x_SIZE * i] = Cell::Alive;

                }
            }

        }
    }

    GRID = MATRIX;

}

void App::Board::Clear()
{
    fill(GRID.begin(), GRID.end(), Cell::Dead);
}

int App::Board::COUNT_NEIGHBOORS(Location<int, int> GRID_CELL)
{
    int count = 0;
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j <2; ++j)
        {
            int absoluteX = GRID_CELL.first + i;
            int absoluteY = GRID_CELL.second + j;
            if (absoluteX == -1 || absoluteX == x_SIZE ||
                absoluteY == -1 || absoluteY == y_SIZE ||
               (i == 0 && j == 0))
            {
                continue;
            }

            if (GRID[absoluteX + x_SIZE * absoluteY] == Cell::Alive)
            {
                ++count;
            }
        }
    }

    return count;
}
    int App::Board::Virus_COUNT_NEIGHBOORS(Location<int, int> GRID_CELL)
    {
        int count = 0;
        for (int i = -1; i < 2; ++i)
        {
            for (int j = -1; j <2; ++j)
            {
                int absoluteX = GRID_CELL.first + i;
                int absoluteY = GRID_CELL.second + j;
                if (absoluteX == -1 || absoluteX == x_SIZE ||
                    absoluteY == -1 || absoluteY == y_SIZE ||
                   (i == 0 && j == 0))
                {
                    continue;
                }

                if (GRID[absoluteX + x_SIZE * absoluteY] == Cell::Virus)
                {
                    ++count;

                }
            }
        }

        return count;
    }
void App::Board::CLICKED_CELL(Location<int, int> Locations)
{
    int ClickedCell = (floor(Locations.first / CELL_SIZE.first)) + x_SIZE * (floor(Locations.second / CELL_SIZE.second));
    GRID[ClickedCell] = GRID[ClickedCell] == Cell::Dead ? Cell::Alive : Cell::Dead;
}


