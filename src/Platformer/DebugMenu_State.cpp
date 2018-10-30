#include "DebugMenu_State.h"
#include "Engine/Window.h"
#include "Engine/StateManager.h"
#include "Engine/FontManager.h"

void DebugMenu_State::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	m_fontManager->RequireResource("arial");
	m_buttonSize = sf::Vector2f(300.0f, 32.0f);
	m_buttonPos = sf::Vector2f(m_window->GetSize().x / 2.0f, m_window->GetSize().y / 2.0f - (BUTTON_COUNT * m_buttonSize.y / 2.0f));

	std::string str[3];
	str[0] = "Launch Game";
	str[1] = "bar";
	str[2] = "Exit";

	for (size_t i = 0; i < BUTTON_COUNT; i++)
	{
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setOrigin(m_buttonSize / 2.0f);
		m_rects[i].setPosition(
			m_buttonPos.x,
			m_buttonPos.y + (i * m_buttonSize.y) + (m_buttonPadding * i));
		m_rects[i].setFillColor({ 255, 0, 0, 255 });

		m_labels[i].setFont(*m_fontManager->GetResource("arial"));
		m_labels[i].setCharacterSize(12);
		m_labels[i].setString(str[i]);
		const auto rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(
			rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);
		m_labels[i].setPosition(m_rects[i].getPosition());
	}

	eventManager->AddCallback(GameState::DEBUG_MENU, "Key_Escape", &DebugMenu_State::Escape, this);
	eventManager->AddCallback(GameState::DEBUG_MENU, "Mouse_Left", &DebugMenu_State::MouseClick, this);
}

void DebugMenu_State::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	m_fontManager->ReleaseResource("arial");
	eventManager->RemoveCallback(GameState::DEBUG_MENU, "Key_Escape");
	eventManager->RemoveCallback(GameState::DEBUG_MENU, "Mouse_Left");
}

void DebugMenu_State::Activate()
{
}

void DebugMenu_State::Deactivate()
{
}

void DebugMenu_State::Update(const sf::Time& time)
{

}

void DebugMenu_State::Draw()
{
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		m_window->GetRenderWindow()->draw(m_rects[i]);
		m_window->GetRenderWindow()->draw(m_labels[i]);
	}
}

void DebugMenu_State::Escape(Kengine::EventDetails* eventDetails)
{
	m_window->Close();
}

void DebugMenu_State::MouseClick(Kengine::EventDetails* eventDetails)
{
	const auto mousePos = eventDetails->m_mouse;

	const auto halfX = m_buttonSize.x / 2.0f;
	const auto halfY = m_buttonSize.y / 2.0f;
	for (size_t i = 0; i < BUTTON_COUNT; ++i) 
	{
		if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			switch (i)
			{
			case 0:
				m_stateManager->SwitchTo(GameState::TITLE);
				m_stateManager->RemoveState(GameState::DEBUG_MENU);
				break;
			case 1:
				std::cout << "Do something for one" << std::endl;
				break;
			case 2:
				m_window->Close();
				break;
			default: 
				throw std::exception("Found click outside of button count");
			}
		}
	}
}
