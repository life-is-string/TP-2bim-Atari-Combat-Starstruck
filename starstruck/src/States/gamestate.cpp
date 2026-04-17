/*
 * gamestate.cpp
 *
 *  Created on: 14 de jun. de 2023
 *      Author: hayde
 */
#include <States/gameState.hpp>

GameState::GameState(GameDataRef data) {
	this->data = data;
	elapsedTime = 0;
}

void GameState::init() {
	elapsedTime = frametime.restart().asSeconds();
	levelMusic.openFromFile("assets/interstellar.wav");
	levelMusic.setVolume(data->volume);
	levelMusic.setLoop(true);
	levelMusic.play();
	Player astronaut(data, "wasd", "assets/astronaut/"), bilu(data, "arrow",
			"assets/etbilu/");
	players.push_back(astronaut);
	players.push_back(bilu);
	players.at(0).init();
	players.at(1).init();
	pewbuf.loadFromFile("assets/pew.wav");
	hitbuf.loadFromFile("assets/hit.ogg");
	hitsound.setBuffer(hitbuf);
	pewsound.setBuffer(pewbuf);
	score.init();
	map.init(level);
	players.at(0).sprite.setPosition(50, wh / 2);
	players.at(1).sprite.setPosition(ww - 105, wh / 2);
}
void GameState::pause(int damaged) {
	for (int i = 0; i < players.size(); i++) {
		players.at(i).blockMovement = true;
		players.at(i).blockRot = true;
		players.at(i).blockBullet = true;
		players.at(i).blockAnimation = true;
	}
	players.at(damaged).doSpin = true;
	this->damaged = damaged;
}
void GameState::resume() {
	std::srand(time(NULL));
	int corner;
	do {
		corner = std::rand() % 4 + 1;
	} while (corner == corner_old);
	corner_old = corner;
	sf::Vector2f pos;
	switch (corner) {
	case 1:
		pos.x = 50;
		pos.y = 160.0;
		break;
	case 2:
		pos.x = ww - 105;
		pos.y = 160.0;
		break;
	case 3:
		pos.x = ww - 105;
		pos.y = wh - 105;
		break;
	case 4:
		pos.x = 50;
		pos.y = wh - 105;
		break;
	}
	players.at(damaged).sprite.setPosition(pos);
	for (int i = 0; i < players.size(); i++) {
		players.at(i).blockMovement = false;
		players.at(i).blockRot = false;
		players.at(i).blockBullet = false;
		players.at(i).blockAnimation = false;
	}
}
void GameState::update() {
	if ((ast_points == maxPoints || bilu_points == maxPoints) && !players.at(damaged).doSpin) {
		doRespawn = false;
		level++;
		if (level > 3) {
			level = 1;
		}
		if(level == 1){
			maxPoints = 5;
			levelMusic.stop();
			levelMusic.openFromFile("assets/interstellar.wav");
			levelMusic.play();
			bg = {157, 121, 188};
		}else if(level == 2){
			maxPoints = 7;
			levelMusic.stop();
			levelMusic.openFromFile("assets/crawling.wav");
			levelMusic.play();
			bg = {83, 164, 181};
		}else if (level == 3){
			maxPoints = 10;
			levelMusic.stop();
			levelMusic.openFromFile("assets/master_of_puppets.wav");
			levelMusic.play();
			bg = {180, 37, 41};
		}
		map.init(level);
		players.at(0).sprite.setPosition(50, wh / 2);
		players.at(1).sprite.setPosition(ww - 105, wh / 2);
		ast_points = 0;
		bilu_points = 0;
		for (int i = 0; i < players.size(); i++) {
			players.at(i).blockMovement = false;
			players.at(i).blockRot = false;
			players.at(i).blockBullet = false;
			players.at(i).blockAnimation = false;
		}
	}
	if (doRespawn) {
		resume();
		doRespawn = false;
	}
	if (elapsedTime >= 1.2) {
		elapsedTime = frametime.restart().asSeconds();
	}
	elapsedTime = frametime.getElapsedTime().asSeconds();
	starCooldown += data->dt;
	rayCooldown += data->dt;
	for (int i = 0; i < stars.size(); i++) {
		stars[i].update(data->dt);
		if (stars[i].testCollision(players.at(1).sprite)) {
			stars.erase(std::next(stars.begin(), i));
			pause(1);
			hitsound.play();
			ast_points++;
		}

	};
	for (int i = 0; i < rays.size(); i++) {
		rays[i].update(data->dt);
		if (rays[i].testCollision(players.at(0).sprite)) {
			rays.erase(std::next(rays.begin(), i));
			pause(0);
			hitsound.play();
			bilu_points++;
		}
	};

	for (int i = 0; i < map.walls.size(); i++) {
		for (int j = 0; j < stars.size(); j++) {
			if (stars[j].testCollision(map.walls[i])) {
				stars.erase(std::next(stars.begin(), j));
				break;
			}
		}
		for (int j = 0; j < rays.size(); j++) {
			if (rays[j].testCollision(map.walls[i])) {
				rays.erase(std::next(rays.begin(), j));
				break;
			}
		}
	};

	for (int i = 0; i < map.walls.size(); i++) {
		if (players.at(1).testCollision(map.walls[i])
				|| players.at(0).testCollision(map.walls[i]))
			break;
	};

	players.at(0).testCollision(players.at(1).sprite);
	players.at(1).testCollision(players.at(0).sprite);
	players.at(0).update(elapsedTime, &doRespawn);
	players.at(1).update(elapsedTime, &doRespawn);
	score.update(ast_points, bilu_points);
}
void GameState::draw() {
	data->window.clear(bg);
	for (int i = 0; i < map.walls.size(); i++) {
		data->window.draw(map.walls[i]);
	};
	for (int i = 0; i < stars.size(); i++) {
		stars[i].draw();
	};
	for (int i = 0; i < rays.size(); i++) {
		rays[i].draw();
	};
	players.at(0).draw();
	players.at(1).draw();
	for (int i = 0; i < 2; i++) {
		data->window.draw(score.points[i]);
	}
	data->window.display();
}
void GameState::handleInput() {
	sf::Event event;
	while (data->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			data->window.close();
		}
		if (event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::C) {
			if (!players.at(0).blockRot) {
				players.at(0).rotate("left");
			}
		}
		if (event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::V) {
			if (!players.at(0).blockRot) {
				players.at(0).rotate("right");
			}
		}
		if (event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::Comma) {
			if (!players.at(1).blockRot) {
				players.at(1).rotate("left");
			}
		}
		if (event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::Period) {
			if (!players.at(1).blockRot) {
				players.at(1).rotate("right");
			}
		}
		if (event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::B) {
			if (starCooldown >= 0.6 && !players.at(0).blockBullet) {
				starCooldown = 0;
				pewsound.play();
				Bullet b1(players.at(0).currentDir, players.at(0).sprite, data,
						"assets/star.png");
				b1.init();
				stars.push_back(b1);
			}
		}
		if (event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::RControl) {
			if (rayCooldown >= 0.6 && !players.at(1).blockBullet) {
				rayCooldown = 0;
				pewsound.play();
				Bullet b2(players.at(1).currentDir, players.at(1).sprite, data,
						"assets/ray.png");
				b2.init();
				rays.push_back(b2);
			}
		}
	}
}

