#include "Window.h"

namespace Kengine
{
	Window::Window(
		const std::string& title, 
		const unsigned int width, 
		const unsigned int height, 
		const unsigned int depth)
	: m_width(width),
	  m_height(height),
	  m_depth(depth),
	  m_isOpen(true)
	{
		m_window.create({width, height, depth}, title);
	}

	Window::~Window()
	{
		m_window.close();
	}

	void Window::HandleEvents()
	{
		sf::Event event{};
		while(m_window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				m_isOpen = false;
			}
		}
	}

	bool Window::IsOpen() const
	{
		return m_isOpen;
	}
}
