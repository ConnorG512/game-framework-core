#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace GFC
{
// Forward
namespace Logger
{
class Instance;
}
//

namespace Init
{
// Forward
class Instance;
enum class Flags : std::uint32_t;
//

class Builder
{
  friend class Init::Instance;

public:
  Builder &set_app_name(const char *name) noexcept;
  Builder &set_app_version(const char *version) noexcept;
  Builder &set_app_identifier(const char *id) noexcept;
  Builder &set_flags(const std::span<const Flags> flags) noexcept;
  Init::Instance build(GFC::Logger::Instance *logger = nullptr) const;

private:
  std::string app_name_{"Application"};
  std::string app_version_{"1.0.0"};
  std::string app_identifier_{"com.example.application"};
  std::vector<Flags> flags_{};
};
} // namespace Init
} // namespace GFC
