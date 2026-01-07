#pragma once

namespace onyx::styling
{

struct layer
{
    enum class types
    {
        fill,
        line,
        raster,
        symbol,
    };

    types type;
};

}