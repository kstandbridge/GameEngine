#pragma once
#include <unordered_map>
#include <functional>

namespace Kengine
{
	template<typename ID>
	class BaseState;

	template<typename ID>
	class EventManager;

	template<typename ID>
	class Window;

	template<typename ID>
	class StateManager
	{
		BaseState<ID>* m_currentState{};
		EventManager<ID>* m_eventManager;
		Window<ID>* m_window;

		std::unordered_map<ID, std::function<BaseState<ID>*(void)>> m_stateFactory;
		std::unordered_map<ID, BaseState<ID>*> m_states;
	public:

		StateManager(EventManager<ID>* eventManager, Window<ID>* window)
			: m_eventManager(eventManager), m_window(window)
		{
		}

		~StateManager()
		{
			for (auto& it : m_states)
			{
				it.second->OnDestroy(m_eventManager);
				delete it.second;
			}
		}

		template<class T>
		void RegisterState(ID id)
		{
			m_stateFactory[id] = [this]() -> BaseState<ID>*
			{
				return new T(this, m_window);
			};
		}

		void SwitchTo(ID id)
		{
			m_eventManager->SetCurrentState(id);

			auto stateIt = m_states.find(id);
			if (stateIt == m_states.end())
			{
				const auto factoryIt = m_stateFactory.find(id);
				if (factoryIt == m_stateFactory.end()) throw std::exception(std::string("Tried to switch to an unregistered state").c_str());
				auto state = factoryIt->second();
				state->OnCreate(m_eventManager);
				state->SetView(m_window->GetRenderWindow()->getDefaultView());
				m_states[id] = state;
				stateIt = m_states.find(id);
			}

			if (m_currentState != nullptr) m_currentState->Deactivate();

			m_currentState = stateIt->second;
			m_currentState->Activate();
			m_window->GetRenderWindow()->setView(m_currentState->GetView());
		}

		void Draw()
		{
			m_currentState->Draw();
		}
	};

}