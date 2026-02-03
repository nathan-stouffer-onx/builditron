#pragma once

#include <string>
#include <vector>

namespace mapitron::shaders
{

struct pair
{
    std::string filename;
    std::string contents;
};

std::vector<pair> generate();

}