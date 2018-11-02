#pragma once
#include <SFML/Graphics.hpp>

namespace Kengine
{

	template<typename ID>
	class EventManager;

	template<typename ID>
	class Window
	{
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

		void Close()
		{
			m_isOpen = false;
		}

		void Init(
			const std::string& title,
			const unsigned int width,
			const unsigned int height,
			const unsigned int depth = 32)
		{
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

		sf::Vector2u GetSize() const
		{
			return m_window.getSize();
		}

		sf::RenderWindow* GetRenderWindow()
		{
			return &m_window;
		}

		sf::FloatRect GetViewSpace()
		{
			// Gets the top left corner of the view.
			sf::Vector2f viewCenter = m_window.getView().getCenter();
			sf::Vector2f viewSize = m_window.getView().getSize();
			sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
			sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
			return viewSpace;
		}
	};


}

