#pragma once
#include <SFML/Graphics.hpp>

namespace Kengine
{
	class Window
	{
		int m_width;
		int m_height;
		int m_depth;
		sf::RenderWindow m_window;

		bool m_isOpen;

	public:
		Window(
			const std::string& title, 
			const unsigned int width, 
			const unsigned int height, 
			const unsigned int depth = 32);
		~Window();

		void HandleEvents();

		bool IsOpen() const;

		int GetWidth() const;
		int GetHeight() const;

		sf::RenderWindow* GetRenderWindow();
	};


}

