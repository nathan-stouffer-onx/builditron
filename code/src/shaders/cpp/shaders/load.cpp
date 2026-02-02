#include "shaders/load.hpp"

#include <fstream>

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(shaders_json);

namespace onyx::shaders
{

nlohmann::json load_components()
{
    auto fs = cmrc::shaders_json::get_filesystem();

    auto file = fs.open("assets/shaders/json/TiledPseudoRasters/Plinth.json");
    std::string str(file.begin(), file.end());
    return nlohmann::json::parse(str);
}

}