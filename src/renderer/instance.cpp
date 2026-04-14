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

[[nodiscard]] std::expected<VkShaderModule, GFC::Ren::ShaderLoadError>
GFC::Ren::load_shader(const std::filesystem::path &path, VkDevice device, GFC::Logger::Instance *logger)
{
  if (!std::filesystem::exists(path))
    return std::unexpected(GFC::Ren::ShaderLoadError::DIRECTORY_NOT_FOUND);

  std::ifstream open_shader_file(path, std::ios::ate | std::ios::binary);
  if (!open_shader_file.is_open())
    return std::unexpected(GFC::Ren::ShaderLoadError::FILE_NOT_OPEN);

  const std::size_t file_size{static_cast<std::size_t>(open_shader_file.tellg())};
  std::vector<std::uint32_t> shader_buffer(file_size / sizeof(std::uint32_t));
  assert(file_size != 0 && !shader_buffer.empty());

  if (logger != nullptr)
    logger->write_to_logger(
        std::format("Shader file successfully opened at path {} with size {}.", path.string(), file_size),
        Logger::LogType::DEBUG);

  open_shader_file.seekg(0);
  open_shader_file.read(reinterpret_cast<char *>(shader_buffer.data()), file_size);

  const VkShaderModuleCreateInfo createInfo{
      .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
      .pNext = nullptr,
      .codeSize = get_shader_code_size(shader_buffer.size()),
      .pCode = shader_buffer.data(),
  };
  VkShaderModule shader_module{};

  if (vkCreateShaderModule(device, &createInfo, nullptr, &shader_module) != VK_SUCCESS)
    return std::unexpected(ShaderLoadError::FAILED_TO_CREATE_SHADER_MODULE);
  else
    return shader_module;
}
