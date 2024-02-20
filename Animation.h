#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Animation
{
public:
	IntRect uvRect;

	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	~Animation();

	void update(int row, float deltaTime, bool faceRight);

private:
	Vector2u imageCount;
	Vector2u currentImage;

	float totalTime;
	float switchTime;

};