#include "onyx/onyx.hpp"

#include <lucid/scalar.hpp>

namespace onyx
{

    int add(int lhs, int rhs)
    {
        return lucid::add(lhs, rhs);
    }

}