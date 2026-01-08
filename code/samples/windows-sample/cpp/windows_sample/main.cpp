#include <iostream>

#include <Windows.h>

#include <onyx/onyx.hpp>

int run()
{
    // call add
    std::cout << "8 + 3 = " << onyx::add(8, 3) << std::endl;

    // call add_layer
    std::cout << "Adding layer" << std::endl;
    onyx::add_layer(R"({ "type": "fill" })");
    std::cout << "Added layer" << std::endl;

    // load token
    std::ifstream fstream("assets/secrets/token.txt");
    if (!fstream.is_open())
    {
        std::cout << "Failed to open token file" << std::endl;
        return 1;
    }
    else
    {
        std::string line;
        std::getline(fstream, line);
        std::cout << "Token value: " << line << std::endl;
        fstream.close();
    }

    return 0;
}

int main(int argc, char* argv[])
{
    return run();
}