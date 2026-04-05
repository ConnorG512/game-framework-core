#include "logging.hpp"
#include <bitmasking.hpp>
#include <expected>
#include <format>
#include <print>
#include <utility>

namespace {
  bool is_at_max_log_count(std::uint64_t current_log_count, std::uint64_t max_log_count)
  {
    // 0 indicates no limit. 
    if(max_log_count == 0)
      return false; 
    
    return (current_log_count >= max_log_count);
  }
}

GFC::Logger::Instance::Instance(const std::string &file_path, const std::span<const LogType> active_log_types) 
  : file_(file_path) 
  , selected_types_(GFC::Bitset::create_bitmask(active_log_types)) {}

[[nodiscard]] std::expected<void, std::string_view> GFC::Logger::Instance::write_to_logger(const std::string &message,
                                                                                           LogType prefix_type) noexcept
{
  if (selected_types_ == std::to_underlying(LogType::NONE))
    return {};

  if (!GFC::Bitset::is_active_bit(selected_types_, prefix_type))
    return {};

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
