#pragma once

namespace mapitron::styling
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