#pragma once
#include <SFML/Graphics.hpp>

namespace Kengine
{

	class EventManager;

	class Window
	{
		int m_width;
		int m_height;
		int m_depth;
		sf::RenderWindow m_window;

		bool m_isOpen;

		EventManager* m_eventManager;

	public:
		Window(EventManager* eventManager);

		~Window();

		void Init(
			const std::string& title, 
			const unsigned int width, 
			const unsigned int height, 
			const unsigned int depth = 32);

		void Update();

		bool IsOpen() const;

		int GetWidth() const;
		int GetHeight() const;

		sf::RenderWindow* GetRenderWindow();
	};


}

