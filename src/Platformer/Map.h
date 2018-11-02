#pragma once
#include "Engine/Window.h"
#include "GameState.h"
#include "Engine/TextureManager.h"
#include "Engine/BaseState.h"

enum Sheet { Tile_Size = 32, Sheet_Width = 256, Sheet_Height = 256 };

using TileID = unsigned int;

struct TileInfo
{
	TileInfo(Kengine::TextureManager* textureManager, const std::string& texture = "", TileID id = 0)
		: m_id(0), m_deadly(false), m_textureManager(textureManager)
	{

		if (texture == "")
		{
			id = 0;
			return;
		}
		if (!m_textureManager->RequireResource(texture)) return;
		m_texture = texture;
		m_id = id;
		m_sprite.setTexture(*m_textureManager->GetResource(m_texture));
		sf::IntRect tileBoundaries(
			m_id % (Sheet::Sheet_Width / Sheet::Tile_Size) * Sheet::Tile_Size,
			m_id / (Sheet::Sheet_Height / Sheet::Tile_Size) * Sheet::Tile_Size,
			Sheet::Tile_Size,
			Sheet::Tile_Size);
		m_sprite.setTextureRect(tileBoundaries);
	}

	~TileInfo()
	{
		if (m_texture == "") return;
		m_textureManager->RequireResource(m_texture);
	}

	sf::Sprite m_sprite;

	TileID m_id;
	std::string m_name;
	sf::Vector2f m_friction;
	bool m_deadly;

	std::string m_texture;
	Kengine::TextureManager* m_textureManager;
};

struct Tile
{
	TileInfo* m_properties;
	bool m_warp; // Is the tile a warp
	// Other flags unique to each tile
};

class Map
{
	Kengine::Window<GameState>* m_window;
	Kengine::BaseState<GameState>* m_currentState;
	Kengine::TextureManager* m_textureManager;

	sf::Sprite m_background;
	sf::Vector2u m_maxMapSize;
	sf::Vector2f m_playerStart;
	std::string m_backgroundTexture;
	float m_mapGravity;
	TileInfo m_defaultTile;

	std::string m_nextMap;

	std::unordered_map<TileID, Tile*> m_tileMap;
	std::unordered_map<TileID, TileInfo*> m_tileSet;

	unsigned ConvertCoords(unsigned int x, unsigned int y);
	Tile* GetTile(unsigned int x, unsigned int y);
public:

	Map(
		Kengine::Window<GameState>* window,
		Kengine::BaseState<GameState>* currentState,
		Kengine::TextureManager* textureManager)
		: m_window(window),
		m_currentState(currentState),
		m_textureManager(textureManager),
		m_defaultTile(textureManager)
	{
	}

	sf::Vector2f GetStartPosition() const;

	void LoadTiles(std::string filePath);
	void LoadMap(std::string filePath);

	void Update(float deltaTime);
	void Draw();
	sf::Vector2u& GetMapSize();
};

