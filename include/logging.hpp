#pragma once

#include <expected>
#include <fstream>
#include <string_view>

namespace GFC::Logger
{
class Instance
{
public:
  enum class InfoType
  {
    ERROR,
    WARNING,
    DEBUG,
    INFO,
  };
  explicit Instance(const std::string &file_path);

  [[nodiscard]] std::expected<void, std::string_view> write_to_logger(const std::string &message,
                                                                      InfoType prefix_type) noexcept;

private:
  std::ofstream file_{"application.log"};
};
} // namespace GFC::Logger
