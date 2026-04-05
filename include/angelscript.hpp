#pragma once

#include <angelscript.h>

namespace GFC
{
namespace Logger
{
class Instance;
}

class Angel
{
public:
  Angel(GFC::Logger::Instance *logger);
  Angel() = default;
  ~Angel();

private:
  asIScriptEngine *engine_{asCreateScriptEngine()};
  GFC::Logger::Instance *logger_{nullptr};
};
} // namespace GFC
