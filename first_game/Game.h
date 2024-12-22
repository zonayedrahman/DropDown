#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>



class Game
{
	sf::RenderWindow* window;
	sf::VideoMode	videoMode;

	sf::Event event;

	// Mouse movement
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// resources
	sf::Font font;

	// text
	sf::Text uiText;


	// game logic
	bool endGame;
	unsigned int points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	// game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;


	
	void initVariables();
	void initWindow();
	void initFonts();
	void initTexts();
	void initEnemies();

public:
	// constructors and destructors
	Game();
	virtual ~Game();

	// accessors
	const bool running() const;
	const bool getEndGame() const;


	// functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();

	void updateText();
	void updateEnemies();
	void update();


	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};

