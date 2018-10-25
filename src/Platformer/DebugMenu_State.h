#pragma once

#include "Engine/BaseState.h"



class DebugMenu_State : public Kengine::BaseState
{
public:
	DebugMenu_State(Kengine::StateManager* stateManager, Kengine::Window* window);

	void OnCreate() override;
	void OnDestroy() override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& time) override;
	void Draw() override;

private:
	sf::RectangleShape m_rectangle;
};

