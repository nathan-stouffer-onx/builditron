#include "onyx/onyx.hpp"

#include <styling/parse/layer_json.hpp>

#include <lucid/scalar.hpp>

#include <engine/brain.hpp>

namespace onyx
{

    void shutdown()
    {
        engine::brain::shutdown();
    }

    int add(int lhs, int rhs)
    {
        return lucid::add(lhs, rhs);
    }

    void add_layer(std::string const& str)
    {
        styling::layer layer = nlohmann::json::parse(str);
        engine::brain::ref().add_layer(layer);
    }

    std::string load_roboto()
    {
        return engine::brain::ref().load_roboto();
    }

}