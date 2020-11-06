#include "Game.hpp"
using namespace std;

App::Game::Game(int W_WIDTH, int W_HEIGHT)
    : WIDTH{W_WIDTH}, HEIGHT{W_HEIGHT}
{
    SDL_assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    W_WINDOWS = SDL_CreateWindow(
            "Tayfur Kaya Game of Life ",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH,
            HEIGHT,
            SDL_WINDOW_SHOWN
            );

    SDL_assert(W_WINDOWS != NULL);

    if (!G_BOARD)
    {
        Location<int, int> ScreenSize = {WIDTH, HEIGHT};
        G_BOARD = make_unique<Board>(ScreenSize);
    }
    SDL_assert(G_BOARD != nullptr);

    W_RENDERER = SDL_CreateRenderer(W_WINDOWS, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_assert(W_RENDERER != NULL);

    SDL_RenderClear(W_RENDERER);
    LINES();
}

App::Game::~Game()
{
    SDL_DestroyWindow(W_WINDOWS);
    SDL_DestroyRenderer(W_RENDERER);
    W_WINDOWS = NULL;
    W_RENDERER = NULL;

    SDL_Quit();
}
void App::Game::RUN()
{
    while (PROGRESS)
    {
        EVENTS();
        if (UPDATE)
        {
            G_BOARD->UPDATE();
        }
        DRAW();
        FRAME_START=SDL_GetTicks();
        frameTime = SDL_GetTicks() - FRAME_START;
        if (FRAME_DELAY>frameTime) {
            SDL_Delay(FRAME_DELAY-frameTime);
        }
    }
}
void App::Game::EVENTS()
{
    SDL_Event Event;
    while(SDL_PollEvent(&Event))
    {
        switch(Event.type)
        {
            case SDL_QUIT:
                PROGRESS = false;
                break;

            case SDL_KEYDOWN:
                if (Event.key.keysym.sym == SDLK_SPACE)
                {
                    UPDATE = UPDATE ? false : true;
                    LINES();
                }
                else if (Event.key.keysym.sym == SDLK_c)
                {
                    G_BOARD->Clear();
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (!UPDATE)
                {
                    if (Event.button.button == SDL_BUTTON_LEFT)
                    {
                        G_BOARD->CLICKED_CELL({Event.button.x, Event.button.y});
                    }
                }
                break;

        }
    }
}

void App::Game::DRAW()
{
    SDL_RenderClear(W_RENDERER);

    for (int i = 0; i < Board::y_SIZE; ++i)
    {
        for (int j = 0; j < Board::x_SIZE; ++j)
        {
            if (G_BOARD->READ_CELL(j + Board::x_SIZE * i) == Board::Cell::Alive)
            {
                SDL_SetRenderDrawColor(W_RENDERER, 255, 255, 255, 255);
            }
            if (G_BOARD->READ_CELL(j + Board::x_SIZE * i) == Board::Cell::Dead)
            {
                SDL_SetRenderDrawColor(W_RENDERER, 0, 0, 0, 255);
            }
            if (G_BOARD->READ_CELL(j + Board::x_SIZE * i) == Board::Cell::Virus)
            {
                SDL_SetRenderDrawColor(W_RENDERER, 255, 0, 0, 0);

            }
            SDL_Rect rect;
            rect.x = G_BOARD->GET_SIZE().first * j;
            rect.y = G_BOARD->GET_SIZE().second * i;
            rect.w = G_BOARD->GET_SIZE().first;
            rect.h = G_BOARD->GET_SIZE().second;

            SDL_RenderFillRect(W_RENDERER, &rect);
            }
    }
   
        LINES();
    
    SDL_RenderPresent(W_RENDERER);
}

void App::Game::LINES()
{
    SDL_SetRenderDrawColor(W_RENDERER, 255, 255, 255, 255);
    for (int i = 0; i < Board::y_SIZE; ++i)
    {
        if (i != 0)
        {
            SDL_RenderDrawLine(
                    W_RENDERER,
                    0,
                    G_BOARD->GET_SIZE().second * i,
                    G_BOARD->GET_SIZE().first * Board::x_SIZE,
                    G_BOARD->GET_SIZE().second * i
                    );
        }
    }

    for (int i = 0; i < Board::x_SIZE; ++i)
    {
        if (i != 0)
        {
            SDL_RenderDrawLine(
                    W_RENDERER,
                    G_BOARD->GET_SIZE().first * i,
                    0,
                    G_BOARD->GET_SIZE().first * i,
                    G_BOARD->GET_SIZE().second * Board::y_SIZE
                    );
        }
    }

    SDL_RenderPresent(W_RENDERER);
    SDL_SetRenderDrawColor(W_RENDERER, 0, 0, 0, 255);
}

