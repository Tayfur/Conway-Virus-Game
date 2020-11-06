#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <time.h>

using  namespace std;
namespace App
{
template <typename T1, typename T2>
struct Location{T1 first ; T2 second;};
    class Board
    {
        public:
            Board(Location<int, int> ScreenSize);
            void UPDATE();
            void Clear();
            enum Cell {Dead,Alive,Virus};
            constexpr static  int x_SIZE = 20;
            constexpr static  int y_SIZE = 20;
            Location<int, int> GET_SIZE() { return CELL_SIZE; }
            void CLICKED_CELL(Location<int, int> CURRENT_MAUSE_LOCATION);
            Cell READ_CELL(int Index) { return GRID[Index]; }
        private:
            int COUNT_NEIGHBOORS(Location<int, int> GRID_CELL);
            int Virus_COUNT_NEIGHBOORS(Location<int, int> GRID_CELL);

            vector<Cell> GRID;
            const Location<int, int> CELL_SIZE;
    };
}
