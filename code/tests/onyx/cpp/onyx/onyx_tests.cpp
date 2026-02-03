#include <vector>

#include <gtest/gtest.h>

#include <mapitron/mapitron.hpp>

namespace mapitron
{

TEST(mapitron, add)
{
    ASSERT_EQ(0, mapitron::add(0, 0)) << "failed 0 + 0";
    ASSERT_EQ(6, mapitron::add(5, 1)) << "failed 5 + 1";
    ASSERT_EQ(6, mapitron::add(1, 5)) << "failed 1 + 5";
}

TEST(mapitron, add_layer)
{
    mapitron::add_layer(R"({ "type": "line" })");
}

TEST(mapitron, load_roboto)
{
    ASSERT_EQ("I am roboto", load_roboto()) << "failed to load roboto font";
}

TEST(mapitron, load_programs)
{
    ASSERT_TRUE(load_programs()) << "failed to load programs";
}

}