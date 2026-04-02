#pragma once

#include <span>
#include <string>
#include <vector>

namespace Init
{
// Forward
class Instance;
enum class Flags;
//

class Builder
{
  friend class Init::Instance;

public:
  consteval Builder &set_app_name(const char *name) noexcept;
  consteval Builder &set_app_version(const char *version) noexcept;
  consteval Builder &set_app_identifier(const char *id) noexcept;
  consteval Builder &set_flags(const std::span<const Flags> flags) noexcept;
  Init::Instance build();

private:
  std::string app_name_{"Application"};
  std::string app_version_{"1.0.0"};
  std::string app_identifier_{"com.example.application"};
  std::vector<Flags> flags_{};
};
} // namespace Init
