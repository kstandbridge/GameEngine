#include "State_Paused.h"
#include "Engine/FontManager.h"
#include "Engine/StateManager.h"
#include "Engine/Window.h"

void State_Paused::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	SetTransparent(true);
	m_fontManager->RequireResource("arial");

	m_text.setFont(*m_fontManager->GetResource("arial"));
	m_text.setString({"PAUSED"});
	m_text.setCharacterSize(14);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u wndSize = m_window->GetSize();

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(wndSize.x / 2.0f, wndSize.y / 2.f);

	m_rectangle.setSize(sf::Vector2f(wndSize));
	m_rectangle.setPosition(0, 0);
	m_rectangle.setFillColor(sf::Color(0, 0, 0, 150));

	eventManager->AddCallback(GameState::PAUSED, "Game_Pause", &State_Paused::Continue, this);
}

void State_Paused::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	m_fontManager->ReleaseResource("arial");

	eventManager->RemoveCallback(GameState::PAUSED, "Game_Pause");
}

void State_Paused::Activate()
{
}

void State_Paused::Deactivate()
{
}

void State_Paused::Update(const sf::Time& time)
{
}

void State_Paused::Draw()
{
	m_window->GetRenderWindow()->draw(m_rectangle);
	m_window->GetRenderWindow()->draw(m_text);
}

void State_Paused::Continue(Kengine::EventDetails* eventDetails)
{
	m_stateManager->SwitchTo(GameState::GAME);
}
