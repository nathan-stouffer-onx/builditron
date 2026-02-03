#include "engine/caching/tile_cache.hpp"

namespace mapitron::engine::caching
{

tile_cache* tile_cache::s_instance = nullptr;

tile_cache& tile_cache::ref()
{
    if (s_instance) { return *s_instance; }
    s_instance = new tile_cache();
    return *s_instance;
}

void tile_cache::shutdown()
{
    delete s_instance;
    s_instance = nullptr;
}

tile_cache::tile_cache() : m_capacity(1 << 15) {}

tile_cache::~tile_cache() = default;

void tile_cache::update() {}

}