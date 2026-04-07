#include "filesystem.hpp"

#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <format>

GFC::Filesystem::Instance::Instance(const std::string &program_dir_name)
    : program_dir_path_(std::format("{}/.local/share/{}/", std::getenv("HOME"), program_dir_name))
{
  assert(!program_dir_path_.empty());
  if (!std::filesystem::exists(program_dir_path_))
    std::filesystem::create_directory(program_dir_path_);
}

const std::filesystem::path &GFC::Filesystem::Instance::get_directory_path() const noexcept
{
  return program_dir_path_;
}
