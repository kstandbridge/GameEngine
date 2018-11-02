#pragma once
#include "Engine/BaseState.h"

#include "GameState.h"

#include "Engine/Window.h"
#include "Map.h"

namespace Kengine {
	struct EventDetails;
}

class State_MapEditor : public Kengine::BaseState<GameState>
{
public:
	State_MapEditor(
		Kengine::FontManager* fontManager,
		Kengine::TextureManager* textureManager,
		Kengine::StateManager<GameState>* stateManager,
		Kengine::Window<GameState>* window)
		: BaseState(fontManager, textureManager, stateManager, window),
		m_map(window,this,textureManager)
	{
	}

	void OnCreate(Kengine::EventManager<GameState>* eventManager) override;
	void OnDestroy(Kengine::EventManager<GameState>* eventManager) override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& time) override;
	void Draw() override;

	void Close(Kengine::EventDetails* eventDetails);
	void MoveUp(Kengine::EventDetails* eventDetails);
	void MoveLeft(Kengine::EventDetails* eventDetails);
	void MoveDown(Kengine::EventDetails* eventDetails);
	void MoveRight(Kengine::EventDetails* eventDetails);

private:
	Map m_map;

	sf::Vector2f m_position;
};

