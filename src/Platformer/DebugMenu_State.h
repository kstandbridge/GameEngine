#pragma once

#include "Engine/BaseState.h"
#include "Engine/EventManager.h"


class DebugMenu_State : public Kengine::BaseState
{
public:
	DebugMenu_State(Kengine::StateManager* stateManager, Kengine::Window* window);

	void OnCreate(Kengine::EventManager* eventManager) override;
	void OnDestroy(Kengine::EventManager* eventManager) override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& time) override;
	void Draw() override;

	void Escape(Kengine::EventDetails* eventDetails);

private:
	sf::RectangleShape m_rectangle;
};

