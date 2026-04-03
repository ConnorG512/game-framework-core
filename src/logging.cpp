#include "logging.hpp"
#include <expected>
#include <format>
#include <print>

GFC::Logger::Instance::Instance(const std::string &file_path) : file_(file_path) {}

[[nodiscard]] std::expected<void, std::string_view>
GFC::Logger::Instance::write_to_logger(const std::string &message, InfoType prefix_type) noexcept
{
  const std::string_view prefix = [prefix_type] -> std::string_view
  {
    switch (prefix_type)
    {
      case InfoType::ERROR:
        return "ERROR";
      case InfoType::WARNING:
        return "WARNING";
      case InfoType::DEBUG:
        return "DEBUG";
      case InfoType::INFO:
        return "INFO";
      default:
        return "N/A";
    }
  }();

  if (!file_.is_open())
    return std::unexpected("Log file is not open for writing!");
  else
  {
    std::println(file_, "{}: {}", prefix, message);
    return {};
  }
}
