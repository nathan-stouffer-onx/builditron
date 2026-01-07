#include <gtest/gtest.h>

#include <engine/caching/tile_cache.hpp>

namespace onyx::engine::caching
{

TEST(engine_caching, tile_cache_capacity)
{
    tile_cache::ref().set_capacity(2);
    ASSERT_EQ(2, tile_cache::ref().get_capacity()) << "failed to set or get capacity";
    tile_cache::shutdown();
}

}