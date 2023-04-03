#pragma once
#include <chrono>

#define TWOPI 6.2831853071f

inline bool is_active = false;
inline bool is_running = false;
inline bool is_fullscreen = true;
inline SDL_Renderer* renderer = nullptr;
inline SDL_Window* window = nullptr;
inline int WINDOW_WIDTH = 1920;
inline int WINDOW_HEIGHT = 1080;
inline SDL_Rect sim_rect = SDL_Rect{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
inline std::chrono::steady_clock::time_point last_frame_time{};
