#pragma once

#include <FastNoise\FastNoise.h>
#include <FastSIMD\FastSIMD.h>

class NoiseTest
{
public:
	NoiseTest() = default;
	bool test()
	{
		constexpr float expected_value = 0.237569F;
		constexpr float epsilon = 0.000001F;
		FastNoise::SmartNode<FastNoise::Simplex> noise = FastNoise::New<FastNoise::Simplex>(FastSIMD::eLevel::Level_Null);
		float noise_val = noise->GenSingle2D(0.5, 0.5, 100);
		bool test_result = std::abs(noise_val - expected_value) < epsilon;
		std::cout << "NoiseTest " << (test_result ? "PASSED" : "FAILED") << " expected " << expected_value << " got " << noise_val << std::endl;
		return test_result;
	}
};