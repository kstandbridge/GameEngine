#include "State_Game.h"
#include "Engine/StateManager.h"
#include "Engine/TextureManager.h"
#include "Engine/Window.h"

void State_Game::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	m_textureManager->RequireResource("Mushroom");
	sf::Texture* texture = m_textureManager->GetResource("Mushroom");
	m_spriteSize = texture->getSize();
	m_sprite.setTexture(*texture);
	m_direction = sf::Vector2f(400.0f, 400.0f);
	
	eventManager->AddCallback(GameState::GAME, "Game_Pause", &State_Game::Pause, this);
	eventManager->AddCallback(GameState::GAME, "Game_Inventory", &State_Game::Bag, this);
}

void State_Game::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	m_textureManager->RequireResource("Mushroom");
	eventManager->RemoveCallback(GameState::GAME, "Game_Pause");
	eventManager->RemoveCallback(GameState::GAME, "Game_Inventory");
}

void State_Game::Activate()
{
}

void State_Game::Deactivate()
{
}

void State_Game::Update(const sf::Time& time)
{
	auto pos = m_sprite.getPosition();
	auto wndSize = m_window->GetSize();

	if ((pos.x + m_spriteSize.x) > wndSize.x ||
		pos.x < 0 && m_direction.x < 0)
	{
		m_direction.x = -m_direction.x;
	}

	if ((pos.y + m_spriteSize.y) > wndSize.y ||
		pos.y < 0 && m_direction.y < 0)
	{
		m_direction.y = -m_direction.y;
	}

	m_sprite.setPosition(
		pos.x + m_direction.x * time.asSeconds(),
		pos.y + m_direction.y * time.asSeconds());
}

void State_Game::Draw()
{
	m_window->GetRenderWindow()->draw(m_sprite);
}

void State_Game::Pause(Kengine::EventDetails* eventDetails)
{
	m_stateManager->SwitchTo(GameState::PAUSED);
}

void State_Game::Bag(Kengine::EventDetails* eventDetails)
{
	m_stateManager->SwitchTo(GameState::INVENTORY);
}
