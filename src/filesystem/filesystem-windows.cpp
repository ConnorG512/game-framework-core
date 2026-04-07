#include "filesystem.hpp"

#include <cassert>
#include <cstdlib>
#include <filesystem>

std::filesystem::path init(const std::string &base_directory_title) noexcept
{
  assert(!base_directory_title.empty() && "\"base_directory_title\" cannot be empty!");
  
  const auto* local_app_data_path {std::getenv("LOCALAPPDATA")};
  assert(local_app_data_path != nullptr);

  const std::filesystem::path full_path{std::filesystem::path{local_app_data_path} / base_directory_title};

  if (!std::filesystem::exists(full_path))
    std::filesystem::create_directories(full_path);

  return full_path;
}
