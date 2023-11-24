#pragma once
#include <chrono>
#include <vector>

#pragma warning(push, 0)
#pragma warning( disable : 4468 )
#include "SDL.h"
#pragma warning(pop)
#include "Vector2.h"

#define TWOPI 6.2831853071f

typedef float decimal; // so that floating point precision can be changed easily
constexpr decimal ZERO_DECIMAL = static_cast<decimal>(0.0);
constexpr decimal ONE_DECIMAL = static_cast<decimal>(1.0);

inline bool is_active = false;
inline bool is_running = false;
inline bool is_fullscreen = true;
inline SDL_Renderer* renderer = nullptr;
inline SDL_Window* window = nullptr;
inline int global_volume = 0;

typedef std::pair<uint32_t, uint32_t> Line; // pair of vertex IDs 
typedef std::vector<Line> LineVector;
typedef std::vector<Vector2<decimal>> VertexVector;

inline constexpr size_t BOX2D_MAX_VERTICES_IN_POLYGON = 8;
inline constexpr float PIXELS_PER_METER = 50.f;
inline constexpr float GRAVITY = 9.814f;

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
