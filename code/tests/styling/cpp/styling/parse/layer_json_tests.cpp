#include <gtest/gtest.h>

#include <styling/parse/layer_json.hpp>

namespace mapitron::styling
{

TEST(styling, parse_layer)
{
    layer l = nlohmann::json::parse(R"({ "type": "line" })");
    ASSERT_EQ(layer::types::line, l.type) << "failed to parse line layer";
}

}