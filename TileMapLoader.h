#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class LayerType
{
	Renderable = 0,
	Collision,
	Triggers
};

struct Tile
{
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect subTexture;
	int layer;
	void render(sf::RenderWindow& window)
	{
		sprite.setTexture(texture);
		sprite.setTextureRect(subTexture);
		window.draw(sprite);
	}
};

struct Layer
{
	std::string name;
	LayerType type;
	std::string tileSetName;
	std::vector<Tile> tiles;
	void render(sf::RenderWindow& window)
	{
		for (Tile& t : tiles)
		{
			t.render(window);
		}
	}
};

struct TileMap
{
	std::vector<Layer> layers;

	void render(sf::RenderWindow& window)
	{
		for (Layer l : layers)
		{
			l.render(window);
		}
	}
};

class TileMapLoader
{
public:
	TileMapLoader() = default;
	static void load(std::string file, TileMap& map);
};

