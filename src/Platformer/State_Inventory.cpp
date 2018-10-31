#include "State_Inventory.h"
#include "Engine/FontManager.h"
#include "Engine/StateManager.h"
#include "Engine/Window.h"

void State_Inventory::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	SetTransparent(true);
	SetTranscendent(true);
	m_fontManager->RequireResource("arial");

	m_text.setFont(*m_fontManager->GetResource("arial"));
	m_text.setString({ "INVENTORY OVERLAY" });
	m_text.setCharacterSize(14);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u wndSize = m_window->GetSize();

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(wndSize.x / 2.0f, wndSize.y / 2.f);

	m_rectangle.setSize({ wndSize.x / 2.0f, wndSize.y / 2.0f });
	m_rectangle.setOrigin(m_rectangle.getSize().x / 2.0f, m_rectangle.getSize().y / 2.0f);
	m_rectangle.setPosition(wndSize.x / 2.0f, wndSize.y / 2.0f);
	m_rectangle.setFillColor(sf::Color(0, 0, 0, 150));

	eventManager->AddCallback(GameState::INVENTORY, "Game_Inventory", &State_Inventory::Close, this);
}

void State_Inventory::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	m_fontManager->ReleaseResource("arial");

	eventManager->RemoveCallback(GameState::INVENTORY, "Game_Inventory");
}

void State_Inventory::Activate()
{
}

void State_Inventory::Deactivate()
{
}

void State_Inventory::Update(const sf::Time& time)
{
}

void State_Inventory::Draw()
{
	m_window->GetRenderWindow()->draw(m_rectangle);
	m_window->GetRenderWindow()->draw(m_text);
}

void State_Inventory::Close(Kengine::EventDetails* eventDetails)
{
	m_stateManager->SwitchTo(GameState::GAME);
}
