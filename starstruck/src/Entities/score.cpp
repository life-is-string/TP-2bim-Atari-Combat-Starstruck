/*
 * score.cpp
 *
 *  Created on: 3 de jul. de 2023
 *      Author: hayde
 */
#include <Entities/score.hpp>
void Score::init() {
	font.loadFromFile("assets/score.ttf");
	sf::FloatRect textbounds;
	for (int i = 0; i < 2; i++) {
		points[i].setFont(font);
		points[i].setString("0");
		points[i].setCharacterSize(100);
		textbounds = points[i].getLocalBounds();
		points[i].setOrigin(textbounds.width / 2, textbounds.height / 2);
	}
	points[0].setFillColor(sf::Color::Blue);
	points[1].setFillColor(sf::Color::Green);
	points[0].setPosition((ww / 2) - 400, 35);
	points[1].setPosition((ww / 2) + 400, 35);
}

void Score::update(int ast_points, int bilu_points) {
	points[0].setString(std::to_string(ast_points));
	points[1].setString(std::to_string(bilu_points));
}

