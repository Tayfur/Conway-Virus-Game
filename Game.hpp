#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "Board.hpp"

using namespace std;
namespace App
{
    class Game
    {
        public:
            
            Game(int W_WIDTH, int W_HEIGHT);
            ~Game();
            Uint32 FRAME_START;
            const int FRAME_DELAY= 1000/6;
            int frameTime;
            int HEIGHT;
            int WIDTH;
            void RUN();
            void EVENTS();
            void DRAW();
            void LINES();
            bool UPDATE = false;
            bool PROGRESS = true;
        
        private:
            unique_ptr<Board> G_BOARD;
            SDL_Window* W_WINDOWS;
            SDL_Renderer* W_RENDERER;
    };
}
