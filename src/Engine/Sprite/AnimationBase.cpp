#include "AnimationBase.h"

namespace Kengine
{
	void AnimationBase::Reset()
	{
		m_frameCurrent = m_frameStart;
		m_elapsedTime = 0.0f;
		CropSprite();
	}

	void AnimationBase::Update(const float& deltaTime)
	{
		if(!m_playing) return;
		m_elapsedTime += deltaTime;
		if(m_elapsedTime < m_frameTime) return;
		FrameStep();
		CropSprite();
		m_elapsedTime = 0;
	}
}
