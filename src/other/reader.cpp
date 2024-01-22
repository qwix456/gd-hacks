#include "reader.hpp"
#include "../hooks.hpp"

using json = nlohmann::json;

namespace reader {
    json data;
    settings setting;

    void load() {
            std::ifstream file("gdhacks/hacks.json");

            L_INFO("Loading hacks.json...");

            if (!file.is_open()) {
                L_ERROR("Failed to open hack.json");
                return;
            }

            std::string file_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();

            L_INFO("hacks.json opened");

            try {
                data = json::parse(file_content);
                L_SUCCESS("hacks.json parsed successfully");
            } catch (const json::parse_error& e) {
                L_ERROR("Error parsing hacks.json: " + std::string(e.what()));
                return;
            }

            if (data.empty()) {
                L_WARNING("No items in data.");
                return;
            }

            for (auto item : data.items()) {
                json hack = item.value();
                L_INFO("Processing hack item: " + item.key());
                L_INFO("Total hacks: " + std::to_string(hack.size()));
                for (size_t i = 0; i < hack.size(); i++) {
                    json item_hack = hack.at(i);
                    apply_hack(item_hack);
                }
            }
        }
        
        void apply_hack(json &item_hack)
        {
                if (item_hack["enabled"]) {
                L_INFO("Applying hack: " + item_hack["name"].get<std::string>());

                if (item_hack.find("opcodes") != item_hack.end()) {
                    json opcodes = item_hack["opcodes"];
                    L_INFO("Total opcodes: " + std::to_string(opcodes.size()));
                    for (int j = 0; j < (int)opcodes.size(); j++) {
                        json opcode = opcodes.at(j);
                        uintptr_t address;
                        if (opcode.find("address") == opcode.end()) {
                            L_ERROR("Address field not found in opcode");
                            return;
                        }
                        sscanf_s(opcode["address"].get<std::string>().c_str(), "%x", &address);
                        DWORD base1 = (DWORD)GetModuleHandleA(0);
                        if (!opcode["lib"].is_null()) {
                            base1 = (DWORD)GetModuleHandleA(std::string(opcode["lib"]).c_str());
                        }
                        L_INFO("Writing bytes to memory...");
                        utils::WriteByte(base1 + address, opcode["on"].get<std::string>());
                        L_SUCCESS("Bytes written to memory!");
                    }
                }
            }
        }
}
