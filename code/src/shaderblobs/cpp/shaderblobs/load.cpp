
#include <algorithm>
#include <vector>

namespace onyx::shaderblobs
{

struct file_range
{
    std::string filename;
    size_t begin;
    size_t size;
};

static std::vector<file_range> s_file_ranges =
{
#include "shaderblobs_ranges.inc"
};

static std::vector<char> s_file_bytes =
{
#include "shaderblobs_bytes.inc"
};

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
        return std::string(s_file_bytes.data() + range.begin, range.size);
    }
}

}