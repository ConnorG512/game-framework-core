#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>
#include <utility>

namespace GFC::Logger
{
enum class LogType : std::uint8_t
{
  // BitFlags:
  ERROR = 1,
  WARNING = 2,
  DEBUG = 4,
  INFO = 8,
  ANGEL_INFO = 16,
  ANGEL_ERROR = 32,

  // Presets:
  ALL = 0xFF,
  NONE = 0,
  ENGINE = ERROR | WARNING | DEBUG | INFO,
  ANGEL = ANGEL_INFO | ANGEL_ERROR,
  BASIC = ERROR | ANGEL_ERROR,
};

class Instance
{
public:
  explicit Instance(const std::filesystem::path &path, const std::span<const LogType> active_log_types,
                    const std::uint64_t max_write_count = 0);

  void write_to_logger(const std::string &message, LogType prefix_type) noexcept;

private:
  std::ofstream file_{"application.log", std::ios::trunc};
  std::uint64_t current_write_count_{0};
  std::uint64_t max_write_count_{std::numeric_limits<decltype(max_write_count_)>::max()};
  std::uint8_t selected_types_{std::to_underlying(LogType::BASIC)};
};
} // namespace GFC::Logger
