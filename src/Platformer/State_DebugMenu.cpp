#include "State_DebugMenu.h"
#include "Engine/Window.h"
#include "Engine/StateManager.h"
#include "Engine/FontManager.h"

void State_DebugMenu::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	m_fontManager->RequireResource("arial");
	m_buttonSize = sf::Vector2f(300.0f, 32.0f);
	m_buttonPos = sf::Vector2f(m_window->GetSize().x / 2.0f, m_window->GetSize().y / 2.0f - (BUTTON_COUNT * m_buttonSize.y / 2.0f));

	std::string str[5];
	str[0] = "Launch Game";
	str[1] = "Sprite Editor";
	str[2] = "bar";
	str[3] = "bas";
	str[4] = "Exit";

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

	eventManager->AddCallback(GameState::DEBUG_MENU, "Key_Escape", &State_DebugMenu::Escape, this);
	eventManager->AddCallback(GameState::DEBUG_MENU, "Mouse_Left", &State_DebugMenu::MouseClick, this);
}

void State_DebugMenu::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	m_fontManager->ReleaseResource("arial");
	eventManager->RemoveCallback(GameState::DEBUG_MENU, "Key_Escape");
	eventManager->RemoveCallback(GameState::DEBUG_MENU, "Mouse_Left");
}

void State_DebugMenu::Activate()
{
}

void State_DebugMenu::Deactivate()
{
}

void State_DebugMenu::Update(const sf::Time& time)
{

}

void State_DebugMenu::Draw()
{
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		m_window->GetRenderWindow()->draw(m_rects[i]);
		m_window->GetRenderWindow()->draw(m_labels[i]);
	}
}

void State_DebugMenu::Escape(Kengine::EventDetails* eventDetails)
{
	m_window->Close();
}

void State_DebugMenu::MouseClick(Kengine::EventDetails* eventDetails)
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
				m_stateManager->Remove(GameState::DEBUG_MENU);
				break;
			case 1:
				m_stateManager->SwitchTo(GameState::SPRITE_EDITOR);
				m_stateManager->Remove(GameState::DEBUG_MENU);
				break;
			case 2:
				std::cout << "Do something for bar" << std::endl;
				break;
			case 3:
				std::cout << "Do something for bas" << std::endl;
				break;
			case 4:
				m_window->Close();
				break;
			default: 
				throw std::exception("Found click outside of button count");
			}
		}
	}
}
