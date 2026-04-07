#pragma once

#include <filesystem>
#include <string>

namespace GFC::Filesystem
{
class Instance
{
public:
  explicit Instance(const std::string &program_dir_name);
  const std::string &get_directory_path() const noexcept;

private:
  std::filesystem::path program_dir_path_{};
};
} // namespace GFC::Filesystem
