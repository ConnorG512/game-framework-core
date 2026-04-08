#include "logging.hpp"
#include <bitmasking.hpp>
#include <cassert>
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
    case GFC::Logger::LogType::ANGEL_INFO:
      return "ANGEL INFO";
    case GFC::Logger::LogType::ANGEL_ERROR:
      return "ANGEL ERROR";
    default:
      return "INVALID LOG USE";
  }
}
} // namespace

GFC::Logger::Instance::Instance(const std::filesystem::path &path, const std::span<const LogType> active_log_types,
                                const std::uint64_t max_write_count)
    : file_(std::filesystem::path(path / "application.log"), std::ios::trunc), max_write_count_(max_write_count),
      selected_types_(GFC::Bitset::create_bitmask(active_log_types))
{
  if (max_write_count_ == 0)
    write_to_logger("Maximum log count has been disabled.", Logger::LogType::INFO);
  else
    write_to_logger(std::format("Logger max count has been set to: {}.", max_write_count_), Logger::LogType::INFO);
}

void GFC::Logger::Instance::write_to_logger(const std::string &message, LogType prefix_type) noexcept
{
  for (const auto log_type : {LogType::ALL, LogType::NONE, LogType::ANGEL, LogType::ENGINE, LogType::BASIC})
    assert(prefix_type != log_type && "Log type provided for writing to logger should not be a preset!");

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

void GFC::Logger::Instance::flush() noexcept
{
  assert(file_.is_open());
  file_.flush();
}
