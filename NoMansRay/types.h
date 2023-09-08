#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <typeinfo>
#include <stdint.h>
#include <math.h>
#include <cstdint>

#include "Vector2.h"
#include "Vector3.h"

typedef float decimal; // so that floating point precision can be changed easily
constexpr decimal ZERO_DECIMAL = static_cast<decimal>(0.0);
constexpr decimal ONE_DECIMAL = static_cast<decimal>(1.0);

enum RENDER_RESULT {
	RENDER_SUCCESS = 0,
	RENDER_FAILED = 1
};

constexpr uint16_t SPRING_K = 2000;
constexpr uint16_t SPRING_D = 20;

class VectorSpherical {
public:
	float theta = 0.f;
	float phi = 0.f;

	VectorSpherical() = default;

	VectorSpherical(float theta, float phi) : theta{ theta }, phi{ phi } {};

	VectorSpherical operator+(const VectorSpherical& other) {
		VectorSpherical sum = VectorSpherical(this->theta + other.theta, this->phi + other.phi);
		return sum;
	}

	VectorSpherical operator-(const VectorSpherical& other) {
		VectorSpherical sum = VectorSpherical(this->theta - other.theta, this->phi - other.phi);
		return sum;
	}
};

template <typename T>
class Range {
public:
	T min = 0;
	T max = 0;

	Range() = default;
	Range(T min, T max) : min{ min }, max{ max } {};
};

struct RGB {
	uint8_t R = 0;
	uint8_t G = 0;
	uint8_t B = 0;
};

struct RGBA {
	uint8_t R = 0;
	uint8_t G = 0;
	uint8_t B = 0;
	uint8_t A = 0;
};

struct HSL {
	float H = 0;
	float S = 0;
	float L = 0;
};

enum class eFontSize {
	SMALL,
	MEDIUM,
	LARGE,
	TITLE
};

typedef struct _EndPointRef {
	int	ref;
	Vector2<float> pt;
} EndPoint;

typedef struct _Spring
{
	EndPoint end1;
	EndPoint end2;
	float k = SPRING_K;
	float damping = SPRING_D;
	float nominal_length{ 0.f };
} Spring;