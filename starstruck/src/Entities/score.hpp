/*
 * score.hpp
 *
 *  Created on: 3 de jul. de 2023
 *      Author: hayde
 */

#ifndef ENTITIES_SCORE_HPP_
#define ENTITIES_SCORE_HPP_
#include <Entities/entity.hpp>
#include <stdafx.hpp>
class Score : public Entity{
public:
	void init();
	void update(int ast_points, int bilu_points);
	sf::Text points[2];
private:
	sf::Font font;
};



#endif /* ENTITIES_SCORE_HPP_ */
