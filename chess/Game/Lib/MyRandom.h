#pragma once
#include <random>
#include "MyVector2.h"

inline unsigned sed = static_cast<unsigned>(std::time(nullptr));
inline std::mt19937 gen(sed); // Mersenne Twister 乱数生成器をシード値で初期化

inline int RandomInt(int max, int min) {
	///最小値、最大値
	std::uniform_int_distribution<int> randomNum(min, max);
	int rand_ = static_cast<int>(randomNum(gen));
	return rand_;
}

inline void Random(Vec2f& num, int maxNum, int minNum) {
	///最小値、最大値
	std::uniform_int_distribution<int> shakeX(minNum, maxNum);
	std::uniform_int_distribution<int> shakeY(minNum, maxNum);

	num.x = static_cast<float>(shakeX(gen));
	num.y = static_cast<float>(shakeY(gen));
}

inline Vec2f Random(float maxNum, float minNum) {
	Vec2f result;

	// 最小値、最大値
	std::uniform_real_distribution<float> shakeX(minNum, maxNum);
	std::uniform_real_distribution<float> shakeY(minNum, maxNum);

	result.x = shakeX(gen);
	result.y = shakeY(gen);

	return result;
}

inline float Randomf(float maxNum, float minNum) {
	float result;

	///最小値、最大値
	std::uniform_real_distribution<float> shake(minNum, maxNum);

	result = static_cast<float>(shake(gen));

	return result;
}