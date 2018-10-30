#pragma once
#include <SFML/Graphics.hpp>

namespace Kengine
{
	template<typename ID>
	class StateManager;

	template<typename ID>
	class EventManager;

	template<typename ID>
	class Window;

	template<typename ID>
	class BaseState
	{
	public:
		virtual void OnCreate(EventManager<ID>* eventManager) = 0;
		virtual void OnDestroy(EventManager<ID>* eventManager) = 0;
		
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		virtual void Update(const sf::Time& time) = 0;
		virtual void Draw() = 0;

		sf::View& GetView() { return m_view; }

		void SetView(sf::View view)
		{
			m_view = view;
		}

	protected:
		BaseState(StateManager<ID>* stateManager, Window<ID>* window)
			: m_stateManager(stateManager), m_window(window)
		{
		}

		StateManager<ID>* m_stateManager;
		Window<ID>* m_window;
		sf::View m_view;
	};
	
}
