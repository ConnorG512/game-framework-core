#include "logging.hpp"
#include <bitmasking.hpp>
#include <expected>
#include <format>
#include <print>
#include <string_view>
#include <utility>

namespace
{
[[nodiscard]] bool is_at_max_log_count(std::uint64_t current_log_count, std::uint64_t max_log_count)
{
  // 0 indicates no limit.
  if (max_log_count == 0)
    return false;

  return (current_log_count >= max_log_count);
}

[[nodiscard]] std::string_view get_logging_prefix(GFC::Logger::LogType prefix_type)
{
  switch (prefix_type)
  {
    case GFC::Logger::LogType::ERROR:
      return "ERROR";
    case GFC::Logger::LogType::WARNING:
      return "WARNING";
    case GFC::Logger::LogType::DEBUG:
      return "DEBUG";
    case GFC::Logger::LogType::INFO:
      return "INFO";
    default:
      return "N/A";
  }
}
} // namespace

GFC::Logger::Instance::Instance(const std::string &file_path, const std::span<const LogType> active_log_types,
                                const std::uint64_t max_write_count)
    : file_(file_path), max_write_count_(max_write_count),
      selected_types_(GFC::Bitset::create_bitmask(active_log_types))
{
}

void GFC::Logger::Instance::write_to_logger(const std::string &message, LogType prefix_type) noexcept
{
  if (selected_types_ == std::to_underlying(LogType::NONE) ||
      !GFC::Bitset::is_active_bit(selected_types_, prefix_type) || !file_.is_open())
    return;

  if (is_at_max_log_count(current_write_count_, max_write_count_))
  {
    std::println(file_, "Log has hit maximum output count of [{}]. Closing log.", max_write_count_);
    file_.close();
  }

  std::println(file_, "{}: {}", get_logging_prefix(prefix_type), message);
  current_write_count_++;
  return;
}
