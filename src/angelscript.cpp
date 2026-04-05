#include "angelscript.h"
#include "angelscript.hpp"
#include "logging.hpp"
#include <cassert>
#include <format>

namespace
{
void register_function(asIScriptEngine *engine, const std::span<const GFC::Angel::ExportedFunction> angel_funcs,
                       GFC::Logger::Instance *logger = nullptr)
{
  assert(engine);
  for (const auto &func : angel_funcs)
  {
    assert(func.declaration);
    assert(func.address);
  }

  if (logger)
    logger->write_to_logger(std::format("Found {} functions to regiser to anglescript.", angel_funcs.size()),
                            GFC::Logger::LogType::DEBUG);

  for (const auto &func : angel_funcs)
  {
    const auto res{engine->RegisterGlobalFunction(func.declaration, asFUNCTION(func.address), asCALL_CDECL)};
    if (logger && res < 0)
      logger->write_to_logger(std::format("Failed to Register Angelscript Function: [{}].", func.declaration),
                              GFC::Logger::LogType::ERROR);
  }
}
} // namespace

GFC::Angel::Engine::Engine(GFC::Logger::Instance *logger) : logger_(logger)
{
  assert(logger_ != nullptr);

  if (engine_ == nullptr)
    logger->write_to_logger("Failed to create AngelScript engine, is nullptr!", GFC::Logger::LogType::ERROR);
  else
    logger->write_to_logger("AngelScript engine init successful!", GFC::Logger::LogType::INFO);
}

GFC::Angel::Engine::~Engine() { engine_->ShutDownAndRelease(); }
