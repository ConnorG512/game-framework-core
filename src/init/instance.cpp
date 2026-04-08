#include "SDL3/SDL_error.h"
#include "SDL3/SDL_init.h"
#include "init/builder.hpp"
#include "init/instance.hpp"
#include "logging.hpp"
#include "utils.hpp"

#include <array>
#include <cassert>
#include <format>
#include <ranges>
#include <stdexcept>
#include <string_view>

GFC::Init::Instance::~Instance() { SDL_Quit(); }

GFC::Init::Instance::Instance(const Init::Builder &builder, GFC::Logger::Instance *logger)
{
  // Instance is a friend of Builder.
  if (!SDL_SetAppMetadata(builder.app_name_.c_str(), builder.app_version_.c_str(), builder.app_identifier_.c_str()))
  {
    if (logger != nullptr)
      logger->write_to_logger(std::format("Failed to Set App Metadata! Error: {}.", SDL_GetError()),
                              Logger::LogType::ERROR);
  }
  if (!SDL_Init(Utils::or_flags<Init::Flags, SDL_InitFlags>(builder.flags_)))
  {
    constexpr std::string_view error_message{"Failed to Initialise application! Error:"};
    if (logger != nullptr)
      logger->write_to_logger(std::format("{} {}.", error_message, SDL_GetError()), Logger::LogType::ERROR);
    throw std::runtime_error(std::format("{} {}.", error_message, SDL_GetError()));
  }
  if (logger != nullptr)
  {
    const auto titles = std::to_array({"App Title", "App Version", "App Identifier"});
    const auto properties = std::to_array({builder.app_name_, builder.app_version_, builder.app_identifier_});
    for (const auto &[title, property] : std::views::zip(titles, properties))
      logger->write_to_logger(std::format("{}: {}", title, property), Logger::LogType::DEBUG);
  }
}
