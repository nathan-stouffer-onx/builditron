#include <filesystem>
#include <fstream>
#include <iostream>

#include <CLI/CLI.hpp>

#include <shaders/generate.hpp>
#include <shaders/load.hpp>

namespace onyx::shadertron
{

static constexpr char c_directory[] = "shaders";

void log(nlohmann::json const& component)
{
    std::cout << "shader inputs: [ ";
    bool first = true;
    for (nlohmann::json const& input : component["inputs"])
    {
        if (!first)
        {
            std::cout << ", ";
        }
        std::cout << input["name"];
        first = false;
    }
    std::cout << " ]" << std::endl;
}

void generate(bool clean_first)
{
    if (clean_first)
    {
        std::filesystem::remove_all(c_directory);
    }

    if (!std::filesystem::exists(c_directory))
    {
        std::filesystem::create_directory(c_directory);
    }

    nlohmann::json component = shaders::load();
    log(component);

    std::vector<shaders::pair> pairs = shaders::generate();
    for (shaders::pair const& pair : pairs)
    {
        std::ofstream file(std::string(c_directory) + "/" + pair.filename);
        file << pair.contents; 
    }
}

int main(int argc, char* argv[])
{
    CLI::App app("shadertron is a tool that generates shaders from families of json components.", "shadertron");

    bool clean_first = true;
    app.add_option("-c,--clean-first", clean_first, "Indicates whether or not the existing output directory should be cleaned first")
        ->capture_default_str();

    generate(clean_first);

    return 0;
}

}

int main(int argc, char* argv[])
{
    return onyx::shadertron::main(argc, argv);
}