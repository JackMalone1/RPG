#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"

#include "TileMapLoader.h"



class Game
{
public:
	/// <summary>
	/// @brief Default constructor that initialises the SFML window, 
	///   and sets vertical sync enabled. 
	/// </summary>
	Game();

	/// <summary>
	/// @brief the main game loop.
	/// 
	/// A complete loop involves processing SFML events, updating and drawing all game objects.
	/// The actual elapsed time for a single game loop results (lag) is stored. If this value is 
	///  greater than the notional time for one loop (MS_PER_UPDATE), then additional updates will be 
	///  performed until the lag is less than the notional time for one loop.
	/// The target is one update and one render cycle per game loop, but slower PCs may 
	///  perform more update than render operations in one loop.
	/// </summary>
	void run();

protected:



	sf::Font m_font;



	void setUpTexture();

	void setUpText();

	/// <summary>
	/// @brief Placeholder to perform updates to all game objects.
	/// </summary>
	/// <param name="time">update delta time</param>
	void update(double dt);

	/// <summary>
	/// @brief Draws the background and foreground game objects in the SFML window.
	/// The render window is always cleared to black before anything is drawn.
	/// </summary>
	void render();

	/// <summary>
	/// @brief Checks for events.
	/// Allows window to function and exit. 
	/// Events are passed on to the Game::processGameEvents() method.
	/// </summary>	
	void processEvents();

	/// <summary>
	/// @brief Handles all user input.
	/// </summary>
	/// <param name="event">system event</param>
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;

	TileMap tileMap;
};
