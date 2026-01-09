#include <gtest/gtest.h>

#include <shaders/load.hpp>

namespace onyx::shaders
{

TEST(shaders, load)
{
    nlohmann::json shader = load();
    ASSERT_EQ(2, shader["inputs"].size()) << "failed to load correct number of inputs";
}

}