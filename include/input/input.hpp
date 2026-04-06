#pragma once

#include "scancodes.hpp"

namespace GFC::Input
{
bool is_key_being_pressed(const ScanCode keypress, const bool refresh = false) noexcept;
}
