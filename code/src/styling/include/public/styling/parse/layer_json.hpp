#pragma once

#include <nlohmann/json.hpp>

#include "styling/layers/layer.hpp"

namespace onyx::styling
{

void from_json(nlohmann::json const& j, layer& layer);

}