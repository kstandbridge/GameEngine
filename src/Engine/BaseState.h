#pragma once
#include <SFML/Graphics.hpp>

namespace Kengine
{
	class StateManager;
	class EventManager;
	class Window;
	
	class BaseState
	{
		friend class StateManager;
	public:
		virtual void OnCreate(EventManager* eventManager) = 0;
		virtual void OnDestroy(EventManager* eventManager) = 0;
		
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		virtual void Update(const sf::Time& time) = 0;
		virtual void Draw() = 0;

		sf::View& GetView() { return m_view; }

	protected:
		BaseState(StateManager* stateManager, Window* window)
			: m_stateManager(stateManager), m_window(window)
		{
		}

		StateManager* m_stateManager;
		Window* m_window;
		sf::View m_view;
	};
	
}
