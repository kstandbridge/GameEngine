#pragma once
#include <sstream>

namespace Kengine
{
	class SpriteSheet;

	class AnimationBase
	{
		friend class SpriteSheet;

		float m_elapsedTime;
		bool m_playing;

	protected:

		unsigned int m_frameCurrent;

		unsigned int m_frameStart;
		unsigned int m_frameEnd;
		unsigned int m_frameRow;
		float m_frameTime;
		unsigned int m_frameActionStart;
		unsigned int m_frameActionEnd;

		bool m_loop;

		std::string m_name;
		SpriteSheet* m_spriteSheet;

		virtual void CropSprite() = 0;
		virtual void FrameStep() = 0;
		virtual void ReadIn(std::stringstream& stream) = 0;

	public:

		AnimationBase()
			: m_elapsedTime(0.0f),
			m_playing(false),
			m_frameCurrent(0),
			m_frameStart(0),
			m_frameEnd(0),
			m_frameRow(0),
			m_frameTime(0.0f),
			m_frameActionStart(-1),
			m_frameActionEnd(-1),
			m_loop(true),
			m_spriteSheet(nullptr)
		{
		}

		void SetName(const std::string& name) { m_name = name; }
		void SetSpriteSheet(SpriteSheet* spriteSheet) { m_spriteSheet = spriteSheet; }
		void SetLooping(const bool& loop) { m_loop = loop; }

		void Play() { m_playing = true; }
		void Pause() { m_playing = false; }
		void Stop() { m_playing = false; Reset(); }
		void Reset();

		void Update(const float& deltaTime);

		friend std::stringstream& operator>>(std::stringstream& stream, AnimationBase& animation)
		{
			animation.ReadIn(stream);
			return stream;
		}

	};
}

