#pragma once

// Forward
namespace GFC
{
namespace EasyWindow
{
class Instance;
}
}; // namespace GFC
//

namespace GFC::Event
{
void start_loop(bool &finished, GFC::EasyWindow::Instance &window);
}
