#include "shaders/load.hpp"

#include <fstream>

namespace onyx::shaders
{

nlohmann::json load()
{
    nlohmann::json j;
    std::ifstream file("assets/shaders/json/TiledPseudoRasters/Plinth.json");
    file >> j;
    return j;
}

}
