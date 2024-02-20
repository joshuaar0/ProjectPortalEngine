#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->hpMax = 10;
	this->hp = hpMax;
}

void Player::initShape()
{
	this->shape.setFillColor(Color::Green);
	this->shape.setSize(Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);//Set position

	this->initVariables();
	this->initShape();
}

Player::~Player()
{
}

const RectangleShape& Player::getShape() const
{//return shape of player
	return this->shape;
}

//Accessors
const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

//FUnctions
void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
	{
		this->hp -= damage;
	}if (this->hp < 0)
	{
		this->hp = 0;
	}
}


void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
	{
		this->hp += health;
	}
	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

void Player::updateInput()
{
	//Keyboard input
	if (Keyboard::isKeyPressed(Keyboard::A))//Checks if A is pressed
	{
		this->shape.move(-this->movementSpeed, 0.f);//movement in the left direction, 0.f movement to the y axis (no movement).
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))//Checks if D is pressed
	{
		this->shape.move(this->movementSpeed, 0.f);//move right, no movement upd/down.
	}
	if (Keyboard::isKeyPressed(Keyboard::W))//Checks if W is pressed
	{
		this->shape.move(0.f, -this->movementSpeed); //Move up the screen.
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))//Checks if S is pressed
	{
		this->shape.move(0.f, this->movementSpeed); //Move down the screen.
	}
}

void Player::updateWindowBoundsCollision(const RenderTarget* target)
{//Update bounds after every position change
	//Left collision
	if (this->shape.getGlobalBounds().left <= 0.f)
	{
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	}
	//Right collision
	else if(this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
	{
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	}
	//Left collision
	if (this->shape.getGlobalBounds().top <= 0.f)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	}
	//Right collision
	else if(this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
	}
}

void Player::update(const RenderTarget* target)
{
	//Window bounds collision
	this->updateInput();

	this->updateWindowBoundsCollision(target);

}

void Player::render(RenderTarget* target)
{
	target->draw(this->shape);
}
