#include "filesystem/filesystem.hpp"
#include "filesystem/utils.hpp"

#include <cassert>
#include <filesystem>

std::expected<std::filesystem::path, GFC::Filesystem::DirError>
GFC::Filesystem::init(const std::string &base_directory_title, const bool allow_custom_dir) noexcept
{
  assert(!base_directory_title.empty() && "\"base_directory_title\" cannot be empty!");

  const auto [path, type] = find_path_from_env_var("HOME", true);
  if (path == nullptr)
    return std::unexpected(DirError::DIR_VAR_NULL);
  if (type == FoundDirType::CUSTOM)
    return std::filesystem::path(path);
  else if (type == FoundDirType::SYSTEM)
    return std::filesystem::path(path) / ".local" / "share" / base_directory_title;
  else
    return std::unexpected(DirError::NO_DIR_FOUND);
}
