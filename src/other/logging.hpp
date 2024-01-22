#pragma once

#include <fstream>
#include <string>
#include <ctime>

namespace logging {
    enum log_lvl {
        LOG_ERROR,
        LOG_WARNING,
        LOG_SUCCESS,
        LOG_INFO
    };

    std::string get_current_time();
    void log_message(log_lvl level, std::string message, std::string log_file_name = "gdhacks/log_file.log");
} // namespace logging


#define L_ERROR(message) logging::log_message(logging::LOG_ERROR, message)
#define L_WARNING(message) logging::log_message(logging::LOG_WARNING, message)
#define L_SUCCESS(message) logging::log_message(logging::LOG_SUCCESS, message)
#define L_INFO(message) logging::log_message(logging::LOG_INFO, message)