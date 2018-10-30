#pragma once

#include "Engine/BaseState.h"
#include "Engine/EventManager.h"

#include "GameState.h"

class DebugMenu_State : public Kengine::BaseState<GameState>
{
	const static size_t BUTTON_COUNT = 3;

	sf::RectangleShape m_rects[BUTTON_COUNT];
	sf::Text m_labels[BUTTON_COUNT];

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	size_t m_buttonPadding;
public:
	DebugMenu_State(
		Kengine::FontManager* fontManager,
		Kengine::TextureManager* textureManager,
		Kengine::StateManager<GameState>* stateManager,
		Kengine::Window<GameState>* window)
		: BaseState(fontManager, textureManager, stateManager, window), 
		  m_buttonPadding(10)
	{
	}

	void OnCreate(Kengine::EventManager<GameState>* eventManager) override;
	void OnDestroy(Kengine::EventManager<GameState>* eventManager) override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& time) override;
	void Draw() override;

	void Escape(Kengine::EventDetails* eventDetails);
	void MouseClick(Kengine::EventDetails* eventDetails);


};

