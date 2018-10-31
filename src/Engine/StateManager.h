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

	class FontManager;
	class TextureManager;

	template<typename ID>
	class StateManager
	{
		FontManager* m_fontManager;
		TextureManager* m_textureManager;
		BaseState<ID>* m_currentState{};
		EventManager<ID>* m_eventManager;
		Window<ID>* m_window;

		std::unordered_map<ID, std::function<BaseState<ID>*(void)>> m_stateFactory;
		std::vector<std::pair<ID, BaseState<ID>*>> m_states;
		std::vector<ID> m_toRemove;

		void CreateState(const ID& type)
		{
			auto newState = m_stateFactory.find(type);
			if (newState == m_stateFactory.end()) return;
			BaseState<ID>* state = newState->second();
			state->SetView(m_window->GetRenderWindow()->getDefaultView());
			m_states.emplace_back(type, state);
			state->OnCreate(m_eventManager);
		}

		void ProcessRemoveStates()
		{
			while (m_toRemove.begin() != m_toRemove.end())
			{
				RemoveState(*m_toRemove.begin());
				m_toRemove.erase(m_toRemove.begin());
			}
		}

		void RemoveState(ID id)
		{
			for (auto it = m_states.begin(); it != m_states.end(); ++it)
			{
				if (it->first == id)
				{
					it->second->OnDestroy(m_eventManager);
					delete it->second;
					m_states.erase(it);
					return;
				}
			}
		}

	public:

		StateManager(
			FontManager* fontManager,
			TextureManager* textureManager,
			EventManager<ID>* eventManager,
			Window<ID>* window)
			: m_fontManager(fontManager),
			m_textureManager(textureManager),
			m_eventManager(eventManager),
			m_window(window)
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
				return new T(
					m_fontManager,
					m_textureManager,
					this,
					m_window);
			};
		}

		void SwitchTo(ID id)
		{
			m_eventManager->SetCurrentState(id);
			for (auto it = m_states.begin(); it != m_states.end(); ++it)
			{
				if (it->first == id)
				{
					m_states.back().second->Deactivate();
					ID tmp_type = it->first;
					BaseState<ID>* tmp_state = it->second;
					m_states.erase(it);
					m_states.emplace_back(tmp_type, tmp_state);
					tmp_state->Activate();
					m_window->GetRenderWindow()->setView(tmp_state->GetView());
					return;
				}
			}

			// State with type wasn't found
			if (!m_states.empty()) m_states.back().second->Deactivate();
			CreateState(id);
			m_states.back().second->Activate();
			m_window->GetRenderWindow()->setView(m_states.back().second->GetView());
		}

		void Draw()
		{
			if (m_states.empty()) return;
			if (m_states.back().second->IsTransparent() && m_states.size() > 1)
			{
				auto it = m_states.end();
				while (it != m_states.begin())
				{
					if (it != m_states.end())
					{
						if (!it->second->IsTransparent())
						{
							break;
						}
					}
					--it;
				}
				for (; it != m_states.end(); ++it)
				{
					m_window->GetRenderWindow()->setView(it->second->GetView());
					it->second->Draw();
				}
			}
			else
			{
				m_states.back().second->Draw();
			}
		}

		void Update(const sf::Time time)
		{
			if (m_states.empty()) return;
			if (m_states.back().second->IsTranscendent() && m_states.size() > 1)
			{
				auto it = m_states.end();
				while (it != m_states.begin())
				{
					if (it != m_states.end())
					{
						if (!it->second->IsTranscendent())
						{
							break;
						}
					}
					--it;
				}
				for (; it != m_states.end(); ++it)
				{
					it->second->Update(time);
				}
			}
			else
			{
				m_states.back().second->Update(time);
			}
			ProcessRemoveStates();
		}

		void Remove(const ID& type)
		{
			m_toRemove.push_back(type);
		}

	};
}
