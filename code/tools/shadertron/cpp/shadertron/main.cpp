#include <filesystem>
#include <fstream>
#include <iostream>

#include <CLI/CLI.hpp>

#include <shaders/generate.hpp>
#include <shaders/load.hpp>

namespace onyx::shadertron
{

static constexpr std::string c_base_directory = "shaders";

void touch_directory(std::string const& path)
{
    if (!std::filesystem::exists(path))
    {
        std::filesystem::create_directory(path);
    }
}

void generate(bool clean_first)
{
    if (clean_first)
    {
        std::filesystem::remove_all(c_base_directory);
    }

    std::filesystem::remove_all(c_base_directory + "/src");

    touch_directory(c_base_directory);
    touch_directory(c_base_directory + "/src");

    std::vector<shaders::pair> pairs = shaders::generate();
    for (shaders::pair const& pair : pairs)
    {
        std::ofstream file(c_base_directory + "/src/" + pair.filename);
        file << pair.contents; 
    }
}

int main(int argc, char* argv[])
{
    CLI::App app("shadertron is a tool that generates shaders from families of json components.", "shadertron");

    bool clean_first = false;
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