#include <vector>

#include <gtest/gtest.h>

#include <onyx/onyx.hpp>

namespace onyx
{

TEST(onyx, add)
{
    ASSERT_EQ(0, onyx::add(0, 0)) << "failed 0 + 0";
    ASSERT_EQ(6, onyx::add(5, 1)) << "failed 5 + 1";
    ASSERT_EQ(6, onyx::add(1, 5)) << "failed 1 + 5";
}

TEST(onyx, add_layer)
{
    onyx::add_layer(R"({ "type": "line" })");
}

TEST(onyx, load_roboto)
{
    ASSERT_EQ("I am roboto", load_roboto()) << "failed to load roboto font";
}

TEST(onyx, load_programs)
{
    ASSERT_TRUE(load_programs()) << "failed to load programs";
}

}