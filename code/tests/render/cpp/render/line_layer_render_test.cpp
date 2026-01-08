#include <chrono>

#include <gtest/gtest.h>

#include <onyx/onyx.hpp>

namespace onyx
{

TEST(render, line_layer)
{
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

}