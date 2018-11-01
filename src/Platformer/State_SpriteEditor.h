#pragma once
#include "Engine/BaseState.h"
#include "Engine/Sprite/SpriteSheet.h"

#include "GameState.h"


namespace Kengine {
	struct EventDetails;
}

class State_SpriteEditor : public Kengine::BaseState<GameState>
{
	Kengine::SpriteSheet m_spriteSheet;

public:
	State_SpriteEditor(
		Kengine::FontManager* fontManager,
		Kengine::TextureManager* textureManager,
		Kengine::StateManager<GameState>* stateManager,
		Kengine::Window<GameState>* window)
		: BaseState(fontManager, textureManager, stateManager, window),
		  m_spriteSheet(textureManager)
	{
	}

	void OnCreate(Kengine::EventManager<GameState>* eventManager) override;
	void OnDestroy(Kengine::EventManager<GameState>* eventManager) override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& time) override;
	void Draw() override;

	void Close(Kengine::EventDetails* eventDetails);

	void MoveLeft(Kengine::EventDetails* eventDetails);
	void MoveRight(Kengine::EventDetails* eventDetails);
	void Attack(Kengine::EventDetails* eventDetails);
	void Jump(Kengine::EventDetails* eventDetails);
};
