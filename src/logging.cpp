#include "logging.hpp"
#include <expected>
#include <format>
#include <print>

GFC::Logger::Instance::Instance(const std::string &file_path) : file_(file_path) {}

[[nodiscard]] std::expected<void, std::string_view>
GFC::Logger::Instance::write_to_logger(const std::string &message, LogType prefix_type) noexcept
{
  const std::string_view prefix = [prefix_type] -> std::string_view
  {
    switch (prefix_type)
    {
      case LogType::ERROR:
        return "ERROR";
      case LogType::WARNING:
        return "WARNING";
      case LogType::DEBUG:
        return "DEBUG";
      case LogType::INFO:
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
