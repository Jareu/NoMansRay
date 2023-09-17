#pragma once
#include <chrono>
#pragma warning(push, 0)
#pragma warning( disable : 4468 )
#include "SDL.h"
#pragma warning(pop)
#include "types.h"

#define TWOPI 6.2831853071f

inline bool is_active = false;
inline bool is_running = false;
inline bool is_fullscreen = true;
inline SDL_Renderer* renderer = nullptr;
inline SDL_Window* window = nullptr;

inline int WINDOW_WIDTH = 1920;
inline int WINDOW_HEIGHT = 1080;
inline int WINDOW_WIDTH_HALF = WINDOW_WIDTH/2;
inline int WINDOW_HEIGHT_HALF = WINDOW_HEIGHT/2;
inline auto WINDOW_SIZE = Vector2<int>{ WINDOW_WIDTH, WINDOW_HEIGHT };
inline auto WINDOW_SIZE_HALF = Vector2<int>{ WINDOW_WIDTH_HALF, WINDOW_HEIGHT_HALF };

inline float WINDOW_WIDTH_F = static_cast<float>(WINDOW_WIDTH);
inline float WINDOW_HEIGHT_F = static_cast<float>(WINDOW_HEIGHT);
inline float WINDOW_WIDTH_HALF_F = static_cast<float>(WINDOW_WIDTH_HALF);
inline float WINDOW_HEIGHT_HALF_F = static_cast<float>(WINDOW_HEIGHT_HALF);
inline auto WINDOW_SIZE_F = Vector2<float>{ WINDOW_WIDTH_F, WINDOW_HEIGHT_F };
inline auto WINDOW_SIZE_HALF_F = Vector2<float>{ WINDOW_WIDTH_HALF_F, WINDOW_HEIGHT_HALF_F };

inline SDL_Rect sim_rect = SDL_Rect{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
inline std::chrono::steady_clock::time_point last_frame_time{};
