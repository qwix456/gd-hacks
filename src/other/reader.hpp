#pragma once

#include "../utils.hpp"
#include "../hacks/gd.hpp"
#include "../hacks/bools.hpp"
#include "logging.hpp"
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

namespace reader
{
    extern settings setting;
    extern json data;
    void load();
    void apply_hack(json& item_hack);
} // namespace reader