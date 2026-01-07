#include <iostream>

#include <Windows.h>

#include <onyx/onyx.hpp>

int run()
{
    std::cout << "8 + 3 = " << onyx::add(8, 3) << std::endl;
    std::cout << "Adding layer" << std::endl;
    onyx::add_layer(R"({ "type": "fill" })");
    std::cout << "Added layer" << std::endl;
    return 0;
}

int main(int argc, char* argv[])
{
    return run();
}