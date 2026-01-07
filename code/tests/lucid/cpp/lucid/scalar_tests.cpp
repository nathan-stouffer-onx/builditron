#include <vector>

#include <gtest/gtest.h>

#include <lucid/scalar.hpp>

namespace lucid
{

TEST(scalar, add)
{
    ASSERT_EQ(0, lucid::add(0, 0)) << "failed 0 + 0";
    ASSERT_EQ(6, lucid::add(5, 1)) << "failed 5 + 1";
    ASSERT_EQ(6, lucid::add(1, 5)) << "failed 1 + 5";
}

}