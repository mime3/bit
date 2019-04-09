#pragma once
#ifndef __MINI__RANDOM_GENERATOR__
#define __MINI__RANDOM_GENERATOR__
#include <random>

namespace MINI
{
	enum class RANDOM
	{
		RAND_DEVICE,
		MERSENNE_TWISTER,
		MERSENNE_TWISTER64
	};
	template<typename T>
	class RandomGenerator
	{
		std::mt19937 mt;
		T _min;
		T _max;

	private:

	public:
		RandomGenerator(T min, T max);
		~RandomGenerator();
		
		T GetNumber();
	};
	template<typename T>
	inline T RandomGenerator<T>::GetNumber()
	{
		T ret = mt();
		return ret;
	}
}
#endif