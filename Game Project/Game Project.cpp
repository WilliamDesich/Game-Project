#include <SFML/Graphics.hpp>
#include "Header1.h"

sf::Vector2f position(80, 425);
sf::Vector2f velocity(0, 0);

float gravity = .45f;
bool gravitystate = false;

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(670, 500), "Beaver Game");

	sf::Texture backgroundTex;
	backgroundTex.loadFromFile("Textures/forest.png");
	sf::Texture backgroundTex2;
	backgroundTex2.loadFromFile("Textures/forest2.png");
	sf::Texture backgroundTex3;
	backgroundTex3.loadFromFile("Textures/forest3.png");
	sf::Texture walkingTex;
	walkingTex.loadFromFile("Textures/BeaverWalking.png");
	sf::Texture idleTex;
	idleTex.loadFromFile("Textures/BeaverIdle.png");
	sf::Texture spikeTex;
	spikeTex.loadFromFile("Textures/YellowSpike.png");
	sf::Texture topSpikeTex;
	topSpikeTex.loadFromFile("Textures/YellowSpike.png");

	sf::IntRect rect[2];
	rect[0] = sf::IntRect(0, 0, 36, 24);
	rect[1] = sf::IntRect(0, 24, 36, 24);

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTex);
	sf::Sprite backgroundSprite2;
	backgroundSprite2.setTexture(backgroundTex2);
	sf::Sprite backgroundSprite3;
	backgroundSprite3.setTexture(backgroundTex3);

	backgroundSprite.setPosition(0,0);
	backgroundSprite2.setPosition(670,0);
	backgroundSprite3.setPosition(670*2,0);

	sf::Sprite obstacleSprite;
	obstacleSprite.setTexture(spikeTex);
	obstacleSprite.setOrigin(32, 32);
	obstacleSprite.setScale(3, 3);
	obstacleSprite.setPosition(480, 467);

	sf::Sprite topObstacleSprite;
	topObstacleSprite.setTexture(topSpikeTex);
	topObstacleSprite.setOrigin(32, 32);
	topObstacleSprite.setScale(3, -3);
	topObstacleSprite.setPosition(650, -17);

	sf::Sprite playerSprite;
	//playerSprite.setTexture(walkingTex);
	//playerSprite.setTextureRect(rect[0]);
	playerSprite.setTexture(idleTex);
	playerSprite.setOrigin(24, 18);
	playerSprite.setScale(2, 2);
	playerSprite.setPosition(position);

	float everythingPos = -.1;

	float randomTime = RandomFloat(.5, 2);

	sf::Clock clock, difClock, obstacleClock, topObstacleClock;
	int imgCount = 0;

	float timer = 0;
	float spriteTimer = 0;
	float obstacleTimer = 0;
	float topObstacleTimer = 0;

	bool movingUp = false;
	bool movingDown = false;
	bool movingLeft = false;
	bool movingRight = false;

	bool facingLeft = true;

	bool beaverInvert = false;


	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space)
				{
					gravitystate = !gravitystate;
					gravity = -gravity;
					playerSprite.scale(1, -1);
				}

				if (event.key.code == sf::Keyboard::A) {
					movingLeft = true;

					if (!facingLeft) {
						playerSprite.scale(-1, 1);
						facingLeft = true;
					}
				}
				if (event.key.code == sf::Keyboard::D) {
					movingRight = true;

					if (facingLeft) {
						playerSprite.scale(-1, 1);
						facingLeft = false;
					}

				}
			}

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) {
					movingUp = false;
				}

				if (event.key.code == sf::Keyboard::A) {
					movingLeft = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					movingRight = false;


				}
			}
		}

		timer = clock.getElapsedTime().asSeconds();
		if (timer > .3f) {
			if (imgCount < 1)
				imgCount++;
			else
				imgCount = 0;
			clock.restart();
		}

		velocity.x = 0;

		if (movingRight)
			velocity.x += .25f;
		if (movingLeft)
			velocity.x -= .25f;

		velocity.y += gravity;

		if (position.y >= 425) {
			position.y = 425;
			if (velocity.y > 0)
				velocity.y = 0;
		}

		if (position.y <= 25) {
			position.y = 25;
			if (velocity.y < 0)
				velocity.y = 0;
		}


		position += velocity;

			playerSprite.setTexture(walkingTex);
			playerSprite.setTextureRect(rect[imgCount]);

		if
		(playerSprite.getGlobalBounds().intersects(obstacleSprite.getGlobalBounds()))
		{
			playerSprite.setPosition(80, 425);
			position.x = 80;
			position.y = 425;
			gravity = false;
			playerSprite.scale(1, -1);
		}

		if
		(playerSprite.getGlobalBounds().intersects(topObstacleSprite.getGlobalBounds()))
		{
			playerSprite.setPosition(80, 425);
			position.x = 80;
			position.y = 425;
			gravity = false;
			playerSprite.scale(1, -1);
		}

		backgroundSprite.move(everythingPos,0);
		backgroundSprite2.move(everythingPos, 0);
		backgroundSprite3.move(everythingPos, 0);

		spriteTimer = difClock.getElapsedTime().asSeconds();
		if (spriteTimer > 2) 
		{
			difClock.restart();
			everythingPos -= .025;
		}

		//get time as seconds
		//if (time > the random time AND obstbable is past the screen
		// move it to the other side
		//reset clock
		//randomTime = RandomFloat(.5, 2);
		obstacleTimer = obstacleClock.getElapsedTime().asSeconds();
		if (obstacleTimer > randomTime && obstacleSprite.getGlobalBounds().left < 0 ) {
			obstacleSprite.setPosition(900, 467);
			obstacleClock.restart();
			randomTime = RandomFloat(.5, 2);
		}

		topObstacleTimer = topObstacleClock.getElapsedTime().asSeconds();
		if (topObstacleTimer > randomTime && topObstacleSprite.getGlobalBounds().left < 0) {
			topObstacleSprite.setPosition(900, 67);
			topObstacleClock.restart();
			randomTime = RandomFloat(.5, 2);
		}

		if(backgroundSprite.getPosition().x < -670) 
		{
			backgroundSprite.move(670 * 3, 0);
		}
		if (backgroundSprite2.getPosition().x < -670)
		{
			backgroundSprite2.move(670 * 3, 0);
		}
		if (backgroundSprite3.getPosition().x < -670)
		{
			backgroundSprite3.move(670 * 3, 0);
		}

		obstacleSprite.move(everythingPos, 0);



		//playerSprite.setPosition(position);
		playerSprite.move(velocity);
		window.clear();
		window.draw(backgroundSprite);
		window.draw(backgroundSprite2);
		window.draw(backgroundSprite3);
		window.draw(playerSprite);
		window.draw(obstacleSprite);
		window.draw(topObstacleSprite);
		window.display();

	}
}



