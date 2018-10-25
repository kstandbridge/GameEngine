#include "DebugMenu_State.h"
#include "Engine/StateManager.h"
#include "Engine/Window.h"

DebugMenu_State::DebugMenu_State(Kengine::StateManager* stateManager, Kengine::Window* window)
	: BaseState(stateManager, window)
{
}

void DebugMenu_State::OnCreate()
{
	m_rectangle.setFillColor({255, 0, 0, 255});
	m_rectangle.setSize({ m_window->GetWidth() / 2.0f, m_window->GetHeight() / 2.0f});
	m_rectangle.setOrigin(m_rectangle.getSize() / 2.0f);
	m_rectangle.setPosition({ m_window->GetWidth() / 2.0f, m_window->GetHeight() / 2.0f});
}

void DebugMenu_State::OnDestroy()
{
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
