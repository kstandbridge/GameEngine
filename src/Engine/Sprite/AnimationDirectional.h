#pragma once
#include "AnimationBase.h"

namespace Kengine
{
	class AnimationDirectional : public AnimationBase
	{
	protected:
		void CropSprite() override;
		void FrameStep() override;
		void ReadIn(std::stringstream& stream) override;
	};
}

