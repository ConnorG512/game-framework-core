#pragma once

#include <cstdint>
#include <expected>
#include <fstream>
#include <string_view>

namespace GFC::Logger
{
enum class LogType : std::uint8_t
{
  NONE = 0,
  ERROR = 1,
  WARNING = 2,
  DEBUG = 4,
  INFO = 8,
  ALL = 0xFF,
};

class Instance
{
public:
  explicit Instance(const std::string &file_path, const std::span<const LogType> active_log_types);

  [[nodiscard]] std::expected<void, std::string_view> write_to_logger(const std::string &message,
                                                                      LogType prefix_type) noexcept;

private:
  std::ofstream file_{"application.log"};
  std::uint8_t selected_types_{0};
};
} // namespace GFC::Logger
