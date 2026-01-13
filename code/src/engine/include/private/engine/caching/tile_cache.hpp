#pragma once

#include <cstddef>

namespace onyx::engine::caching
{

class tile_cache
{
public:

    static tile_cache& ref(); 
    static void shutdown();

public:

    void update();

    void set_capacity(size_t capacity) { m_capacity = capacity; }
    size_t get_capacity() const { return m_capacity; }

private:

    static tile_cache* s_instance;
    tile_cache();
    ~tile_cache();

    size_t m_capacity;

};

}