#pragma once

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Tower.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

class Game {

private:
	/**********Variables**********/
	sf::RenderWindow* window;
	sf::VideoMode vidMode;
	sf::Event event;

	/**********Game Objects**********/
	std::vector<Enemy> enemies;
	Enemy enemyTypeOne;
	Enemy enemyTypeTwo;
	Enemy enemyTypeThree;
	Enemy enemyTypeFour;

	std::vector<Tower> towers;
	Tower towerTemp;
	Tower towerTypeOne;

	sf::RectangleShape background;
	sf::RectangleShape path1;
	sf::RectangleShape path2;
	sf::RectangleShape path3;
	sf::RectangleShape path4;
	sf::RectangleShape path5;
	sf::RectangleShape path6;
	sf::RectangleShape shopBackground;

	/**********Game Logic**********/
	int life;
	int round;
	int money;
	bool dragging;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);

	/**********Resources**********/
	sf::Font font;

	/**********Text**********/
	sf::Text uiText;
	sf::Text shopText;
	sf::Text shopTowerOneText;
	sf::Text shopTowerOneInfo;

	/**********Mouse Positions**********/
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	/**********Private Functions**********/
	void initVariables();
	void initWindow();
	void initEnemies();
	void initTowers();
	void initFonts();
	void initText();
public:
	//Constructors and Destructors
	Game();
	virtual ~Game();

	//Functions
	void update();
	void render();

	void renderBackground();

	void renderEnemies(sf::RenderTarget& target);
	void updateEnemies();

	void renderTowers(sf::RenderTarget& target);
	void updateTowers();

	void renderShop(sf::RenderTarget& target);

	void renderText(sf::RenderTarget& target);
	void updateText();

	void spawnEnemy(int enemType);

	void pollEvents();
	void updateMousePositions();

	//Accessors
	const bool running() const;
};


#endif

