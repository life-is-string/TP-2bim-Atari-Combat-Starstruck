/*
 * Player.hpp
 *
 *  Created on: 19 de jun. de 2023
 *      Author: hayde
 */

#ifndef ENTITIES_PLAYER_HPP_
#define ENTITIES_PLAYER_HPP_
#include <Entities/entity.hpp>
#include <Engine/gamedata.hpp>
class Player : public Entity{
public:
	Player(GameDataRef data, std::string keyset, std::string texPath);
	void init();
	void update(float elapsedTime, bool *doRespawn);
	void draw();
	void spin(float elapsedTime, bool *doRespawn);
	void move();
	void rotate(std::string dir);
	void friction();
	void animate(float elapsedTime);
	void idle(float elapsedTime);
	void testCollision(sf::Sprite object);
	bool testCollision(sf::RectangleShape wall);
	sf::Sprite sprite;
	int currentDir = 0;
	bool blockMovement = false, blockRot = false, isIdle = true, blockBullet = false, doSpin = false,
			blockAnimation = false;
private:
	GameDataRef data;
	std::string keyset, texPath;
	sf::Texture frameTex;
	sf::Keyboard::Key keyUp, keyDown, keyRight, keyLeft;
	int dirframes[8] = { 0, 6, 12, 17, 23, 29, 35, 40}, frame = NULL, countSpin = 0;
	sf::Vector2f velocity, dir;
	float acc = 1, maxVelocity = 3, drag = 0.5, multiplier = 60;
	bool playerCollision = false, wallCollision = false;

};



#endif /* ENTITIES_PLAYER_HPP_ */
