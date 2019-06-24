#include <SFML/Graphics.hpp>
#include "Header1.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(670, 450), "Beaver Game");

	sf::Texture backgroundTex;
	backgroundTex.loadFromFile("Textures/forest.png");
	sf::Texture walkingTex;
	walkingTex.loadFromFile("Textures/BeaverWalking.png");
	sf::Texture idleTex;
	idleTex.loadFromFile("Textures/BeaverIdle.png");
	sf::Texture spikeTex;
	spikeTex.loadFromFile("Textures/YellowSpike.png");

	sf::IntRect rect[2];
	rect[0] = sf::IntRect(0, 0, 36, 24);
	rect[1] = sf::IntRect(0, 24, 36, 24);

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTex);

	sf::Sprite obstacleSprite;
	obstacleSprite.setTexture(spikeTex);
	obstacleSprite.setOrigin(32,32);
	obstacleSprite.setScale(3, 3);
	obstacleSprite.setPosition(480, 467);

	sf::Sprite playerSprite;
	//playerSprite.setTexture(walkingTex);
	//playerSprite.setTextureRect(rect[0]);
	playerSprite.setTexture(idleTex);
	playerSprite.setOrigin(24, 18);
	playerSprite.setScale(2, 2);
	playerSprite.setPosition(80, 425);

	sf::Clock clock;
	int imgCount = 0;
	float timer = 0;

	bool movingUp = false;
	bool movingDown = false;
	bool movingLeft = false;
	bool movingRight = false;

	bool facingLeft = true;

	

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) 
				{
					if () 
						//^Make it so if the player is above a certain level, the sprite will jump down.
					{
						playerSprite.scale(1, -1);
					}
					else 
					{
						playerSprite.scale(1, -1);
					}
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
		if (timer > .2f) {
			if (imgCount < 1)
				imgCount++;
			else
				imgCount = 0;
			clock.restart();
		}

		

		sf::Vector2f movement(0, 0);

		if (movingUp)
			movement.y -= 0;
		if (movingDown)
			movement.y += 0;
		if (movingRight)
			movement.x += .25f;
		if (movingLeft)
			movement.x -= .25f;

		if (movingUp || movingDown || movingLeft || movingRight) {
			playerSprite.setTexture(walkingTex);
			playerSprite.setTextureRect(rect[imgCount]);
		}
		else {
			playerSprite.setTexture(idleTex);
			playerSprite.setTextureRect(rect[0]);
		}

		if
		(playerSprite.getGlobalBounds().intersects(obstacleSprite.getGlobalBounds())) 
		{
			playerSprite.setPosition(80, 425);
		}

		playerSprite.move(movement);
		window.clear();
		window.draw(backgroundSprite);
		window.draw(playerSprite);
		window.draw(obstacleSprite);
		window.display();
		
	}
}
