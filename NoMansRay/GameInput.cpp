#include "GameInput.h"

bool GameInput::IsKeyPressedImpl(int keycode)
{
    SDL_PumpEvents();
    keyboard = SDL_GetKeyState(NULL);
}

void GameInput::update()
{

}