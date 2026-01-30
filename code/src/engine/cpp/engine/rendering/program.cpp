#include "engine/rendering/program.hpp"

#include <filesystem>
#include <string>

namespace onyx::engine::rendering
{

bool load_programs()
{
    namespace fs = std::filesystem;
    std::string base = "assets/shaders/src/Plinth";
    return fs::exists(base + ".vs.sc") && fs::exists(base + ".fs.sc");
}

}