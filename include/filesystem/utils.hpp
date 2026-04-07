#pragma once

#include <cstdint>
#include <string>

namespace GFC::Filesystem
{
enum class FoundDirType : std::uint32_t
{
  CUSTOM,
  SYSTEM,
};
struct Directory
{
  const char *path{nullptr};
  FoundDirType type{};
};

Directory find_path_from_env_var(const std::string& env_var, bool allow_custom) noexcept;
}; // namespace GFC::Filesystem
