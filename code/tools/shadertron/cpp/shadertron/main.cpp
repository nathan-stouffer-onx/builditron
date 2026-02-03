#include <filesystem>
#include <fstream>
#include <iostream>

#include <CLI/CLI.hpp>

#include <shaders/generate.hpp>
#include <shaders/load.hpp>

namespace mapitron::shadertron
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

void pack(bool clean_first, std::string const& input_dir, std::filesystem::path const& output_dir)
{
    std::ofstream file_ranges(output_dir / "shaderblobs_ranges.inc");
    std::ofstream file_bytes(output_dir / "shaderblobs_bytes.inc");

    {
        size_t count = 0;
        namespace fs = std::filesystem;
        for (auto& entry : fs::directory_iterator(input_dir))
        {
            if (entry.is_regular_file())
            {
                std::string contents;
                {
                    std::ifstream file(entry.path(), std::ios::binary);
                    file.seekg(0, std::ios::end);
                    contents.resize(file.tellg());
                    file.seekg(0, std::ios::beg);
                    file.read(contents.data(), contents.size());
                }

                // add file range
                {
                    file_ranges << "{ ";
                    file_ranges << entry.path().filename();
                    file_ranges << ", " << count;
                    file_ranges << ", " << contents.size();
                    file_ranges << " },\n";
                }

                // add file bytes
                {
                    file_bytes << "// " << entry.path().filename();
                    file_bytes  << "\n";
                    for (unsigned char byte : contents)
                    {
                        file_bytes
                            << "0x"
                            << std::hex
                            << std::setw(2)
                            << std::setfill('0')
                            << static_cast<int>(byte)
                            << ", ";
                    }
                    file_bytes  << "\n";
                }

                count += contents.size();
            }
        }
    }
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
    std::string input_dir;
    std::string output_dir;

    // add generate subcommand
    {
        CLI::App* generate = app.add_subcommand("generate", "Generate shaders from json");
        generate->callback([&type] { type = types::generate; });
    }

    // add pack subcommand
    {
        CLI::App* pack = app.add_subcommand("pack", "Pack generated shaders into a single cpp file");
        pack->callback([&type] { type = types::pack; });

        pack->add_option("-i,--input_dir", input_dir, "Name of the input directory to pack")
            ->required();

        pack->add_option("-o,--output_dir", output_dir, "Name of generated output directory containing packed shaders")
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
        pack(clean_first, input_dir, output_dir);
    }

    return 0;
}

}

int main(int argc, char* argv[])
{
    return mapitron::shadertron::main(argc, argv);
}