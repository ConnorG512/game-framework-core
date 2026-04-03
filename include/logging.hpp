#pragma once

#include <expected>
#include <fstream>
#include <string_view>

namespace GFC::Logger
{
enum class LogType
{
  ERROR,
  WARNING,
  DEBUG,
  INFO,
};

class Instance
{
public:
  explicit Instance(const std::string &file_path);

  [[nodiscard]] std::expected<void, std::string_view> write_to_logger(const std::string &message,
                                                                      LogType prefix_type) noexcept;

private:
  std::ofstream file_{"application.log"};
};
} // namespace GFC::Logger
