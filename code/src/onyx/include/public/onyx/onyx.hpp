#pragma once

#include <string>

namespace mapitron
{

void shutdown();

int add(int lhs, int rhs);

void add_layer(std::string const& str);

std::string load_roboto();

bool load_programs();

}