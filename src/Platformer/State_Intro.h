#pragma once
#include "GameState.h"

#include "Engine/BaseState.h"
#include "Engine/EventManager.h"



class State_Intro : public Kengine::BaseState<GameState>
{
	sf::Sprite m_sprite;

	sf::Font m_font;
	sf::Text m_text;
	

	float m_timePassed;
	const float ANIMATION_TIME = 3.0f;

public:
	State_Intro(Kengine::TextureManager* textureManager, Kengine::StateManager<GameState>* stateManager, Kengine::Window<GameState>* window);

	void OnCreate(Kengine::EventManager<GameState>* eventManager) override;
	void OnDestroy(Kengine::EventManager<GameState>* eventManager) override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& time) override;
	void Draw() override;

	void Continue(Kengine::EventDetails* eventDetails);
};

