#include <gtest/gtest.h>

#include <engine/symbols/fonts/load.hpp>

namespace mapitron::engine::symbols
{

TEST(symbols, load_roboto)
{
    ASSERT_EQ("I am roboto", symbols::load_roboto()) << "failed to load roboto";
}

}