#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>

unsigned Map::ConvertCoords(unsigned x, unsigned y)
{
	return (x * m_maxMapSize.x) + y; // Row-major
}

Tile* Map::GetTile(unsigned x, unsigned y)
{
	auto it = m_tileMap.find(ConvertCoords(x, y));
	return (it != m_tileMap.end() ? it->second : nullptr);
}

sf::Vector2f Map::GetStartPosition() const
{
	return m_playerStart;
}

void Map::LoadTiles(std::string filePath)
{
	std::ifstream file;
	file.open(filePath);
	if(!file.is_open())
	{
		std::cout << "! Failed loading tile set file: " << filePath << std::endl;
		return;
	}
	std::string line;
	while(std::getline(file, line))
	{
		if(line[0] == '|') continue;
		std::stringstream keyStream(line);
		int tileId;
		keyStream >> tileId;
		if(tileId < 0) continue;
		TileInfo* tile = new TileInfo(m_textureManager, "TileSheet", tileId);
		keyStream >> tile->m_name >> tile->m_friction.x >> tile->m_friction.y >> tile->m_deadly;
		if(!m_tileSet.emplace(tileId, tile).second)
		{
			// Duplicate tile detected!
			std::cout << "! Duplicate tile type: " << tile->m_name << std::endl;
			delete tile;
		}
	}
	file.close();
}

void Map::LoadMap(std::string filePath)
{
	std::ifstream mapFile;
	mapFile.open(filePath);
	if(!mapFile.is_open())
	{
		std::cout << "! Failed loading map file: " << filePath << std::endl;
		return;
	}
	// EntityManager* entity = m_context->m_entityManager;
	std::string line;
	std::cout << "--- Loading a map: " << filePath << std::endl;

	int playerId = -1;
	while(std::getline(mapFile, line))
	{
		if(line[0] == '|') continue;
		std::stringstream keyStream(line);
		std::string type;
		keyStream >> type;
		if(type == "TILE")
		{
			int tileId = 0;
			keyStream >> tileId;
			if(tileId < 0)
			{
				std::cout << "! Bad tile id: " << tileId << std::endl;
				continue;
			}
			auto it = m_tileSet.find(tileId);
			if(it == m_tileSet.end())
			{
				std::cout << "! Tile id(" << tileId << ") was not found in tileset." << std::endl;
				continue;
			}
			sf::Vector2i tileCoords;
			keyStream >> tileCoords.x >> tileCoords.y;
			if(tileCoords.x > m_maxMapSize.x || tileCoords.y > m_maxMapSize.y)
			{
				std::cout << "! Tile is out of range: " << tileCoords.x << "," << tileCoords.y << std::endl;
				continue;
			}
			Tile* tile = new Tile();
			// Bind properties of a tile from a sec.
			tile->m_properties = it->second;
			if(!m_tileMap.emplace(ConvertCoords(tileCoords.x, tileCoords.y), tile).second)
			{
				// Duplicate tile detected!
				std::cout << "! Duplicate tile! : " << tileCoords.x << "," << tileCoords.y << std::endl;
				delete tile;
				tile = nullptr;
				continue;
			}
			std::string warp;
			keyStream >> warp;
			tile->m_warp = false;
			if(warp == "WARP") tile->m_warp = true;
		} 
		else if(type == "BACKGROUND")
		{
			if(m_backgroundTexture != "") continue;
			keyStream >> m_backgroundTexture;
			if(!m_textureManager->RequireResource(m_backgroundTexture))
			{
				m_backgroundTexture = "";
				continue;
			}
			sf::Texture* texture = m_textureManager->GetResource(m_backgroundTexture);
			m_background.setTexture(*texture);
			sf::Vector2f viewSize = m_currentState->GetView().getSize();
			sf::Vector2u textureSize = texture->getSize();
			sf::Vector2f scaleFactors;
			scaleFactors.x = viewSize.x / textureSize.x;
			scaleFactors.y = viewSize.y / textureSize.y;
			m_background.setScale(scaleFactors);
		} 
		else if (type == "SIZE")
		{
			keyStream >> m_maxMapSize.x >> m_maxMapSize.y;
		}
		else if(type == "GRAVITY")
		{
			keyStream >> m_mapGravity;
		}
		else if(type == "DEFAULT_FRICTION")
		{
			keyStream >> m_defaultTile.m_friction.x >> m_defaultTile.m_friction.y;
		}
		else if(type == "NEXTMAP")
		{
			keyStream >> m_nextMap;
		}
		// TODO Loading player and enemies
		else if(type == "PLAYER")
		{
			// if(playerId != -1) continue;
			// // Set up the player position here.
			// playerId = entity->Add(EntityType::Player);
			// if(playerId < 0) continue;
			float playerX = 0; float playerY = 0;
			keyStream >> playerX >> playerY;
			// entity->Find(playerId)->SetPosition(playerX, playerY);
			m_playerStart = sf::Vector2f(playerX, playerY);
		}
		else if(type == "ENEMY")
		{
			// std::string enemyName;
			// keyStream >> enemyName;
			// int enemyId = entity->Add(EntityType::Enemy, enemyName);
			// if(enemyId < 0) continue;
			// float enemyX; float enemyY = 0;
			// keyStream >> enemyX >> enemyY;
			// entity->Find(enemyId)->SetPosition(enemyX, enemyY);
		}
		else
		{
			std::cout << "! Unknown type '" << type << "'" << std::endl;
		}
	}
	mapFile.close();
	std::cout << "--- Map Loaded! ---" << std::endl;
}

void Map::Update(float deltaTime)
{
	// TODO we could load another map maybe?
	sf::FloatRect viewSpace = m_window->GetViewSpace();
	m_background.setPosition(viewSpace.left, viewSpace.top);

}

void Map::Draw()
{
	sf::RenderWindow* window = m_window->GetRenderWindow();
	// window->draw(m_background);

	sf::FloatRect viewSpace = m_window->GetViewSpace();

	// Culling - If its not in the view space, don't draw it!
	// Figure out where to start and end the tiles
	sf::Vector2i tileBegin(
		floor(viewSpace.left / Sheet::Tile_Size),
		floor(viewSpace.top/ Sheet::Tile_Size));
	sf::Vector2i tileEnd(
		ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size),
		ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size));

	unsigned int count = 0;
	for (int x = tileBegin.x; x <= tileEnd.x; ++x)
		for (int y = tileBegin.y; y <= tileEnd.y; ++y)
		{
			if(x < 0 || y < 0) continue;
			Tile* tile = GetTile(x, y);
			if(!tile) continue;
			sf::Sprite& sprite = tile->m_properties->m_sprite;
			sprite.setPosition(x * Sheet::Tile_Size, y * Sheet::Tile_Size);
			window->draw(sprite);
			++count;

			// // Debug.
			// if(m_context->m_debugOverlay.Debug()){
			// 	if(tile->m_properties->m_deadly || tile->m_warp){
			// 		sf::RectangleShape* tileMarker = new sf::RectangleShape(
			// 			sf::Vector2f(Sheet::Tile_Size,Sheet::Tile_Size));
			// 		tileMarker->setPosition(x * Sheet::Tile_Size, y * Sheet::Tile_Size);
			// 		if(tile->m_properties->m_deadly){
			// 			tileMarker->setFillColor(sf::Color(255,0,0,100));
			// 		} else if(tile->m_warp){
			// 			tileMarker->setFillColor(sf::Color(0,255,0,150));
			// 		}
			// 		m_context->m_debugOverlay.Add(tileMarker);
			// 	}
			// }
			// End debug.
		}
}

sf::Vector2u& Map::GetMapSize()
{
	return m_maxMapSize;
}
