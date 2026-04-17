/*
 * map.cpp
 *
 *  Created on: 2 de jul. de 2023
 *      Author: hayde
 */
#include <Entities/map.hpp>
void Map::init(int level) {
	walls.clear();
	if (level == 1) {
		for (int l = 0; l < 22; l++) {
			for (int c = 0; c < 32; c++) {
				if (level1[l][c] == 1) {
					sf::RectangleShape wall(sf::Vector2f(40, 40));
					wall.setPosition(c * wall.getSize().x,
							l * wall.getSize().y);
					wall.setFillColor(sf::Color(63, 28, 60));
					walls.push_back(wall);
				}
			}
		}
	} else if (level == 2) {
		for (int l = 0; l < 22; l++) {
			for (int c = 0; c < 32; c++) {
				if (level2[l][c] == 1) {
					sf::RectangleShape wall(sf::Vector2f(40, 40));
					wall.setPosition(c * wall.getSize().x,
							l * wall.getSize().y);
					wall.setFillColor(sf::Color(255, 95, 93));
					walls.push_back(wall);
				}
			}
		}
	} else if (level == 3) {
		for (int l = 0; l < 22; l++) {
			for (int c = 0; c < 32; c++) {
				if (level3[l][c] == 1) {
					sf::RectangleShape wall(sf::Vector2f(40, 40));
					wall.setPosition(c * wall.getSize().x,
							l * wall.getSize().y);
					wall.setFillColor(sf::Color(250, 127, 119));
					walls.push_back(wall);
				}
			}
		}
	}
}

