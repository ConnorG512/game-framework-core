#include "SDL3/SDL_error.h"
#include "SDL3/SDL_init.h"
#include "init/builder.hpp"
#include "init/instance.hpp"
#include "utils.hpp"

#include <cassert>
#include <format>
#include <functional>
#include <stdexcept>
#include <string_view>

Init::Instance::~Instance() { SDL_Quit(); }

Init::Instance::Instance(const Init::Builder &builder, std::function<void(const std::string &message)> log_callback)
{
  // Instance is a friend of Builder.
  if (!SDL_SetAppMetadata(builder.app_name_.c_str(), builder.app_version_.c_str(), builder.app_identifier_.c_str()))
  {
    if (log_callback != nullptr)
      log_callback(std::format("Failed to Set App Metadata! Error: {}.", SDL_GetError()));
  }
  if (!SDL_Init(Utils::or_flags<Init::Flags, SDL_InitFlags>(builder.flags_)))
  {
    constexpr std::string_view error_message{"Failed to Initialise application! Error:"};
    if (log_callback != nullptr)
      log_callback(std::format("{} {}.", error_message, SDL_GetError()));
    throw std::runtime_error(std::format("{} {}.", error_message, SDL_GetError()));
  }
}
