#include "StateManager.h"

#include "BaseState.h"
#include "EventManager.h"
#include "Window.h"

#include <string>

namespace Kengine
{
	StateManager::StateManager(EventManager* eventManager, Window* window)
		: m_eventManager(eventManager), m_window(window)
	{
	}

	StateManager::~StateManager()
	{
		for (auto& it : m_states)
		{
			it.second->OnDestroy(m_eventManager);
			delete it.second;
		}
	}

	void StateManager::SwitchTo(const unsigned id)
	{
		m_eventManager->m_currentState = id;

		auto stateIt = m_states.find(id);
		if (stateIt == m_states.end())
		{
			const auto factoryIt = m_stateFactory.find(id);
			if (factoryIt == m_stateFactory.end()) throw std::exception(std::string("Tried to switch to state Id: " + std::to_string(id) + ", which is not registered").c_str());
			auto state = factoryIt->second();
			state->OnCreate(m_eventManager);
			state->m_view = m_window->GetRenderWindow()->getDefaultView();
			m_states[id] = state;
			stateIt = m_states.find(id);
		}

		if (m_currentState != nullptr) m_currentState->Deactivate();

		m_currentState = stateIt->second;
		m_currentState->Activate();
		m_window->GetRenderWindow()->setView(m_currentState->GetView());
	}

	void StateManager::Draw()
	{
		m_currentState->Draw();
	}
}
