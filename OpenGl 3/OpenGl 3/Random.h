#pragma once
#include<random>
//Random header class
class randomRain
{
public:
	static void init() 
	{
		//makes a pc seed to get random numbers from
		s_Randomlog.seed(std::random_device()());
	}
	static float randomnum()
	{
		//returns ur random number between the float.
		return (float)s_Distribution(s_Randomlog) / (float)std::numeric_limits<uint32_t>::max();
	}
private:
	static std::mt19937 s_Randomlog;
	static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};