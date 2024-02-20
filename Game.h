#pragma once

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "SwagBall.h"

using namespace std;
using namespace sf;


class Game
{
private:
	VideoMode videoMode;//Stores width/height of window
	RenderWindow* window;
	bool endGame;
	Event sfmlEvent;//Can get evens from window, keyboard, mouse?

	Player player;
	int points;

	Font font;
	Text guiText;
	Text endGameText;

	vector<SwagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;

	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

	//Game logic
	int type;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//Game objects
	vector<RectangleShape> enemies;
	RectangleShape enemy;



public:
	//Constructors and Destructors
	Game();
	~Game();

	//Accessors
	const bool& getEndGame() const;

	//Modifiers

	//Functions
	const bool running() const;
	void pollEvents();

	const int randomizeBallType() const;
	void spawnSwagBalls();
	void updateCollision();
	void updateGui();
	void updatePlayer();
	void update();
	void renderGui(RenderTarget* target);
	void render();



	//functions
	void spawnEnemy();

	void updateEnemies();

	void renderEnemies(RenderTarget& target);
};

