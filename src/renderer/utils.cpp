#include "renderer/utils.hpp"

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
