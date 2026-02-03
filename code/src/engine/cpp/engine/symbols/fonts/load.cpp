#include "engine/symbols/fonts/load.hpp"

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(engine_assets);

namespace mapitron::engine::symbols
{

std::string load_roboto()
{
    auto fs = cmrc::engine_assets::get_filesystem();
    auto file = fs.open("assets/fonts/roboto.ttf");
    return std::string(file.begin(), file.end());
}

}