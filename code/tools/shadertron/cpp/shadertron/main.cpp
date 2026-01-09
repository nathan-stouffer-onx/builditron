#include <iostream>

#include <shaders/load.hpp>

namespace onyx::shadertron
{

int main()
{
    nlohmann::json shader = shaders::load();
    std::cout << "shader inputs: [ ";

    bool first = true;
    for (nlohmann::json const& input : shader["inputs"])
    {
        if (!first)
        {
            std::cout << ", ";
        }
        std::cout << input["name"];
        first = false;
    }
    std::cout << " ]" << std::endl;

    return 0;
}

}

int main()
{
    return onyx::shadertron::main();
}