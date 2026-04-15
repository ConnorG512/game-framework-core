#include "logging.hpp"
#include "renderer/instance.hpp"

#include <VkBootstrap.h>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vulkan/vulkan_core.h>

namespace
{
auto get_shader_code_size = [](const std::integral auto file_size) { return file_size * sizeof(std::uint32_t); };
} // namespace

void GFC::Ren::init(const EasyWindow::Instance &window, Logger::Instance *logger)
{
  vkb::InstanceBuilder builder{};
  auto inst_ret = builder.set_app_name("Example Vulkan App")
                      .request_validation_layers(true)
                      .use_default_debug_messenger()
                      .require_api_version(1, 3, 0)
                      .build();
  if (!inst_ret.has_value())
  {
    const std::string vulkan_build_error{
        std::format("Failed to build Vulkan instance! Error: {}", inst_ret.error().message())};
    if (logger != nullptr)
      logger->write_to_logger(vulkan_build_error, GFC::Logger::LogType::ERROR);
    throw std::runtime_error(vulkan_build_error);
  }

  vkb::Instance vkb_inst = inst_ret.value();
}

