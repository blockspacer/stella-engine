#include "stella/core/application.h"
#include <iostream>

namespace stella
{
namespace core
{

  Application::Application(unsigned width, unsigned height, const std::string &title)
    : m_initial_width(width), m_initial_height(height), m_initial_title(title)
  {
    m_display.SetClearColor(0, 0, 0);
    srand(time(nullptr));
  }

  Application::~Application() { }

  void Application::run()
  {
    while (m_display.IsRunning()) {
      m_display.Clear();
      this->update(m_display.GetDT());
      m_display.Update();
    }
  }

  //void Application::update(const double dt)
  //{

  //}

  uint_fast32_t Application::width()
  {
    return m_display.GetWidth();
  }

  uint_fast32_t Application::height()
  {
    return m_display.GetHeight();
  }

} // namespace script
} // namespace st
