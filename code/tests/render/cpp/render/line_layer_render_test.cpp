#include <chrono>
#include <fstream>

#include <gtest/gtest.h>

#include <onyx/onyx.hpp>

namespace onyx
{

TEST(render, line_layer)
{
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::string filename = "assets/golden-img/line_layer_render_test.txt";
    std::ifstream fstream(filename);
    if (!fstream.is_open())
    {
        FAIL() << "Failed to open " << filename;
    }
    else
    {
        std::string line;
        std::getline(fstream, line);
        fstream.close();
        ASSERT_EQ("line layer", line) << "Incorrect golden img";
    }
}

}