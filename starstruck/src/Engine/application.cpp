/*c
 * game.cpp
 *
 *  Created on: 3 de jun. de 2023
 *      Author: hayde
 */
#include <Engine/application.hpp>

Application::Application(int width, int height) {
	sf::Image icon;
	icon.loadFromFile("assets/icon.png");
	game_data->window.create(sf::VideoMode(width, height), "Starstruck");
	game_data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	game_data->window.setFramerateLimit(60);
	game_data->window.setVerticalSyncEnabled(true);
	game_data->machine.addState(StateRef(new MenuState(game_data)));
	Run();
}
void Application::Run() {

	//Game loop

	while (game_data->window.isOpen()) {
		game_data->dt = clock.restart().asSeconds();
		game_data->machine.doChanges();
		game_data->machine.getActualState()->handleInput();
		game_data->machine.getActualState()->update();
		game_data->machine.getActualState()->draw();
	}
}

