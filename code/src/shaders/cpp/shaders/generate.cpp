#include "shaders/generate.hpp"

#include <cmrc/cmrc.hpp>

#include "shaders/load.hpp"

CMRC_DECLARE(shaders_json);

namespace onyx::shaders
{

namespace
{

void load_handwritten(std::vector<pair>& pairs, cmrc::embedded_filesystem const& fs, std::string const& name)
{
    const char* prefix = "assets/shaders/handwritten/";
    // vertex
    {
        std::string path = prefix + name + ".vs.sc";
        auto file = fs.open(path);
        std::string str(file.begin(), file.end());
        pairs.emplace_back(name + ".vs.sc", str);
    }
    // fragment
    {
        std::string path = prefix + name + ".fs.sc";
        auto file = fs.open(path);
        std::string str(file.begin(), file.end());
        pairs.emplace_back(name + ".fs.sc", str);
    }
}

}

std::vector<pair> generate()
{
    std::vector<pair> pairs;

    auto fs = cmrc::shaders_json::get_filesystem(); 

    // add handwritten shaders
    {
        load_handwritten(pairs, fs, "Fog");
    }

    // add generated shaders
    {
        nlohmann::json plinth = shaders::load_components();

        std::string vertex_input;
        std::string vertex_output;

        for (nlohmann::json const& input : plinth["inputs"])
        {
            if (!vertex_input.empty())
            {
                vertex_input += ", ";
            }
            std::string const& name = input["name"];
            vertex_input += name;
        }

        for (nlohmann::json const& transfers : plinth["transfers"])
        {
            if (!vertex_output.empty())
            {
                vertex_output += ", ";
            }
            std::string const& name = transfers["name"];
            vertex_output += name;
        }

        pairs.push_back({
            "Plinth.vs.sc",
            "$input " + vertex_input + "\n$output " + vertex_output
        });

        pairs.push_back({
            "Plinth.fs.sc",
            "$input " + vertex_output
        });
    }

    return pairs;
}

}