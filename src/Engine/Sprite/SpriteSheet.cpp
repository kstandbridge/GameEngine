#include "SpriteSheet.h"
#include "AnimationDirectional.h"
#include "../TextureManager.h"

namespace Kengine
{
	void SpriteSheet::ReleaseSheet()
	{
		m_textureManager->ReleaseResource(m_texture);
		m_animationCurrent = nullptr;
		while (m_animations.begin() != m_animations.end())
		{
			delete m_animations.begin()->second;
			m_animations.erase(m_animations.begin());
		}
	}

	void SpriteSheet::SetSpritePosition(const sf::Vector2f& pos)
	{
		m_sprite.setPosition(pos);
	}

	bool SpriteSheet::SetAnimation(const std::string& name, const bool& play, const bool& loop)
	{
		auto it = m_animations.find(name);
		if (it == m_animations.end()) return false;
		if (it->second == m_animationCurrent) return false;
		if (m_animationCurrent) m_animationCurrent->Stop();
		m_animationCurrent = it->second;
		m_animationCurrent->SetLooping(loop);
		if (play) m_animationCurrent->Play();
		m_animationCurrent->CropSprite();
		return true;
	}

	bool SpriteSheet::LoadSheet(const std::string& filePath)
	{
		std::ifstream sheet;
		sheet.open(filePath);
		if (sheet.is_open())
		{
			ReleaseSheet(); // Release current sheet resources
			std::string line;
			while (std::getline(sheet, line))
			{
				if (line[0] == '|') continue;
				std::stringstream keyStream(line);
				std::string type;
				keyStream >> type;
				if (type == "Texture")
				{
					if (m_texture != "")
					{
						std::cerr << "! Duplicate texture entries in: " << filePath << std::endl;
						continue;
					}
					std::string texture;
					keyStream >> texture;
					if (!m_textureManager->RequireResource(texture))
					{
						std::cerr << "! Could not set up the texture: " << texture << std::endl;
						continue;
					}
					m_texture = texture;
					m_sprite.setTexture(*m_textureManager->GetResource(m_texture));
				}
				else if (type == "Size")
				{
					keyStream >> m_spriteSize.x >> m_spriteSize.y;
					m_sprite.setOrigin(m_spriteSize.x / 2.0f, m_spriteSize.y / 2.0f);
				}
				else if (type == "Scale")
				{
					keyStream >> m_spriteScale.x >> m_spriteScale.y;
					m_sprite.setScale(m_spriteScale);
				}
				else if (type == "AnimationType")
				{
					keyStream >> m_animationType;
				}
				else if (type == "Animation")
				{
					std::string name;
					keyStream >> name;
					if (m_animations.find(name) != m_animations.end())
					{
						std::cerr << "! Duplicate animation(" << name << ") in: " << filePath << std::endl;
						continue;
					}
					AnimationBase* anim = nullptr;
					if (m_animationType == "Directional")
					{
						anim = new AnimationDirectional();
					}
					else
					{
						std::cerr << "! Unknown animation type: " << m_animationType << std::endl;
						continue;
					}

					keyStream >> *anim;
					anim->SetSpriteSheet(this);
					anim->SetName(name);
					anim->Reset();
					m_animations.emplace(name, anim);

					if (m_animationCurrent) continue;;
					m_animationCurrent = anim;
					m_animationCurrent->Play();
				}

			}
			sheet.close();
			return true;
		}
		std::cerr << "! Failed loading sprite sheet: " << filePath << std::endl;
		return false;
	}

	void SpriteSheet::Update(const float& deltaTime)
	{
		m_animationCurrent->Update(deltaTime);
	}

	void SpriteSheet::Draw(sf::RenderWindow* window)
	{
		window->draw(m_sprite);
	}

	sf::Vector2i SpriteSheet::GetSpriteSize() const
	{
		return m_spriteSize;
	}

	Direction SpriteSheet::GetDirection()
	{
		return m_direction;
	}

	void SpriteSheet::CropSprite(const sf::IntRect& rect)
	{
		m_sprite.setTextureRect(rect);
	}

	void SpriteSheet::SetDirection(const Direction& direction)
	{
		if(direction == m_direction) return;
		m_direction = direction;
		m_animationCurrent->CropSprite();
	}
}
