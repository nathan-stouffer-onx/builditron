#include "engine/brain.hpp"

#include "engine/caching/tile_cache.hpp"

namespace onyx::engine
{

brain* brain::s_instance = nullptr;

brain& brain::ref()
{
    if (s_instance) { return *s_instance; }
    s_instance = new brain();
    return *s_instance;
}

void brain::shutdown()
{
    delete s_instance;
    s_instance = nullptr;
}

brain::brain()
{
    caching::tile_cache::ref();
}

brain::~brain()
{
    caching::tile_cache::shutdown();
}

void brain::add_layer(styling::layer const& layer) {}

}