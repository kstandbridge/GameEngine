#pragma once
#include "GameState.h"
#include "Engine/BaseState.h"
#include "Engine/EventManager.h"


class State_Game : public Kengine::BaseState<GameState>
{
	sf::Sprite m_sprite;
	sf::Vector2u m_spriteSize;
	sf::Vector2f m_direction;
public:
	State_Game(
		Kengine::FontManager* fontManager,
		Kengine::TextureManager* textureManager,
		Kengine::StateManager<GameState>* stateManager,
		Kengine::Window<GameState>* window)
		: BaseState<GameState>(fontManager, textureManager, stateManager, window)
	{
	};

	void OnCreate(Kengine::EventManager<GameState>* eventManager) override;
	void OnDestroy(Kengine::EventManager<GameState>* eventManager) override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& time) override;
	void Draw() override;

	void Pause(Kengine::EventDetails* eventDetails);
};

