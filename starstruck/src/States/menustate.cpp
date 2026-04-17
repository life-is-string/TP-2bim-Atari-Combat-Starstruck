/*
 * menu.cpp
 *
 *  Created on: 9 de jun. de 2023
 *      Author: hayde
 */
#include <iostream> //temporary
#include <States/menuState.hpp>

MenuState::MenuState(GameDataRef data) {
	this->data = data;
	selected_index = 0;
	enter = false;
}
void MenuState::init() {

	data->volume=17;
	bg_tex.loadFromFile("assets/menu_bgd.png");
	background.setTexture(bg_tex);
	tut_tex.loadFromFile("assets/tutorial.png");
	tutorial.setTexture(tut_tex);
	arcadefont.loadFromFile("assets/arcade.ttf");
	menuMusic.openFromFile("assets/highway_to_hell.wav");
	menuMusic.setLoop(true);
	menuMusic.setVolume(40);
	menuMusic.play();
	enterBuf.loadFromFile("assets/enter_menu.wav");
	enterOption.setBuffer(enterBuf);
	selectBuf.loadFromFile("assets/switch.ogg");
	select.setBuffer(selectBuf);

	menu[0].setString("Play");
	menu[1].setString("Options");
	menu[2].setString("Exit");
	title.setString("STARSTRUCK");

	sf::FloatRect textbounds;
	titlefont.loadFromFile("assets/menu_font.ttf");
	title.setFont(titlefont);
	title.setCharacterSize(160);
	volumeText.setFont(arcadefont);
	volumeText.setFillColor(sf::Color::Black);
	volumeText.setCharacterSize(100);
	title.setCharacterSize(120);
	textbounds = title.getLocalBounds();
	title.setOrigin(textbounds.width / 2, textbounds.height / 2);
	title.setFillColor(sf::Color { 185, 205, 212 });
	title.setPosition(ww / 2, 160);

	float distance = -100;
	for (int i = 0; i < 3; i++) {
		menu[i].setFont(arcadefont);
		menu[i].setFillColor(unselected);
		menu[i].setCharacterSize(100);
		textbounds = menu[i].getLocalBounds();
		menu[i].setOrigin(textbounds.width / 2, textbounds.height / 2);
		menu[i].setPosition(ww / 2, wh / 2 + distance);
		distance += 100;
	}

	selected_index = 0;
	menu[selected_index].setFillColor(selected);

}
void MenuState::draw() {
	data->window.clear(sf::Color::White);
	data->window.draw(background);
	if (inOptions) {
		data->window.draw(tutorial);
		data->window.draw(volumeText);
	} else {
		data->window.draw(title);
		for (int i = 0; i < 3; i++) {
			data->window.draw(menu[i]);
		}
	}
	data->window.display();
}
void MenuState::setVolume(int i) {
	sf::FloatRect textbounds;
	float volume = menuMusic.getVolume();
	if(i == -1){
		 volume -= 10;
		 if(volume < 0){
			 volume = 0;
		 }
		 volumeText.setString(std::to_string(static_cast<int>(std::round(volume))));
		 textbounds = volumeText.getLocalBounds();
		 volumeText.setOrigin(textbounds.width / 2, textbounds.height / 2);
		 volumeText.setPosition(ww / 2, 350);
		 menuMusic.setVolume(volume);
	}else if(i == 1){
		volume += 10;
		if(volume > 100){
			volume = 100;
		}

		volumeText.setString(std::to_string(static_cast<int>(std::round(volume)))) ;
		textbounds = volumeText.getLocalBounds();
		volumeText.setOrigin(textbounds.width / 2, textbounds.height / 2);
		volumeText.setPosition(ww / 2, 350);
		menuMusic.setVolume(volume);
	}
	data->volume = volume;
}

void MenuState::update() {
	if (selected_index > 0 && moveUp) { //it will only move up when current selected option is not the first one
		select.play();
		menu[selected_index].setFillColor(unselected);
		selected_index--;
		menu[selected_index].setFillColor(selected);
		moveUp = false;
	}
	if (selected_index < 2 && moveDown) { //it will only move up when current selected option is not the last one
		select.play();
		menu[selected_index].setFillColor(unselected);
		selected_index++;
		menu[selected_index].setFillColor(selected);
		moveDown = false;
	}
	if (enter) {
		options();
	}
}

void MenuState::handleInput() {
	sf::Event event;
	while (data->window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			data->window.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Up && !inOptions) {
				moveUp = true;
				break;
			}
			if (event.key.code == sf::Keyboard::Down && !inOptions) {
				moveDown = true;
				break;
			}
			if (event.key.code == sf::Keyboard::Enter && !inOptions) {
				enter = true;
				enterOption.play();
				break;
			}
			if (event.key.code == sf::Keyboard::Escape && inOptions) {
				inOptions = false;
				break;
			}
			if (event.key.code == sf::Keyboard::N && inOptions) {
				setVolume(-1);
				break;
			}
			if (event.key.code == sf::Keyboard::M && inOptions) {
				setVolume(1);
				break;
			}
		}

	}
}

void MenuState::options() { //happens when entering an option
	switch (selected_index) { //current index entered
	case 0:
		std::cout << "Play!";
		menuMusic.setLoop(false);
		menuMusic.stop();
		data->machine.addState(StateRef(new GameState(data)), true);
		enter = false;
		break;
	case 1:
		std::cout << "Options!";
		inOptions = true;
		enter = false;
		break;
	case 2:
		data->window.close();
		break;
	}
}

