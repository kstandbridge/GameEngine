#include "State_MapEditor.h"

#include <iostream>

#include "Engine/EventManager.h"
#include "Engine/StateManager.h"


void State_MapEditor::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	std::cout << "MapEditor OnCreate..." << std::endl;

	m_map.LoadTiles("Resources/tiles.cfg");
	m_map.LoadMap("Resources/Map1.map");

	sf::Vector2u size = m_window->GetRenderWindow()->getSize();
	m_view.setSize(size.x, size.y);
	m_view.zoom(0.6f);
	m_position = m_map.GetStartPosition();
	m_view.setCenter(m_map.GetStartPosition());
	m_window->GetRenderWindow()->setView(m_view);

	eventManager->AddCallback(GameState::MAP_EDITOR, "Key_Escape", &State_MapEditor::Close, this);
	eventManager->AddCallback(GameState::MAP_EDITOR, "Player_MoveUp", &State_MapEditor::MoveUp, this);
	eventManager->AddCallback(GameState::MAP_EDITOR, "Player_MoveLeft", &State_MapEditor::MoveLeft, this);
	eventManager->AddCallback(GameState::MAP_EDITOR, "Player_MoveDown", &State_MapEditor::MoveDown, this);
	eventManager->AddCallback(GameState::MAP_EDITOR, "Player_MoveRight", &State_MapEditor::MoveRight, this);

}

void State_MapEditor::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	std::cout << "MapEditor OnDestroy..." << std::endl;
	eventManager->RemoveCallback(GameState::MAP_EDITOR, "Key_Escape");
	eventManager->RemoveCallback(GameState::MAP_EDITOR, "Player_MoveUp");
	eventManager->RemoveCallback(GameState::MAP_EDITOR, "Player_MoveLeft");
	eventManager->RemoveCallback(GameState::MAP_EDITOR, "Player_MoveDown");
	eventManager->RemoveCallback(GameState::MAP_EDITOR, "Player_MoveRight");
}

void State_MapEditor::Activate()
{
	std::cout << "MapEditor Activate..." << std::endl;
}

void State_MapEditor::Deactivate()
{
	std::cout << "MapEditor Deactivate..." << std::endl;
}

void State_MapEditor::Update(const sf::Time& time)
{
	m_view.setCenter(m_position);
	m_window->GetRenderWindow()->setView(m_view);

	sf::FloatRect viewSpace = m_window->GetViewSpace();
	if(viewSpace.left <= 0)
	{
		m_view.setCenter(viewSpace.width / 2,m_view.getCenter().y);
		m_window->GetRenderWindow()->setView(m_view);
	} 
	else if (viewSpace.left + viewSpace.width > (m_map.GetMapSize().x + 1) * Sheet::Tile_Size)
	{
		m_view.setCenter(((m_map.GetMapSize().x + 1) * Sheet::Tile_Size) - (viewSpace.width / 2), m_view.getCenter().y);
		m_window->GetRenderWindow()->setView(m_view);
	}

	m_map.Update(time.asSeconds());
}

void State_MapEditor::Draw()
{
	m_map.Draw();
}

void State_MapEditor::Close(Kengine::EventDetails* eventDetails)
{
	m_stateManager->SwitchTo(GameState::DEBUG_MENU);
	m_stateManager->Remove(GameState::MAP_EDITOR);
}

void State_MapEditor::MoveUp(Kengine::EventDetails* eventDetails)
{
	m_position.y--;
}

void State_MapEditor::MoveLeft(Kengine::EventDetails* eventDetails)
{
	m_position.x--;
}

void State_MapEditor::MoveDown(Kengine::EventDetails* eventDetails)
{
	m_position.y++;
}

void State_MapEditor::MoveRight(Kengine::EventDetails* eventDetails)
{
	m_position.x++;
}
