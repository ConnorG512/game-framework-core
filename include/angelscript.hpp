#pragma once

#include <angelscript.h>

namespace GFC
{
namespace Logger
{
class Instance;
}

namespace Angel
{
struct ExportedFunction
{
  const char *declaration{nullptr};
  void *address{nullptr};
};

class Engine
{
public:
  Engine(GFC::Logger::Instance *logger);
  Engine() = default;
  ~Engine();

private:
  asIScriptEngine *engine_{asCreateScriptEngine()};
  GFC::Logger::Instance *logger_{nullptr};
};
} // namespace Angel
} // namespace GFC
