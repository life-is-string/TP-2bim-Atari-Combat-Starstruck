/*
 * player.cpp
 *
 *  Created on: 19 de jun. de 2023
 *      Author: hayde
 */

#include <Entities/player.hpp>
Player::Player(GameDataRef data, std::string keyset, std::string texPath) :
		data(data), keyset(keyset), texPath(texPath) {
}
void Player::init() {
	currentDir = south;
	sprite.setOrigin(sprite.getGlobalBounds().width / 2,
			sprite.getGlobalBounds().height / 2);
	sprite.setScale(1.125, 1.125);
	if (keyset == "arrow") {
		keyUp = sf::Keyboard::Up;
		keyDown = sf::Keyboard::Down;
		keyLeft = sf::Keyboard::Left;
		keyRight = sf::Keyboard::Right;
	}
	if (keyset == "wasd") {
		keyUp = sf::Keyboard::W;
		keyDown = sf::Keyboard::S;
		keyLeft = sf::Keyboard::A;
		keyRight = sf::Keyboard::D;
	}
}
void Player::move() {
	dir = (sf::Vector2f(0, 0));
	if (!blockMovement) {
		if (sf::Keyboard::isKeyPressed(keyUp)) {
			dir.y = -1;
			if (velocity.y > -maxVelocity) {
				velocity.y += acc * dir.y;
			}
		} else if (sf::Keyboard::isKeyPressed(keyLeft)) {
			dir.x = -1;
			if (velocity.x > -maxVelocity) {
				velocity.x += acc * dir.x;
			}
		} else if (sf::Keyboard::isKeyPressed(keyDown)) {
			dir.y = 1;
			if (velocity.y < maxVelocity) {
				velocity.y += acc * dir.y;
			}
		} else if (sf::Keyboard::isKeyPressed(keyRight)) {
			dir.x = 1;
			if (velocity.x < maxVelocity) {
				velocity.x += acc * dir.x;
			}
		}
	}
}
void Player::friction() {
	//Up
	if (velocity.y < 0) {

		velocity.y += drag;

		if (velocity.y > 0) {
			velocity.y = 0;
		}
	}
	//Down
	if (velocity.y > 0) {

		velocity.y -= drag;

		if (velocity.y < 0) {
			velocity.y = 0;
		}
	}
	//Left
	if (velocity.x < 0) {

		velocity.x += drag;

		if (velocity.y > 0) {
			velocity.y = 0;
		}
	}
	//Right
	if (velocity.x > 0) {

		velocity.x -= drag;

		if (velocity.x < 0) {
			velocity.x = 0;
		}
	}

}

void Player::rotate(std::string dir) {
	if (dir == "left") {
		currentDir++;
		if (currentDir >= 8)
			currentDir = 0;
	} else if (dir == "right") {
		currentDir--;
		if (currentDir < 0)
			currentDir = 7;
	}
}
void Player::testCollision(sf::Sprite object) {
	if (sprite.getGlobalBounds().intersects(object.getGlobalBounds())) {
		playerCollision = true;
	} else {
		playerCollision = false;
	}
}

bool Player::testCollision(sf::RectangleShape wall) {
	if (sprite.getGlobalBounds().intersects(wall.getGlobalBounds())) {
		wallCollision = true;
	} else {
		wallCollision = false;
	}
	return wallCollision;
}
void Player::draw() {
	data->window.draw(sprite);
}
void Player::spin(float elapsedTime, bool *doRespawn) {
	float factor = 0.15;
	if (elapsedTime >= 0 && elapsedTime < factor) {
		rotate("right");
		countSpin++;
	} else if (elapsedTime >= factor && elapsedTime < factor * 2) {
		rotate("right");
		countSpin++;
	} else if (elapsedTime >= factor * 2 && elapsedTime < factor * 3) {
		rotate("right");
		countSpin++;
	} else if (elapsedTime >= factor * 3 && elapsedTime < factor * 4) {
		rotate("right");
		countSpin++;
	} else if (elapsedTime >= factor * 4 && elapsedTime < factor * 5) {
		rotate("right");
		countSpin++;
	} else if (elapsedTime >= factor * 5 && elapsedTime < factor * 6) {
		rotate("right");
		countSpin++;
	} else if (elapsedTime >= factor * 6 && elapsedTime < factor * 7) {
		rotate("right");
		countSpin++;
	} else if (elapsedTime >= factor * 7 && elapsedTime < factor * 8) {
		rotate("right");
		countSpin++;
	}
	if (countSpin == 48) {
		isIdle = true;
		doSpin = false;
		*doRespawn = true;
		countSpin = 0;
	}
}
void Player::idle(float elapsedTime) {
	if (elapsedTime >= 0 && elapsedTime < 0.3) {
		frame = dirframes[currentDir] + 1;
	} else if (elapsedTime >= 0.3 && elapsedTime < 0.6) {
		frame = dirframes[currentDir] + 2;
	} else if (elapsedTime >= 0.6 && elapsedTime < 0.9) {
		frame = dirframes[currentDir] + 3;
	} else if (elapsedTime >= 0.9 && elapsedTime < 1.2) {
		frame = dirframes[currentDir];
	}
	std::stringstream path;
	path << texPath << frame << ".png";
	frameTex.loadFromFile(path.str());
}
void Player::animate(float elapsedTime) {
	std::stringstream path;
	if ((elapsedTime >= 0 && elapsedTime < 0.3)
			|| (elapsedTime >= 0.6 && elapsedTime < 0.9)) { //first frame
		if (sf::Keyboard::isKeyPressed(keyUp)
				|| sf::Keyboard::isKeyPressed(keyDown)
				|| sf::Keyboard::isKeyPressed(keyLeft)
				|| sf::Keyboard::isKeyPressed(keyRight)) {
			isIdle = false;
			if (currentDir == west || currentDir == east) {
				frame = dirframes[currentDir];
			} else {
				frame = dirframes[currentDir] + 4;
			}

		} else {
			isIdle = true;
		}
		path << texPath << frame << ".png";
		frameTex.loadFromFile(path.str());

	} else if ((elapsedTime >= 0.3 && elapsedTime < 0.6)
			|| (elapsedTime >= 0.9 && elapsedTime < 1.2)) { //second frame
		if (sf::Keyboard::isKeyPressed(keyUp)
				|| sf::Keyboard::isKeyPressed(keyDown)
				|| sf::Keyboard::isKeyPressed(keyLeft)
				|| sf::Keyboard::isKeyPressed(keyRight)) {
			isIdle = false;
			if (currentDir == west || currentDir == east) {
				frame = dirframes[currentDir] + 4;
			} else {
				frame = dirframes[currentDir] + 5;
			}

		} else {
			isIdle = true;
		}
		path << texPath << frame << ".png";
		frameTex.loadFromFile(path.str());
	}
}
void Player::update(float elapsedTime, bool *doRespawn) {
	if (!blockMovement) {
		move();
	}
	friction();
	if (!blockAnimation) {
		animate(elapsedTime);
	}
	if (isIdle) {
		idle(elapsedTime);
	}
	if (doSpin) {
		spin(elapsedTime, &*doRespawn);
	}
	if (playerCollision || wallCollision) {
		velocity.x = -velocity.x * 1.25;
		velocity.y = -velocity.y * 1.25;
	}
	sprite.move(velocity.x * data->dt * multiplier,
			velocity.y * data->dt * multiplier);
	sprite.setTexture(frameTex);
}

