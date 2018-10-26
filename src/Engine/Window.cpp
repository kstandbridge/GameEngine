#include "Window.h"
#include "EventManager.h"

namespace Kengine
{
	Window::Window(EventManager* eventManager)
		: m_eventManager(eventManager)
	{
	}

	Window::~Window()
	{
		m_window.close();
	}

	void Window::Init(
		const std::string& title,
		const unsigned int width,
		const unsigned int height,
		const unsigned int depth)
	{
		m_width = width;
		m_height = height;
		m_depth = depth;
		m_isOpen = true;
		m_window.create({ width, height, depth }, title);
	}

	void Window::Update()
	{
		sf::Event event{};
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_isOpen = false;
			}
			m_eventManager->HandleEvent(event);
		}
		m_eventManager->Update();
	}

	bool Window::IsOpen() const
	{
		return m_isOpen;
	}

	int Window::GetWidth() const
	{
		return m_width;
	}

	int Window::GetHeight() const
	{
		return m_height;
	}

	sf::RenderWindow* Window::GetRenderWindow()
	{
		return &m_window;
	}
}
