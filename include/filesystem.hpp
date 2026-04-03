#pragma once

#include "logging.hpp"
#include <functional>
#include <string>

namespace GFC::Filesystem
{
[[nodiscard]] bool
does_directory_exist(const std::string &file_path,
                     std::function<void(const std::string &message, GFC::Logger::LogType type)> log_func = nullptr);
}
