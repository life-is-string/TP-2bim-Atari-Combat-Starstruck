/*
 * game.hpp
 *
 *  Created on: 3 de jun. de 2023
 *      Author: hayde
 */
#pragma once
#ifndef ENGINE_APPLICATION_HPP_
#define ENGINE_APPLICATION_HPP_
#include <Engine/gamedata.hpp>
#include <stdafx.hpp>
#include <Engine/statemachine.hpp>
#include <States/menuState.hpp>

class Application{
public:
	Application(int width, int height);
private:
	const float dt= 1.0/60; //60 updates per second (framerate)
	sf::Clock clock;
	GameDataRef game_data = std::make_shared<GameData>();

	void Run();
};




#endif /* ENGINE_APPLICATION_HPP_ */
