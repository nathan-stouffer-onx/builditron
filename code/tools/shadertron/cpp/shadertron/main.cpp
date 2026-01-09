#include <filesystem>
#include <fstream>
#include <iostream>

#include <CLI/CLI.hpp>

#include <shaders/generate.hpp>
#include <shaders/load.hpp>

namespace onyx::shadertron
{

namespace fs = std::filesystem;

void touch_directory(fs::path const& path)
{
    if (!fs::exists(path))
    {
        fs::create_directory(path);
    }
}

void generate(bool clean_first)
{
    fs::path base = "shaders";

    if (clean_first)
    {
        fs::remove_all(base);
    }

    touch_directory(base);
    touch_directory(base / "src");
    touch_directory(base / "assemble-cache");

    for (fs::directory_entry const& entry : fs::directory_iterator(base / "src"))
    {
        if (entry.is_regular_file())
        {
            fs::path cached = base / "assemble-cache" / entry.path().filename();
            fs::remove(cached);
            fs::rename(entry.path(), cached);
        }
    }

    std::vector<shaders::pair> pairs = shaders::generate();
    for (shaders::pair const& pair : pairs)
    {
        fs::path cached_path = base / "assemble-cache" / pair.filename;
        std::string cached;
        if (fs::exists(cached_path))
        {
            std::ifstream file(cached_path, std::ios::binary);
            file.seekg(0, std::ios::end);
            cached.resize(file.tellg());
            file.seekg(0, std::ios::beg);
            file.read(cached.data(), cached.size());
        }

        fs::path target = base / "src" / pair.filename;
        if (cached != pair.contents)
        {
            std::cout << "[" << pair.filename << "]" << std::endl;
            std::ofstream file(target);
            file << pair.contents;
        }
        else
        {
            fs::rename(cached_path, target);
        }
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