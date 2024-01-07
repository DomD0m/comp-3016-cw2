#include "Random.h"

std::mt19937 randomRain::s_Randomlog;
std::uniform_int_distribution<std::mt19937::result_type> randomRain::s_Distribution;