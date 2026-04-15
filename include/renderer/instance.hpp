#pragma once


namespace GFC
{
namespace Logger
{
class Instance;
}
namespace EasyWindow
{
class Instance;
}
} // namespace GFC

namespace GFC::Ren
{
void init(const EasyWindow::Instance &window, Logger::Instance *logger = nullptr);


} // namespace GFC::Ren
