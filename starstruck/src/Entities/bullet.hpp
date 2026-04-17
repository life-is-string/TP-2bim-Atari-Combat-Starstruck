/*
 * bullet.hpp
 *
 *  Created on: 2 de jul. de 2023
 *      Author: hayde
 */

#ifndef ENTITIES_BULLET_HPP_
#define ENTITIES_BULLET_HPP_
#include <stdafx.hpp>
#include <Engine/gamedata.hpp>
#include <Entities/Entity.hpp>
class Bullet : public Entity{
public:
	Bullet(int currentDir, sf::Sprite origin, GameDataRef data, std::string texPath);
	void init();
	void update(float dt);
	void draw();
	bool testCollision(sf::Sprite target);
	bool testCollision(sf::RectangleShape wall);
	sf::Sprite bullet;
private:
	GameDataRef data;
	std::string texPath;
	sf::Vector2f pos;
	sf::Texture texture;
	sf::Vector2f velocity;
	sf::Sprite origin;
	int currentDir;
	float angle = 0, angleRad = 0, vel = 3, x, y;

};




#endif /* ENTITIES_BULLET_HPP_ */
