#include "State_MapEditor.h"

#include <iostream>

#include "Engine/EventManager.h"
#include "Engine/StateManager.h"


void State_MapEditor::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	std::cout << "MapEditor OnCreate..." << std::endl;

	eventManager->AddCallback(GameState::MAP_EDITOR, "Key_Escape", &State_MapEditor::Close, this);
}

void State_MapEditor::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	std::cout << "MapEditor OnDestroy..." << std::endl;
	eventManager->RemoveCallback(GameState::MAP_EDITOR, "Key_Escape");
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
}

void State_MapEditor::Draw()
{
}

void State_MapEditor::Close(Kengine::EventDetails* eventDetails)
{
	m_stateManager->SwitchTo(GameState::DEBUG_MENU);
	m_stateManager->Remove(GameState::MAP_EDITOR);
}
