#pragma once

#include <styling/layers/layer.hpp>

namespace onyx::engine
{

class brain
{
public:

    static brain& ref();
    static void shutdown();

    void add_layer(styling::layer const& layer);

private:

    static brain* s_instance;
    brain();
    ~brain();

};

}