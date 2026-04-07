#include "filesystem/utils.hpp"

#include <cstdlib>
#include <cassert>

GFC::Filesystem::Directory GFC::Filesystem::find_path_from_env_var(const std::string &env_var,
                                                                   bool allow_custom_path) noexcept
{
  auto find_dir = [](const char *env_var = nullptr) -> const char *
  {
    const auto *dir{std::getenv(env_var)};
    return (dir != nullptr) ? dir : nullptr;
  };

  // Search the custom provided path before looking in system paths.
  if (allow_custom_path == true)
  {
    const auto final_dir = [&find_dir, env_var]() -> Directory
    {
      const auto *custom_game_dir{find_dir("GFC_GAME_DATA_DIR")};
      return {(custom_game_dir != nullptr) ? custom_game_dir : find_dir(env_var.c_str()),
              (custom_game_dir != nullptr) ? FoundDirType::CUSTOM : FoundDirType::SYSTEM};
    }();
    assert(final_dir.path != nullptr);
    return final_dir;
  }
  else
    return {find_dir(env_var.c_str()), FoundDirType::SYSTEM};
}
