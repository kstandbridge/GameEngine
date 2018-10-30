#include "DebugMenu_State.h"
#include "Engine/Window.h"

DebugMenu_State::DebugMenu_State(
	Kengine::StateManager<GameState>* stateManager, 
	Kengine::Window<GameState>* window)
	: BaseState(stateManager, window)
{
}

void DebugMenu_State::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	m_rectangle.setFillColor({255, 0, 0, 255});
	m_rectangle.setSize({ m_window->GetWidth() / 2.0f, m_window->GetHeight() / 2.0f});
	m_rectangle.setOrigin(m_rectangle.getSize() / 2.0f);
	m_rectangle.setPosition({ m_window->GetWidth() / 2.0f, m_window->GetHeight() / 2.0f});

	eventManager->AddCallback(GameState::DEBUG_MENU, "Key_Escape", &DebugMenu_State::Escape, this);
}

void DebugMenu_State::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	eventManager->RemoveCallback(GameState::DEBUG_MENU, "Key_Escape");
}

void DebugMenu_State::Activate()
{
}

void DebugMenu_State::Deactivate()
{
}

void DebugMenu_State::Update(const sf::Time& time)
{
}

void DebugMenu_State::Draw()
{
	m_window->GetRenderWindow()->draw(m_rectangle);
}

void DebugMenu_State::Escape(Kengine::EventDetails* eventDetails)
{
	std::cout << "Holy shit it worked!" << std::endl;
}
