#include "Game.h"



void Game::initVariables()
{

	this->window = nullptr;

	// game logic

	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 6;
	this->mouseHeld = false;

}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Game 1");


	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
		std::cout << "ERROR: initFonts():: could not load font\n";
	}
}

void Game::initTexts()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(18);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("Initializer");
	this->uiText.setPosition(10.f, 10.f);
}

void Game::initEnemies()
{
	this->enemy.setPosition(0,0);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);


}



Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initTexts();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}


void Game::spawnEnemy()
{
	/*
	@ return void

	spawns enemies and sets their colors and positions
	sets a random position
	sets a random color
	adds enemies to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
		0.f
	);

	// randomize enemy type
	int type = rand() % 5;

	switch (type) {

	case 0:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;

	case 1:
		this->enemy.setSize(sf::Vector2f(80.f, 80.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;

	case 2:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;

	case 3:
		this->enemy.setSize(sf::Vector2f(120.f, 120.f));
		this->enemy.setFillColor(sf::Color::Red);
		break;

	case 4:
		this->enemy.setSize(sf::Vector2f(150.f, 150.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;

	default:
		this->enemy.setSize(sf::Vector2f(150.f, 150.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;
	}


	


	// spawn the enemy
	this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event)) {

		switch (this->event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;


		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
		}
	}
}

void Game::updateMousePositions()
{
	/*
	@ return void
	updates mouse position
		- relative to window

	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n"
		<< "Health: "  << this->health << "\n";
	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{

	/*

	@ return void

	updates the enemy spawn timer and spawns enemies
	when the total amount of enemies is smaller than the max
	moves enemies downwards
	removes the enemies at the edge of the screen
	*/

	// updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {

			// spawn enemy and reset timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}



	// move the enemies
	//for (auto& e : this->enemies) {
	//	e.move(0.f, 1.f);
	//};


	// updating each enemy and checking if below the screen
	for (unsigned int i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].move(0.f, 5.f);



		// if below the window
		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			//std::cout << "Health: " << this->health << "\n";
		}



	}


	// check if clicked on
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {



		if (this->mouseHeld == false) {

			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
				if (enemies[i].getGlobalBounds().contains(this->mousePosView)) {


					if (this->enemies[i].getFillColor() == sf::Color::Magenta) {
						this->points += 10;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Blue) {
						this->points += 7;
					}
					if (this->enemies[i].getFillColor() == sf::Color::Cyan) {
						this->points += 5;
					}
					if (this->enemies[i].getFillColor() == sf::Color::Red) {
						this->points += 3;
					}
					if (this->enemies[i].getFillColor() == sf::Color::Green) {
						this->points += 1;
					}




					deleted = true;
					this->enemies.erase(this->enemies.begin() + static_cast<int>(i));

					//std::cout << "Points: " << this->points << "\n";
				}
			}
		}


		
	}
	else {
		this->mouseHeld = false;
	}
}

// Functions
void Game::update()
{
	this->pollEvents();

	if (!this->endGame) {
		this->updateMousePositions();
		
		this->updateText();
		this->updateEnemies();
	}
	

	if (this->health <= 0) {
		this->endGame = true;
	}



	// relative to screen
	//std::cout << "Mouse position: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";
	//relative to window
	//std::cout << "Mouse position: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";


}

void Game::renderText(sf::RenderTarget& target)
{
	//std::cout << static_cast<std::string>(this->uiText.getString()) << std::endl;
	//std::cout << &target << std::endl;
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	// rendering all the enemies
	for (auto& e : this->enemies) {
		target.draw(e);
	}
}

void Game::render() {

	/*
			- clear old frame
			- render objects
			- display new frame in window

		Renders the game objects
	*/
	this->window->clear();


	// Draw game objects
	//std::cout << &this->window << std::endl;
	this->renderEnemies(*this->window);
	this->renderText(*this->window);

	std::cout << "Rendering text: " << this->uiText.getString().toAnsiString() << std::endl;
	std::cout << this->window << std::endl;
	sf::Vector2f position = this->uiText.getPosition();
	std::cout << "Text position: (" << position.x << ", " << position.y << ")" << std::endl;



	this->window->display();

}
