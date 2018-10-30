#include "State_Intro.h"

#include "Engine/Window.h"
#include "Engine/TextureManager.h"


State_Intro::State_Intro(
	Kengine::TextureManager* textureManager, 
	Kengine::StateManager<GameState>* stateManager, 
	Kengine::Window<GameState>* window)
	: BaseState<GameState>(textureManager, stateManager, window), m_timePassed(0)
{
}

void State_Intro::OnCreate(Kengine::EventManager<GameState>* eventManager)
{
	
	m_textureManager->RequireResource("Intro");
	sf::Texture* texture = m_textureManager->GetResource("Intro");
	sf::Vector2u size = texture->getSize();

	m_sprite.setTexture(*texture);
	m_sprite.setPosition(m_window->GetSize().x / 2.0f, 0);
	m_sprite.setOrigin(size.x / 2.0f, size.y / 2.0f);
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
		(m_window->GetSize().y / 2.0f) + size.y);
}

void State_Intro::OnDestroy(Kengine::EventManager<GameState>* eventManager)
{
	m_textureManager->ReleaseResource("Intro");
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
