#pragma once
#include <SFML/Graphics.hpp>

namespace Kengine
{
	template<typename ID>
	class StateManager;

	template<typename ID>
	class EventManager;

	template<typename ID>
	class Window;

	class FontManager;
	class TextureManager;

	template<typename ID>
	class BaseState
	{
	public:
		virtual void OnCreate(EventManager<ID>* eventManager) = 0;
		virtual void OnDestroy(EventManager<ID>* eventManager) = 0;
		
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		virtual void Update(const sf::Time& time) = 0;
		virtual void Draw() = 0;

		sf::View& GetView() { return m_view; }

		void SetView(sf::View view)
		{
			m_view = view;
		}

		void SetTransparent(const bool transparent) { m_transparent = transparent; }
		bool IsTransparent() const { return m_transparent; }

		void SetTranscendent(const bool transcendent) { m_transcendent = transcendent; }
		bool IsTranscendent() const { return m_transcendent; }

	protected:
		BaseState(
			FontManager* fontManager, 
			TextureManager* textureManager, 
			StateManager<ID>* stateManager, 
			Window<ID>* window)
			: m_fontManager(fontManager),
			  m_textureManager(textureManager), 
			  m_stateManager(stateManager), 
			  m_window(window)
		{
		}

		FontManager* m_fontManager;
		TextureManager* m_textureManager;
		StateManager<ID>* m_stateManager;
		Window<ID>* m_window;
		sf::View m_view;

		bool m_transparent;
		bool m_transcendent;
	};
	
}
