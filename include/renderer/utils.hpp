#pragma once

#include <expected>
#include <filesystem>
#include <vulkan/vulkan_core.h>

namespace GFC
{
namespace Logger
{
class Instance;
}
} // namespace GFC

namespace GFC::Ren
{
enum class ShaderLoadError
{
  DIRECTORY_NOT_FOUND,
  FILE_NOT_OPEN,
  FAILED_TO_CREATE_SHADER_MODULE,
};

[[nodiscard]] std::expected<VkShaderModule, ShaderLoadError>
load_shader(const std::filesystem::path &path, VkDevice device, GFC::Logger::Instance *logger = nullptr);

}; // namespace GFC::Ren
