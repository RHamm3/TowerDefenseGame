#include "Game.h"

//Constructors
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initEnemies();
	this->initTowers();
	this->initFonts();
	this->initText();
}

Game::~Game() {
	delete this->window;
}

/***************PUBLIC FUNCTIONS***************/

//Updates Game
void Game::update() {

	this->pollEvents();
	this->updateMousePositions();
	this->updateText();
	this->updateTowers();
	this->updateEnemies();

}


/********************RENDER GAME OBJECTS********************/
void Game::render() {

	this->window->clear();

	//Draw Game Objects
	this->renderBackground();
	this->renderTowers(*this->window);
	this->renderEnemies(*this->window);
	this->renderText(*this->window);

	this->window->display();

}

/********************RENDER BACKGROUND********************/
void Game::renderBackground() {

	//Green
	this->background.setSize(sf::Vector2f(1920.f, 880.f));
	this->background.setFillColor(sf::Color(0, 204, 0));

	//First Straight
	this->path1.setPosition(sf::Vector2f(165.f, 0.f));
	this->path1.setSize(sf::Vector2f(100.f, 730.f));
	this->path1.setFillColor(sf::Color(160, 160, 160));

	//Second Straight
	this->path2.setPosition(sf::Vector2f(165.f, 645.f));
	this->path2.setSize(sf::Vector2f(550.f, 100.f));
	this->path2.setFillColor(sf::Color(160, 160, 160));

	//Third Straight
	this->path3.setPosition(sf::Vector2f(715.f, 185.f));
	this->path3.setSize(sf::Vector2f(100.f, 560.f));
	this->path3.setFillColor(sf::Color(160, 160, 160));

	//Fourth Straight
	this->path4.setPosition(sf::Vector2f(715.f, 165.f));
	this->path4.setSize(sf::Vector2f(535.f, 100.f));
	this->path4.setFillColor(sf::Color(160, 160, 160));

	//Fifth Straight
	this->path5.setPosition(sf::Vector2f(1215.f, 165.f));
	this->path5.setSize(sf::Vector2f(100.f, 170.f));
	this->path5.setFillColor(sf::Color(160, 160, 160));

	//Sixth Straight
	this->path6.setPosition(sf::Vector2f(1215.f, 305.f));
	this->path6.setSize(sf::Vector2f(800.f, 100.f));
	this->path6.setFillColor(sf::Color(160, 160, 160));

	//Shop Background
	renderShop(*this->window);

	this->window->draw(background);
	this->window->draw(path1);
	this->window->draw(path2);
	this->window->draw(path3);
	this->window->draw(path4);
	this->window->draw(path5);
	this->window->draw(path6);

}

/********************RENDER SHOP********************/
void Game::renderShop(sf::RenderTarget& target) {

	this->shopBackground.setPosition(sf::Vector2f(0.f, 880.f));
	this->shopBackground.setSize(sf::Vector2f(1920.f, 200.f));
	this->shopBackground.setFillColor(sf::Color::Black);

	sf::CircleShape shopTowerOne;

	shopTowerOne.setRadius(45.f);
	shopTowerOne.setFillColor(sf::Color::Magenta);
	shopTowerOne.setPosition(sf::Vector2f(200.f, 950.f));

	this->window->draw(shopBackground);
	this->window->draw(shopTowerOne);

}

/********************RENDER ENEMIES********************/
void Game::renderEnemies(sf::RenderTarget& target) {

	for (auto& e : this->enemies) {

		sf::Text enemyHealth;		
		enemyHealth.setString(std::to_string(e.getHealth()));
		enemyHealth.setFont(this->font);
		enemyHealth.setCharacterSize(20);
		enemyHealth.setFillColor(sf::Color::Red);
		enemyHealth.setPosition(sf::Vector2f(e.getPosition().x, e.getPosition().y - 20));
		target.draw(enemyHealth);
		target.draw(e);
	}

}

/********************UPDATE ENEMIES********************/
void Game::updateEnemies() {

	//Updates Spawn Timers and Spawns Enemies

	//If Total Enemies Is Less Than Max
	if (this->enemies.size() < this->maxEnemies) {
		//Spawn Enemy and Reset Timer
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->enemySpawnTimer = 0.f;
			this->spawnEnemy((rand() % 4) + 1);
		}
		//Else Add to Timer
		else {
			this->enemySpawnTimer += 15.f;
		}
	}

	//Moves Enemies
	for (int i = 0; i < this->enemies.size(); i++) {
		if (this->enemies[i].getPosition().x >= 1250 && this->enemies[i].getPosition().y == 340) {
			this->enemies[i].move(this->enemies[i].getSpeed(), 0.f);
		}
		else if (this->enemies[i].getPosition().x == 1250 && this->enemies[i].getPosition().y >= 200) {
			this->enemies[i].move(0.f, this->enemies[i].getSpeed());
		}
		else if (this->enemies[i].getPosition().x >= 750 && this->enemies[i].getPosition().y == 200) {
			this->enemies[i].move(this->enemies[i].getSpeed(), 0.f);
		}
		else if (this->enemies[i].getPosition().x == 750 && this->enemies[i].getPosition().y <= 680) {
			this->enemies[i].move(0.f, this->enemies[i].getSpeed() * -1);
		}
		else if (this->enemies[i].getPosition().y == 680) {
			this->enemies[i].move(this->enemies[i].getSpeed(), 0.f);
		}
		else {
			this->enemies[i].move(0.f, this->enemies[i].getSpeed());
		}

	}

	//If Enemies Are in Range of a Tower, Take Damage
	for (int i = 0; i < this->towers.size(); i++) {
		for (int j = 0; j < this->enemies.size(); j++) {
			if (this->towers[i].getRangeCircle().getGlobalBounds().contains(this->enemies[j].getPosition()) && towers[i].getAttackReady()) {
				enemies[j].setHealth(enemies[j].getHealth() - 5);
				if (enemies[j].getHealth() <= 0) {
					enemies.erase(enemies.begin() + j);
				}
			}
		}
	}

	//If Enemies reach the end
	for (int i = 0; i < this->enemies.size(); i++) {
		if (this->enemies[i].getPosition().x == 1920) {
			if (this->enemies[i].getType() == 1) {
				life -= 2;
			}
			else if (this->enemies[i].getType() == 2) {
				life--;
			}
			else if (this->enemies[i].getType() == 3) {
				life -= 5;
			}
			else if (this->enemies[i].getType() == 4) {
				life -= 3;
			}
		}
	}

}

/********************SPAWN ENEMIES********************/
void Game::spawnEnemy(int enemType) {
	this->enemyTypeOne.setPosition(200.f, 0.f);
	this->enemyTypeTwo.setPosition(200.f, 0.f);
	this->enemyTypeThree.setPosition(200.f, 0.f);
	this->enemyTypeFour.setPosition(200.f, 0.f);

	if (enemType == 1) {
		this->enemies.push_back(this->enemyTypeOne);
	}
	else if (enemType == 2) {
		this->enemies.push_back(this->enemyTypeTwo);
	}
	else if (enemType == 3) {
		this->enemies.push_back(this->enemyTypeThree);
	}
	else if (enemType == 4) {
		this->enemies.push_back(this->enemyTypeFour);
	}
}

/********************RENDER TOWERS********************/
void Game::renderTowers(sf::RenderTarget& target) {

	//If player has clicked on a tower from shop
	if (dragging) {
		//Set Range Circle to Follow Mouse and Center on Mouse
		towerTemp.setRangePos(sf::Vector2f(this->mousePosView.x - towerTemp.getRange(), this->mousePosView.y - towerTemp.getRange()));
		
		//Display Tower
		towerTemp.setOrigin(sf::Vector2f(45.f, 45.f));
		towerTemp.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y));

		target.draw(towerTemp.getRangeCircle());
		target.draw(towerTemp);
	}
	for (auto& e : this->towers) {
		target.draw(e);
	}
}

/********************UPDATE TOWERS********************/
void Game::updateTowers() {

	for (int i = 0; i < this->towers.size(); i++) {
		if (this->towers[i].getTowerAttackTimer() >= this->towers[i].getTowerAttackTimerMax()) {
			this->towers[i].setAttackReady(true);
			this->towers[i].setTowerAttackTimer(0.f);
		}
		else {
			this->towers[i].setTowerAttackTimer(this->towers[i].getTowerAttackTimer() + 5.f);
		}
	}

}

/********************RENDER TEXT********************/
void Game::renderText(sf::RenderTarget& target) {

	target.draw(this->uiText);
	target.draw(this->shopTowerOneText);
	target.draw(this->shopText);

	if ((this->mousePosView.x >= 175 && this->mousePosView.x <= 350) && (this->mousePosView.y >= 900)) {
		this->shopTowerOneInfo.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y));
		target.draw(this->shopTowerOneInfo);
	}

}

/********************UPDATE TEXT********************/
void Game::updateText() {

	std::stringstream ss;
	std::stringstream shop;
	std::stringstream shopTowerOne;
	std::stringstream shopTowerOneStats;

	ss << "Life: " << this->life << "\n"
		<< "Round: " << this->round << "\n"
		<< "Money: " << this->money << "\n";

	shop << "SHOP";

	shopTowerOne << "Tower Type One";
	shopTowerOneStats << "Damage Per Hit: 5 \nAttack Speed: 1 \nRange: 250";

	this->uiText.setString(ss.str());
	this->shopText.setString(shop.str());
	this->shopTowerOneText.setString(shopTowerOne.str());
	this->shopTowerOneInfo.setString(shopTowerOneStats.str());

}

/********************POLL EVENTS********************/
void Game::pollEvents() {

	while (this->window->pollEvent(this->event)) {
		switch (this->event.type) {
		//If Close is Clicked, Close
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			//If Escape is pressed while tower dragging, stop dragging
			if (this->event.key.code == sf::Keyboard::Escape && dragging) {
				dragging = false;
			}
		case sf::Event::MouseButtonPressed:
			if (this->event.mouseButton.button == sf::Mouse::Left) {
				if (!dragging) {
					//If Left Click is Pressed On Tower One in the Shop, and player has money, start dragging
					if ((this->mousePosView.x >= 175 && this->mousePosView.x <= 350) && (this->mousePosView.y >= 900) && this->money >= 100) {
						towerTemp = this->towerTypeOne;
						dragging = true;
					}
				}
				else if (dragging) {
					//If Already Dragging and Left Click is Pressed, Place Tower and Subtract 100 Money
					towers.push_back(towerTemp);
					this->money -= 100;
					//If Money is Now Less Than 100, Stop Dragging
					if (this->money < 100) {
						dragging = false;
					}
				}
			}
			break;
		}
	}

}

/********************UPDATE MOUSE POSITIONS********************/
void Game::updateMousePositions() {
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

const bool Game::running() const {
	return this->window->isOpen();
}

/********************INITIALIZATION FUNCTIONS********************/
void Game::initVariables() {

	this->window = nullptr;
	this->life = 25;
	this->round = 1;
	this->money = 1000;
	this->dragging = false;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax; 
	this->maxEnemies = 5;

}

void Game::initWindow() {

	this->vidMode.height = 1080;
	this->vidMode.width = 1920;
	this->window = new sf::RenderWindow(this->vidMode, "Ryan's Tower Defense Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

}

void Game::initEnemies() {

	this->enemyTypeOne.setSize(sf::Vector2f(30.f, 30.f));
	this->enemyTypeOne.setFillColor(sf::Color::Red);

	this->enemyTypeTwo.setSize(sf::Vector2f(10.f, 10.f));
	this->enemyTypeTwo.setFillColor(sf::Color::Blue);
	this->enemyTypeTwo.setSpeed(5);
	this->enemyTypeTwo.setHealth(15);
	this->enemyTypeTwo.setType(2);

	this->enemyTypeThree.setSize(sf::Vector2f(50.f, 50.f));
	this->enemyTypeThree.setFillColor(sf::Color::Black);
	this->enemyTypeThree.setSpeed(1);
	this->enemyTypeThree.setHealth(50);
	this->enemyTypeThree.setType(3);

	this->enemyTypeFour.setSize(sf::Vector2f(30.f, 30.f));
	this->enemyTypeFour.setFillColor(sf::Color::Yellow);
	this->enemyTypeFour.setHealth(40);
	this->enemyTypeFour.setType(4);

}

void Game::initTowers() {

	this->towerTypeOne.setFillColor(sf::Color::Magenta);
	this->towerTypeOne.setRadius(45.f);
	this->towerTypeOne.setDamagePerHit(5);
	this->towerTypeOne.setAttackSpeed(1.f);

}

void Game::initFonts() {

	this->font.loadFromFile("Fonts/Dosis-Bold.ttf");

}

void Game::initText() {

	this->uiText.setFont(this->font);
	this->uiText.setFillColor(sf::Color::Black);
	this->uiText.setCharacterSize(25);
	this->uiText.setString("NONE");

	this->shopText.setFont(this->font);
	this->shopText.setFillColor(sf::Color::White);
	this->shopText.setCharacterSize(50);
	this->shopText.setPosition(sf::Vector2f(25.f, 950.f));
	this->shopText.setString("NONE");

	this->shopTowerOneText.setFont(this->font);
	this->shopTowerOneText.setFillColor(sf::Color::White);
	this->shopTowerOneText.setCharacterSize(20);
	this->shopTowerOneText.setString("NONE");
	this->shopTowerOneText.setPosition(sf::Vector2f(175.f, 900.f));

	this->shopTowerOneInfo.setFont(this->font);
	this->shopTowerOneInfo.setFillColor(sf::Color::White);
	this->shopTowerOneInfo.setCharacterSize(20);
	this->shopTowerOneInfo.setString("NONE");
	this->shopTowerOneInfo.setPosition(sf::Vector2f(0.f, 0.f));

}
