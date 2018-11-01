#include "State_SpriteEditor.h"

#include "Engine/Window.h"

#include <iostream>
#include "Engine/EventManager.h"

void State_SpriteEditor::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	std::cout << "SpriteEditor OnCreate..." << std::endl;
	m_spriteSheet.LoadSheet("Resources/SpriteSheets/Player.sheet");
	m_spriteSheet.SetSpritePosition({ 
		m_window->GetSize().x / 2.0f, 
		m_window->GetSize().y / 2.0f });

	eventManager->AddCallback(GameState::SPRITE_EDITOR, "Player_MoveLeft", &State_SpriteEditor::MoveLeft, this);
	eventManager->AddCallback(GameState::SPRITE_EDITOR, "Player_MoveRight", &State_SpriteEditor::MoveRight, this);
	eventManager->AddCallback(GameState::SPRITE_EDITOR, "Player_Jump", &State_SpriteEditor::Jump, this);
	eventManager->AddCallback(GameState::SPRITE_EDITOR, "Player_Attack", &State_SpriteEditor::Attack, this);
}

void State_SpriteEditor::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	std::cout << "SpriteEditor OnDestroy..." << std::endl;
	eventManager->RemoveCallback(GameState::SPRITE_EDITOR, "Player_MoveLeft");
	eventManager->RemoveCallback(GameState::SPRITE_EDITOR, "Player_MoveRight");
	eventManager->RemoveCallback(GameState::SPRITE_EDITOR, "Player_Jump");
	eventManager->RemoveCallback(GameState::SPRITE_EDITOR, "Player_Attack");
}

void State_SpriteEditor::Activate()
{
	std::cout << "SpriteEditor Activate..." << std::endl;
}

void State_SpriteEditor::Deactivate()
{
	std::cout << "SpriteEditor Deactivate..." << std::endl;
}

void State_SpriteEditor::Update(const sf::Time& time)
{
	m_spriteSheet.Update(time.asSeconds());
}

void State_SpriteEditor::Draw()
{
	m_spriteSheet.Draw(m_window->GetRenderWindow());
}

void State_SpriteEditor::MoveLeft(Kengine::EventDetails* eventDetails)
{
	m_spriteSheet.SetDirection(Kengine::Direction::Left);
	m_spriteSheet.SetAnimation("Walk", true, true);
}

void State_SpriteEditor::MoveRight(Kengine::EventDetails* eventDetails)
{
	m_spriteSheet.SetDirection(Kengine::Direction::Right);
	m_spriteSheet.SetAnimation("Walk", true, true);
}

void State_SpriteEditor::Attack(Kengine::EventDetails* eventDetails)
{
	m_spriteSheet.SetAnimation("Attack", true, true);
}

void State_SpriteEditor::Jump(Kengine::EventDetails* eventDetails)
{
	m_spriteSheet.SetAnimation("Jump", true, true);
}
