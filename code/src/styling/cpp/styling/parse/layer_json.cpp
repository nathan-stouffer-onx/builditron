#include "styling/parse/layer_json.hpp"

namespace mapitron::styling
{

void from_json(nlohmann::json const& j, layer& layer)
{
    std::string type = j["type"];
    if (type == "fill") { layer.type = layer::types::fill; }
    if (type == "line") { layer.type = layer::types::line; }
    if (type == "raster") { layer.type = layer::types::raster; }
    if (type == "symbol") { layer.type = layer::types::symbol; }
}

}