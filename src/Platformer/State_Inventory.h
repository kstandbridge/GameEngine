#pragma once
#include "Engine/BaseState.h"
#include "GameState.h"
#include "Engine/EventManager.h"

class State_Inventory : public Kengine::BaseState<GameState>
{
	sf::Text m_text;
	sf::RectangleShape m_rectangle;

public:
	State_Inventory(
		Kengine::FontManager* fontManager,
		Kengine::TextureManager* textureManager,
		Kengine::StateManager<GameState>* stateManager,
		Kengine::Window<GameState>* window)
		: BaseState<GameState>(fontManager, textureManager, stateManager, window)
	{
	}

	void OnCreate(Kengine::EventManager<GameState>* eventManager) override;
	void OnDestroy(Kengine::EventManager<GameState>* eventManager) override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& time) override;
	void Draw() override;

	void Close(Kengine::EventDetails* eventDetails);
};

