#include "engine/rendering/program.hpp"

#include <string>

#include <shaderblobs/load.hpp>

namespace mapitron::engine::rendering
{

bool load_programs()
{
    std::string vert = shaderblobs::load("Plinth.vs.sc");
    std::string frag = shaderblobs::load("Plinth.fs.sc");
    return !vert.empty() && !frag.empty();
}

}