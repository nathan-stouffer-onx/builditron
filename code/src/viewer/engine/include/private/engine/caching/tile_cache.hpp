#pragma once

namespace onyx::engine
{

class tile_cache
{
public:

    tile_cache();

    void update();

    void set_capacity(size_t capacity) { m_capacity = capacity; }
    size_t get_capacity() const { return m_capacity; }

private:

    size_t m_capacity;

};

}