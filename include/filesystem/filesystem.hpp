#pragma once

#include <expected>
#include <filesystem>
#include <string>

namespace GFC::Filesystem
{

enum class DirError
{
  DIR_VAR_NULL,
  NO_DIR_FOUND,
};
std::expected<std::filesystem::path, DirError> init(const std::string &base_directory_title,
                                                    const bool allow_custom_dir = false) noexcept;
} // namespace GFC::Filesystem
