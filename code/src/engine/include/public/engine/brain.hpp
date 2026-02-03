#pragma once

#include <string>

#include <styling/layers/layer.hpp>

namespace mapitron::engine
{

class brain
{
public:

    static brain& ref();
    static void shutdown();

    void add_layer(styling::layer const& layer);

    std::string load_roboto();

    bool load_programs();

private:

    static brain* s_instance;
    brain();
    ~brain();

};

}