#include "init/builder.hpp"
#include "init/instance.hpp"
#include <cassert>

GFC::Init::Builder &GFC::Init::Builder::set_app_name(const char *name) noexcept
{
  app_name_ = name;
  assert(name != nullptr);
  return *this;
}

GFC::Init::Builder &GFC::Init::Builder::set_app_version(const char *version) noexcept
{
  app_version_ = version;
  assert(version != nullptr);
  return *this;
}

GFC::Init::Builder &GFC::Init::Builder::set_app_identifier(const char *id) noexcept
{
  app_identifier_ = id;
  assert(id != nullptr);
  return *this;
}

GFC::Init::Builder &GFC::Init::Builder::set_flags(const std::span<const Flags> flags) noexcept
{
  for (const auto &flag : flags)
    flags_.emplace_back(flag);

  return *this;
}

GFC::Init::Instance
GFC::Init::Builder::build(GFC::Logger::Instance *logger) const
{
  return GFC::Init::Instance(*this, logger);
}
