#include "window.hpp"

namespace
{
auto or_flags = [](const std::span<Window::Instance::Flags> flags)
{
  auto result{0};
  for (const auto &flag : flags)
    result |= std::to_underlying(flag);
  return result;
};
} // namespace

Window::Instance::Instance(const std::string &title, std::pair<std::int32_t, std::int32_t> xy,
                           const std::span<Flags> flags)
    : title{title.c_str()}, xy_{xy.first, xy.second},
      window_instance_{SDL_CreateWindow(title.c_str(), xy_.first, xy_.second, or_flags(flags)), &SDL_DestroyWindow}
{
}
