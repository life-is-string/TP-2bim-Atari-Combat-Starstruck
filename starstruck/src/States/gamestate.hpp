/*
 * menu.hpp
 *
 *  Created on: 9 de jun. de 2023
 *      Author: hayde
 */
#pragma once
#ifndef STATES_GAMESTATE_HPP_
#define STATES_GAMESTATE_HPP_
#include <Engine/gamedata.hpp>
#include <Entities/bullet.hpp>
#include <Engine/state.hpp>
#include <stdafx.hpp>
#include <Entities/player.hpp>
#include <Entities/map.hpp>
#include <Entities/score.hpp>

class GameState: public State {
public:
	GameState(GameDataRef data);
	void init();
	void update();
	void handleInput();
	void draw();
	void pause(int damaged);
	void resume();

private:
	GameDataRef data;
	sf::SoundBuffer hitbuf, pewbuf;
	sf::Sound hitsound, pewsound;
	sf::Music levelMusic;
	Map map;
	sf::Color bg{157, 121, 188};
	Score score;
	bool doRespawn = NULL;
	int ast_points = 0, bilu_points = 0, damaged = 0, corner_old = 0, level = 1, maxPoints = 5;
	float starCooldown = 0, rayCooldown = 0, elapsedTime;
	sf::Clock frametime;
	std::vector<Player> players;
	std::vector<Bullet> stars;
	std::vector<Bullet> rays;
};

#endif /* STATES_GAMESTATE_HPP_ */
