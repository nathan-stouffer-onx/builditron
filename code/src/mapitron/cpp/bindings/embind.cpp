#include <emscripten/bind.h>
#include <mapitron/mapitron.hpp>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mapitron)
{
    // Expose the mapitron API to JavaScript
    function("build_type", &mapitron::build_type);
    function("shutdown", &mapitron::shutdown);
    function("add", &mapitron::add);
    function("add_layer", &mapitron::add_layer);
    function("load_roboto", &mapitron::load_roboto);
    function("load_programs", &mapitron::load_programs);
}
