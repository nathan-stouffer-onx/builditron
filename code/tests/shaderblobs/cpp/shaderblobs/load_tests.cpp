#include <gtest/gtest.h>

#include <shaderblobs/load.hpp>

namespace mapitron::shaderblobs
{

TEST(shaderblobs, load)
{
    std::string plinth_fragment = shaderblobs::load("Plinth.fs.sc");
    ASSERT_EQ("$input world_position, color", plinth_fragment) << "failed to load Plinth.fs.sc";
}

}