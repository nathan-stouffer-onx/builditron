#include <gtest/gtest.h>

#include <engine/caching/tile_cache.hpp>

namespace onyx::engine::caching
{

class tile_cache_test : public ::testing::Test
{
protected:
    void TearDown() override
    {
        tile_cache::shutdown();
    }
};

TEST_F(tile_cache_test, tile_cache_capacity)
{
    tile_cache::ref().set_capacity(2);
    ASSERT_EQ(2, tile_cache::ref().get_capacity()) << "failed to set or get capacity";
}

}