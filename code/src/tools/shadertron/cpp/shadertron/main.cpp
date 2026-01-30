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
            std::cout << "[gen: " << pair.filename << "]" << std::endl;
            std::ofstream file(target);
            file << pair.contents;
        }
        else
        {
            fs::rename(cached_path, target);
        }
    }
}

void pack(bool clean_first, std::string const& input_directory, std::string const& output_filename)
{
    std::ofstream file(output_filename);

    std::string header = 
R"(
#include <algorithm>
#include <vector>

namespace onyx::shaderblobs
{
)";

    std::string index_struct = 
R"(
struct file_range
{
    std::string filename;
    size_t begin;
    size_t size;
};

static std::vector<file_range> s_file_ranges;
static std::vector<uint8_t> s_file_bytes;
)";

std::string file_ranges = "\nstatic std::vector<file_range> s_file_ranges = \n{";
    std::string file_bytes = "\nstatic std::vector<uint8_t> s_file_bytes = \n{";

    {
        namespace fs = std::filesystem;
        for (auto& entry : fs::directory_iterator(input_directory))
        {
            if (entry.is_regular_file())
            {
                file_bytes += "\n    0x00,";
            }
        }
    }

    file_ranges += "\n};\n";
    file_bytes += "\n};\n";

    std::string load_func =
R"(
std::string load(std::string const& filename)
{
    auto found = std::find_if(s_file_ranges.begin(), s_file_ranges.end(),
        [&filename] (file_range const& range) { return range.filename == filename; }
    );

    if (found == s_file_ranges.end())
    {
        return "";
    }
    else
    {
        file_range const& range = *found;
        return std::string(s_file_bytes[range.begin], range.size);
    }
}
)";

    std::string footer = 
R"(
})";

    file << header;
    file << index_struct;
    file << load_func;
    file << file_ranges;
    file << file_bytes;
    file << footer;
}

enum class types
{
    generate,
    pack,
};

int main(int argc, char* argv[])
{
    CLI::App app("shadertron is a tool that generates shaders from families of json components.", "shadertron");
    app.require_subcommand(1);

    types type;
    bool clean_first = false;
    std::string input_directory;
    std::string output_filename;

    // add generate subcommand
    {
        CLI::App* generate = app.add_subcommand("generate", "Generate shaders from json");
        generate->callback([&type] { type = types::generate; });
    }

    // add pack subcommand
    {
        CLI::App* pack = app.add_subcommand("pack", "Pack generated shaders into a single cpp file");
        pack->callback([&type] { type = types::pack; });

        pack->add_option("-i,--input_directory", input_directory, "Name of the input directory to pack")
            ->required();

        pack->add_option("-o,--output_file", output_filename, "Name of generated output file containing packed shaders")
            ->required();
    }

    app.add_option("-c,--clean-first", clean_first, "Indicates whether or not the existing output directory should be cleaned first")
        ->capture_default_str();

    CLI11_PARSE(app, argc, argv);

    if (type == types::generate)
    {
        generate(clean_first);
    }
    else if (type == types::pack)
    {
        pack(clean_first, input_directory, output_filename);
    }

    return 0;
}

}

int main(int argc, char* argv[])
{
    return onyx::shadertron::main(argc, argv);
}