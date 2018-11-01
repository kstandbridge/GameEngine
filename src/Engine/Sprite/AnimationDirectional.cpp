#include "AnimationDirectional.h"
#include <SFML/Graphics/Rect.hpp>
#include "SpriteSheet.h"

namespace Kengine
{
	void AnimationDirectional::CropSprite()
	{
		auto size = m_spriteSheet->GetSpriteSize();
		sf::IntRect rect(
			size.x * m_frameCurrent,
			size.y * (m_frameRow + (short)m_spriteSheet->GetDirection()),
			size.x,
			size.y);
		m_spriteSheet->CropSprite(rect);
	}

	void AnimationDirectional::FrameStep()
	{
		if (m_frameStart < m_frameEnd)
			++m_frameCurrent;
		else
			--m_frameCurrent;

		if ((m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd) ||
			(m_frameStart > m_frameEnd && m_frameCurrent < m_frameEnd))
		{
			if (m_loop)
			{
				m_frameCurrent = m_frameStart;
				return;
			}
			m_frameCurrent = m_frameEnd;
			Pause();
		}
	}

	void AnimationDirectional::ReadIn(std::stringstream& stream)
	{
		stream >> m_frameStart
			>> m_frameEnd
			>> m_frameRow
			>> m_frameTime
			>> m_frameActionStart
			>> m_frameActionEnd;
	}
}
