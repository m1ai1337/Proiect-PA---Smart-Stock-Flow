#include "includes.h"
#include "json.hpp"
#include <filesystem>
#include <fstream>

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace data {
    void save();
    void load();
}
