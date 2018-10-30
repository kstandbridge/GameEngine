#pragma once
#include <SFML/Graphics.hpp>

namespace Kengine
{

	template<typename ID>
	class EventManager;

	template<typename ID>
	class Window
	{
		int m_width;
		int m_height;
		int m_depth;
		sf::RenderWindow m_window;

		bool m_isOpen;

		EventManager<ID>* m_eventManager;

	public:
		Window(EventManager<ID>* eventManager)
			: m_eventManager(eventManager)
		{
		}

		~Window()
		{
			m_window.close();
		}

		void Init(
			const std::string& title,
			const unsigned int width,
			const unsigned int height,
			const unsigned int depth = 32)
		{
			m_width = width;
			m_height = height;
			m_depth = depth;
			m_isOpen = true;
			m_window.create({ width, height, depth }, title);
		}

		void Update()
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

		bool IsOpen() const
		{
			return m_isOpen;
		}

		int GetWidth() const
		{
			return m_width;
		}

		int GetHeight() const
		{
			return m_height;
		}

		sf::RenderWindow* GetRenderWindow()
		{
			return &m_window;
		}
	};


}

