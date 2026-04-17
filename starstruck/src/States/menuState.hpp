/*
 * menu.hpp
 *
 *  Created on: 9 de jun. de 2023
 *      Author: hayde
 */
#pragma once
#ifndef STATES_MENUSTATE_HPP_
#define STATES_MENUSTATE_HPP_
#include <Engine/gamedata.hpp>
#include <States/gameState.hpp>
#include <Engine/statemachine.hpp>
#include <stdafx.hpp>


class MenuState: public State {
public:
	MenuState(GameDataRef data);
	void init();
	void draw();
	void handleInput();
	void options();
	void setVolume(int i);
	//void update();
	void update();
	//void handleInput();

private:
	GameDataRef data;
	sf::Music menuMusic;
	sf::SoundBuffer selectBuf, enterBuf;
	sf::Sound select, enterOption;
	sf::Font arcadefont, titlefont;
	sf::Text menu[3], title, volumeText;
	sf::Sprite background, tutorial;
	sf::Texture bg_tex, tut_tex;
	int selected_index;
	sf::Color unselected{255,255,255}; //white
	sf::Color selected{0,255,0}; //green
	bool moveUp = false, moveDown = false, enter = false, inOptions = false;
};

#endif /* STATES_MENUSTATE_HPP_ */
