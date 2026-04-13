#pragma once 

#include <expected>
#include <string_view>

namespace GFC::VK {
  std::expected<void, std::string_view> init() noexcept;
}
