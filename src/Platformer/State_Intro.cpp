#include "State_Intro.h"
#include "Engine/Window.h"


State_Intro::State_Intro(Kengine::StateManager<GameState>* stateManager, Kengine::Window<GameState>* window)
	: BaseState<GameState>(stateManager, window), m_timePassed(0)
{
}

void State_Intro::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	if (!m_texture.loadFromFile("Resources/intro.png")) throw std::exception("Failed to load Resources/intro.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_window->GetSize().x / 2.0f, 0);
	m_sprite.setOrigin(m_texture.getSize().x / 2.0f, m_texture.getSize().y / 2.0f);
	eventManager->AddCallback(GameState::TITLE, "Intro_Continue", &State_Intro::Continue, this);

	if (!m_font.loadFromFile("Resources/arial.ttf")) throw std::exception("Unable to load font media/arial.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(15);
	m_text.setString("Press space to continue...");
	const auto rect = m_text.getLocalBounds();
	m_text.setOrigin(
		rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
	m_text.setPosition(
		m_window->GetSize().x / 2.0f, 
		(m_window->GetSize().y / 2.0f) + m_texture.getSize().y);
}

void State_Intro::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	eventManager->RemoveCallback(GameState::TITLE, "Into_Continue");
}

void State_Intro::Activate()
{
}

void State_Intro::Deactivate()
{
}

void State_Intro::Update(const sf::Time& time)
{
	if (m_timePassed < ANIMATION_TIME)
	{
		m_timePassed += time.asSeconds();
		m_sprite.setPosition(
			m_sprite.getPosition().x, 
			(m_window->GetSize().y / 2.0f) * (m_timePassed / ANIMATION_TIME));
	}
}

void State_Intro::Draw()
{
	m_window->GetRenderWindow()->draw(m_sprite);

	if (m_timePassed > ANIMATION_TIME)
	{
		m_window->GetRenderWindow()->draw(m_text);
	}
}

void State_Intro::Continue(Kengine::EventDetails* eventDetails)
{
	if (m_timePassed > ANIMATION_TIME)
	{
		m_window->Close();
	}
}
