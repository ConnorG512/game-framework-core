#include "angelscript.h"
#include "angelscript.hpp"
#include "logging.hpp"
#include <cassert>

GFC::Angel::Angel(GFC::Logger::Instance *logger)
  : logger_(logger)
{
  assert(logger_ != nullptr);

  if (engine_ == nullptr)
    logger->write_to_logger("Failed to create AngelScript engine, is nullptr!", GFC::Logger::LogType::ERROR);
  else
    logger->write_to_logger("AngelScript engine init successful!", GFC::Logger::LogType::INFO);
}

GFC::Angel::~Angel() { engine_->ShutDownAndRelease(); }
