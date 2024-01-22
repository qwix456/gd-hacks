#include "logging.hpp"

std::string logging::get_current_time()
{
    std::time_t raw_time;
    std::time(&raw_time);
    std::tm* time_info = std::localtime(&raw_time);

    char buffer[9];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", time_info);

    return std::string(buffer);
}

void logging::log_message(log_lvl level, std::string message, std::string log_file_name)
{
    std::ofstream log_file(log_file_name, std::ios::out);

    if (!log_file.is_open())
        return;

    if (log_file.tellp() != 0)
        log_file << std::endl;

    std::string log_entry = "[" + get_current_time() + "][";

    switch (level) {
        case LOG_ERROR:
            log_entry += "ERROR]";
            break;
        case LOG_WARNING:
            log_entry += "WARNING]";
            break;
        case LOG_SUCCESS:
            log_entry += "SUCCESS]";
            break;
        case LOG_INFO:
            log_entry += "INFO]";
            break;
        default:
            break;
    }

    log_entry += "[GDHacks] " + message;

    log_file << log_entry << std::endl;
    log_file.close();
}

#define L_ERROR(message) logging::log_message(logging::LOG_ERROR, message)
#define L_WARNING(message) logging::log_message(logging::LOG_WARNING, message)
#define L_SUCCESS(message) logging::log_message(logging::LOG_SUCCESS, message)