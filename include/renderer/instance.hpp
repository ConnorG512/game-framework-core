#pragma once 

namespace GFC {
  namespace Logger {class Instance;}
  namespace EasyWindow {class Instance;}
}

namespace GFC::Ren {
  void init(const EasyWindow::Instance& window, Logger::Instance* logger = nullptr);
}
