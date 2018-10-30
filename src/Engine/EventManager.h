#pragma once
#include <string>

#include <functional>
#include <unordered_map>
#include <utility>

#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Kengine
{
	enum class EventType
	{
		KeyDown = sf::Event::KeyPressed,
		KeyUp = sf::Event::KeyReleased,
		MButtonDown = sf::Event::MouseButtonPressed,
		MButtonUp = sf::Event::MouseButtonReleased,
		MouseWheel = sf::Event::MouseWheelMoved,
		WindowResized = sf::Event::Resized,
		GainedFocus = sf::Event::GainedFocus,
		LostFocus = sf::Event::LostFocus,
		MouseEntered = sf::Event::MouseEntered,
		MouseLeft = sf::Event::MouseLeft,
		Closed = sf::Event::Closed,
		TextEntered = sf::Event::TextEntered,

		// Prevents clashing of identifiers
		Keyboard = sf::Event::Count + 1, Mouse, Joystick
		// anything past this point is higher then the max of sf::Event:EventType
	};

	// Stores a copy of the sf::Event.key.code
	struct EventInfo
	{
		EventInfo() { m_code = 0; }
		EventInfo(int code) { m_code = code; }

		union
		{
			int m_code;
		};
	};

	// Stores all of the sf::Event details
	struct EventDetails
	{
		EventDetails(std::string name)
			: m_name(std::move(name))
		{
			Clear();
		}

		std::string m_name;

		sf::Vector2i m_size;
		sf::Uint32 m_textEntered;
		sf::Vector2i m_mouse;
		int m_mouseWheelDelta;
		int m_keyCode;

		void Clear()
		{
			m_size = sf::Vector2i(0, 0);
			m_textEntered = 0;
			m_mouse = sf::Vector2i(0, 0);
			m_mouseWheelDelta = 0;
			m_keyCode = -1;
		}
	};

	struct Binding
	{
		Binding(const std::string& name)
			: m_name(name), c(0), m_details(name)
		{
		}

		void BindEvent(EventType type, EventInfo info = EventInfo())
		{
			m_events.emplace_back(type, info);
		}

		std::vector<std::pair<EventType, EventInfo>> m_events;
		std::string m_name;
		int c; // Count of events that are "happening"

		EventDetails m_details;
	};

	using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

	template<typename ID>
	class EventManager
	{
		std::unordered_map<std::string, Binding*> m_bindings;
		std::unordered_map<ID, CallbackContainer> m_callbacks;

		ID m_currentState;

		bool AddBinding(Binding* binding)
		{
			if (m_bindings.find(binding->m_name) != m_bindings.end()) return false;
			return m_bindings.emplace(binding->m_name, binding).second;
		}

	public:

		EventManager(const std::string& configPath)
			: m_currentState(ID(0))
		{
			LoadBindings(configPath);
		}

		~EventManager()
		{
			for (auto& itr : m_bindings)
			{
				delete itr.second;
				itr.second = nullptr;
			}
		}

		void SetCurrentState(ID state)
		{
			m_currentState = state;
		}

		void LoadBindings(const std::string& configPath)
		{
			std::string delimiter = ":";

			std::ifstream bindings;
			bindings.open(configPath);
			if (!bindings.is_open())
			{
				std::cerr << "! Failed loading keys.cfg" << std::endl;
				return;
			}

			std::string line;
			while (std::getline(bindings, line))
			{
				std::stringstream keystream(line);
				std::string callbackName;
				keystream >> callbackName;
				Binding* bind = new Binding(callbackName);
				while (!keystream.eof())
				{
					std::string keyVal;
					keystream >> keyVal;
					size_t start = 0;
					size_t end = keyVal.find(delimiter);
					if (end == std::string::npos)
					{
						delete bind;
						bind = nullptr;
						break;
					}
					EventType type = EventType(std::stoi(keyVal.substr(start, end - start)));
					int code = std::stoi(keyVal.substr(end + delimiter.length(),
						keyVal.find(delimiter, end + delimiter.length())));
					EventInfo eventInfo;
					eventInfo.m_code = code;

					bind->BindEvent(type, eventInfo);
				}

				if (!AddBinding(bind)) delete bind;
				bind = nullptr;
			}

			bindings.close();
		}

		template<class T>
		bool AddCallback(ID id, std::string name, void(T::*func)(EventDetails*), T* instance)
		{
			auto it = m_callbacks.emplace(id, CallbackContainer()).first;
			auto temp = std::bind(func, instance, std::placeholders::_1);
			return it->second.emplace(name, temp).second;
		}

		bool RemoveCallback(ID id, const std::string& name)
		{
			auto statePair = m_callbacks.find(id);
			if (statePair == m_callbacks.end()) return false;
			const auto callbackPair = statePair->second.find(name);
			if (callbackPair == statePair->second.end()) return false;
			statePair->second.erase(name);
			return true;
		}

		void HandleEvent(sf::Event& event)
		{
			for (auto& bindingIt : m_bindings)
			{
				Binding* binding = bindingIt.second;
				for (auto& eventIt : binding->m_events)
				{
					EventType sfmlEvent = static_cast<EventType>(event.type);
					if (eventIt.first != sfmlEvent) continue;
					if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
					{
						if (eventIt.second.m_code == event.key.code)
						{
							if (binding->m_details.m_keyCode != -1)
								binding->m_details.m_keyCode = eventIt.second.m_code;
							++(binding->c);
							break;
						}
					}
					else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
					{
						if (eventIt.second.m_code == event.mouseButton.button)
						{
							binding->m_details.m_mouse.x = event.mouseButton.x;
							binding->m_details.m_mouse.y = event.mouseButton.y;
							if (binding->m_details.m_keyCode != -1)
								binding->m_details.m_keyCode = eventIt.second.m_code;
							++(binding->c);
							break;
						}
					}
					else
					{
						if (sfmlEvent == EventType::MouseWheel)
						{
							binding->m_details.m_mouseWheelDelta = event.mouseWheel.delta;
						}
						else if (sfmlEvent == EventType::WindowResized)
						{
							binding->m_details.m_size.x = event.size.width;
							binding->m_details.m_size.y = event.size.height;
						}
						else if (sfmlEvent == EventType::TextEntered)
						{
							binding->m_details.m_textEntered = event.text.unicode;
						}
						++(binding->c);
					}
				}
			}
		}

		void Update()
		{
			// TODO ignore input without focus?
			// if (!m_hasFocus) return;
			for (auto& binding_itr : m_bindings)
			{
				Binding* binding = binding_itr.second;
				for (auto& event_itr : binding->m_events)
				{
					switch (event_itr.first)
					{
					case EventType::Keyboard:
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(event_itr.second.m_code)))
						{
							if (binding->m_details.m_keyCode != -1)
							{
								binding->m_details.m_keyCode = event_itr.second.m_code;
							}
							++(binding->c);
						}
						break;
					case EventType::Mouse:
						if (sf::Mouse::isButtonPressed(sf::Mouse::Button(event_itr.second.m_code)))
						{
							if (binding->m_details.m_keyCode != -1)
							{
								binding->m_details.m_keyCode = event_itr.second.m_code;
							}
							++(binding->c);
						}
						break;
					case EventType::Joystick:
						// Up for expansion.
						break;
					}
				}

				if (binding->m_events.size() == binding->c)
				{
					auto stateCallBacks = m_callbacks.find(m_currentState);
					auto otherCallbacks = m_callbacks.find(ID(0));

					if (stateCallBacks != m_callbacks.end())
					{
						auto callback_itr = stateCallBacks->second.find(binding->m_name);
						if (callback_itr != stateCallBacks->second.end())
						{
							callback_itr->second(&binding->m_details);
						}
					}

					if (otherCallbacks != m_callbacks.end())
					{
						auto callback_itr = otherCallbacks->second.find(binding->m_name);
						if (callback_itr != otherCallbacks->second.end())
						{
							callback_itr->second(&binding->m_details);
						}
					}
				}
				binding->c = 0;
				binding->m_details.Clear();
			}
		}
	};
}

