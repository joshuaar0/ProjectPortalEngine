#include "Game.h"



void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 30;
	this->points = 0;

	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;


}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new RenderWindow(this->videoMode, "Game 2", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);
}
void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/LemonMilk.otf"))
		cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD LemonMilk.otf" << endl;
}

void Game::initText()
{
	//Gui text init
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(Color::White);
	this->guiText.setCharacterSize(40);

	//End game text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(Color::Red);
	this->endGameText.setCharacterSize(100);
	this->endGameText.setPosition(Vector2f(130, 200));//x and y
	this->endGameText.setString("YOU DIED, GAME OVER");
}

//Constructors and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}

//functions
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::spawnEnemy()
{
	/*
	* Spawns enemies and sets their types and colors, positions randomly.
	* Sets a random type (diff)
	* Sets a random position
	* Sets a random color
	* Adds enemy to the vector
	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	//Randomize enemy type
	int type = rand() % 5;//0 to 4

	switch (type)
	{
	case 0:
		this->enemy.setSize(Vector2f(30.f, 30.f));
		this->enemy.setFillColor(Color::Cyan);
		break;
	case 1:
		this->enemy.setSize(Vector2f(40.f, 40.f));
		this->enemy.setFillColor(Color::Magenta);
		break;
	case 2:
		this->enemy.setSize(Vector2f(40.f, 40.f));
		this->enemy.setFillColor(Color::Yellow);
		break;
	case 3:
		this->enemy.setSize(Vector2f(70.f, 70.f));
		this->enemy.setFillColor(Color::Red);
		break;
	case 4:
		this->enemy.setSize(Vector2f(20.f, 20.f));
		this->enemy.setFillColor(Color::Green);
		break;
	default:
		this->enemy.setSize(Vector2f(100.f, 100.f));
		this->enemy.setFillColor(Color::White);
		break;
	}

	//Spawn the enemy
	this->enemies.push_back(this->enemy);

}


void Game::updateEnemies()
{
	/*
	* update the enemy spawn timer and spawns enemies
	* when the total amount fo enemies is smaller than the max
	* Moves the enemies downward.
	* Removes the enemies at the edge of the screen.
	*/
	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		//Spawn the enemy and reset the timer
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move and updating the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 5.f);

		//If the enemy is past the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void Game::renderEnemies(RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}


void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->sfmlEvent.key.code == Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

const int Game::randomizeBallType() const
{
	int type = SwagBallTypes::DEFAULT;
	int randomValue = rand() % 100 + 1;

	if (randomValue > 60 && randomValue <= 80)
		type = SwagBallTypes::DAMAGING;
	else if (randomValue > 80 && randomValue <= 100)
		type = SwagBallTypes::HEALING;

	return type;
}

//Handles spawning of balls
void Game::spawnSwagBalls()
{
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += 1.f;
	}
	else
	{
		if (this->swagBalls.size() < this->maxSwagBalls)
		{
			this->swagBalls.push_back(SwagBall(*this->window, this->randomizeBallType()));
			this->spawnTimer = 0.f;
		}
	}
}

void Game::updateCollision()
{
	//Check the collision
	for (size_t i = 0; i < this->swagBalls.size(); i++)
	{//Checks if player and balls are intersecting, then erase it.
		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{

			switch (this->swagBalls[i].getType())
			{
			case SwagBallTypes::DEFAULT:
				this->points++;
				break;
			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(2);
				this->points--;
				break;
			case SwagBallTypes::HEALING:
				this->player.gainHealth(1);
				this->points++;
				break;
			}
			
			//Add points
			//this->points++;

			//Remove the ball
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->enemies[i].getGlobalBounds()))
		{
			if (this->enemies[i].getFillColor() == Color::Green)
			{
				this->points++;
				this->player.gainHealth(1);
			}
			if (this->enemies[i].getFillColor() == Color::Yellow)
			{
				this->points++;
			}
			if (this->enemies[i].getFillColor() == Color::Magenta)
			{
				this->points++;
			}
			if (this->enemies[i].getFillColor() == Color::Cyan)
			{
				this->points++;
			}
			if (this->enemies[i].getFillColor() == Color::Red)
			{
				this->points--;
				this->player.takeDamage(1);
			}
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void Game::updateGui()
{
	stringstream ss;//stream that takes data and prints it out easily without parsing, converts on its own.

	ss << " Points: " << this->points 
		<< " Health: " << this->player.getHp() << " / " << this->player.getHpMax() << endl;

	this->guiText.setString(ss.str());
}

void Game::updatePlayer()
{
	this->player.update(this->window);


	if (this->player.getHp() <= 0)
	{
		this->endGame = true;
	}
}

void Game::update()
{
	this->pollEvents();
	if (this->endGame == false)
	{
		//this->updateMousePositions();
		//this->updateText();
		this->updateEnemies();

		this->spawnSwagBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGui();
	}
}

void Game::renderGui(RenderTarget* target)//Pointer to whatever we want to use. Renders not to the window directly?
{
	target->draw(this->guiText);
}

void Game::render()
{
	this->window->clear();//Clears old frame

	//Render stuff
	this->player.render(this->window);

	for (auto i: this->swagBalls)
	{
		i.render(*this->window);
	}
	this->renderEnemies(*this->window);

	this->renderGui(this->window);//Renders onto the window

	//Render end text
	if (this->endGame == true)
	{
		this->window->draw(this->endGameText);
	}

	this->window->display();//Draws new frame?
}

