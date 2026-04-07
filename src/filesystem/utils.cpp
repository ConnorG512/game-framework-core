#include "filesystem/utils.hpp"

#include <cstdlib>

GFC::Filesystem::Directory
GFC::Filesystem::find_path_from_env_var(const std::string& env_var, bool allow_custom_path) noexcept
{
  auto find_dir = [](const char* env_var = nullptr) -> const char*
  {
    const auto* dir {std::getenv(env_var)};
    return (dir != nullptr) ? dir : nullptr;
  };

  // Search the custom provided path before looking in system paths.
  if(allow_custom_path == true)
    return {find_dir("GAME_DATA_DIR"), FoundDirType::CUSTOM};
  else 
    return {find_dir(env_var.c_str()), FoundDirType::SYSTEM};
}
