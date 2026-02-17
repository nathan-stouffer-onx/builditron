#include <emscripten/bind.h>
#include <mapitron/mapitron.hpp>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mapitron) {
    // Expose the mapitron API to JavaScript
    function("shutdown", &mapitron::shutdown);
    function("add", &mapitron::add);
    function("addLayer", &mapitron::add_layer);
    function("loadRoboto", &mapitron::load_roboto);
    function("loadPrograms", &mapitron::load_programs);
}
