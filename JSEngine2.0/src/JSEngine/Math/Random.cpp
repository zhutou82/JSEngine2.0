#include "PCH.h"
#include "Random.h"

namespace JSEngine
{
    std::mt19937 Random::s_Engine;
    std::uniform_int_distribution<std::mt19937::result_type> Random::s_Range;

}

