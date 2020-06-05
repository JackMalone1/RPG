#include "TileMapLoader.h"

void operator >> (const YAML::Node& layerNode, Layer& layer)
{
	layer.name = layerNode["name"].as<std::string>();
	layer.type = static_cast<LayerType>(layerNode["type"].as<int>());
}

void operator >> (const YAML::Node& tileNode, Tile& tile)
{
	tile.texture.loadFromFile(tileNode["path"].as<std::string>());
	tile.sprite.setTexture(tile.texture);
	tile.subTexture.left = tileNode["left"].as<float>();
	tile.subTexture.top = tileNode["top"].as<float>();
	tile.subTexture.width = tileNode["width"].as<float>();
	tile.subTexture.height = tileNode["height"].as<float>();
	tile.sprite.setTextureRect(tile.subTexture);
	tile.position.x = tileNode["position"]["x"].as<float>();
	tile.position.y = tileNode["position"]["y"].as<float>();
	tile.sprite.setPosition(tile.position);
	tile.layer = tileNode["layer"].as<int>();
}

void operator >> (const YAML::Node& tileMapNode, TileMap& tileMap)
{
	const YAML::Node& layersNode = tileMapNode["layers"].as<YAML::Node>();

	for (unsigned i = 0; i < layersNode.size(); ++i)
	{
		Layer layer;
		layersNode[i] >> layer;
		tileMap.layers.push_back(layer);
	}

	const YAML::Node& tilesNode = tileMapNode["tiles"].as<YAML::Node>();

	for (unsigned i = 0; i < tilesNode.size(); ++i)
	{
		Tile tile;
		tilesNode[i] >> tile;
		tileMap.layers.at(tile.layer).tiles.push_back(tile);
	}
}


void TileMapLoader::load(std::string file, TileMap& map)
{
	std::stringstream ss;
	ss << ".//resources//levels//";
	ss << file;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("File: " + ss.str() + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> map;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}
