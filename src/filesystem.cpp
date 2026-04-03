#include "filesystem.hpp"

#include <cassert>
#include <filesystem>

[[nodiscard]] bool GFC::Filesystem::does_directory_exist(
    const std::string &file_path, std::function<void(const std::string &message, GFC::Logger::LogType type)> log_func)
{
  const char *err_dir_empty{"File path that has been provided to \"does_directory_exist\" is empty!"};
  assert(!file_path.empty() && err_dir_empty);

  if (log_func != nullptr)
    log_func(err_dir_empty, GFC::Logger::LogType::ERROR);

  return (std::filesystem::exists(file_path));
}
