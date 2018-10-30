#pragma once

#include "Engine/BaseState.h"
#include "Engine/EventManager.h"

#include "GameState.h"



class DebugMenu_State : public Kengine::BaseState<GameState>
{
public:
	DebugMenu_State(Kengine::StateManager<GameState>* stateManager, Kengine::Window<GameState>* window);

	void OnCreate(Kengine::EventManager<GameState>* eventManager) override;
	void OnDestroy(Kengine::EventManager<GameState>* eventManager) override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& time) override;
	void Draw() override;

	void Escape(Kengine::EventDetails* eventDetails);

private:
	sf::RectangleShape m_rectangle;
};

