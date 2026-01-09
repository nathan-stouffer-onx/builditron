#pragma once

#include <nlohmann/json.hpp>

namespace onyx::shaders
{

nlohmann::json load_components();

bool load_shaders();

}
