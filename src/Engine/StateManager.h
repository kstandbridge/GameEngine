#pragma once
#include <unordered_map>
#include <functional>

namespace Kengine
{
	class BaseState;
	class Window;

	class StateManager
	{
		BaseState* m_currentState {};
		Window* m_window;

		std::unordered_map<int, std::function<BaseState*(void)>> m_stateFactory;
		std::unordered_map<int, BaseState*> m_states;
	public:

		StateManager(Window* window);
		~StateManager();

		template<class T>
		void RegisterState(int id)
		{
			m_stateFactory[id] = [this]() -> BaseState*
			{
				return new T(this, m_window);
			};
		}

		void SwitchTo(unsigned int id);
		void Draw();
	};

}