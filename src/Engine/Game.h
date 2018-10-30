#pragma once
#include "EventManager.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "Window.h"

namespace Kengine
{
	template<typename ID>
	class Game
	{
		sf::Clock m_clock;
		sf::Time m_deltaTime;
		TextureManager* m_textureManager;
		EventManager<ID>* m_eventManager;
		Window<ID>* m_window;
		StateManager<ID>* m_stateManager;
	public:
		Game()
		{
			m_textureManager = new TextureManager("Resources/textures.cfg");
			m_eventManager = new EventManager<ID>("Resources/keys.cfg");
			m_window = new Window<ID>(m_eventManager);
			m_stateManager = new StateManager<ID>(m_textureManager, m_eventManager, m_window);
		}

		~Game()
		{
			delete m_stateManager;
			delete m_window;
			delete m_eventManager;
			delete m_textureManager;
		}

		bool IsRunning()
		{
			return m_window->IsOpen();
		}

		void Init(std::string title, int width, int height, ID defaultState)
		{
			m_window->Init(title, width, height);
			m_stateManager->SwitchTo(defaultState);
		}

		template<class T>
		void RegisterState(ID id)
		{
			m_stateManager->template RegisterState<T>(id);
		}

		void Update()
		{
			m_window->Update();
			m_stateManager->Update(m_deltaTime);
			m_deltaTime = m_clock.restart();
		}

		void Draw()
		{
			m_window->GetRenderWindow()->clear(sf::Color(64, 0, 64, 255));

			m_stateManager->Draw();

			m_window->GetRenderWindow()->display();
		}
	};
}
