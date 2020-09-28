#pragma once

#include <SFML/Graphics.hpp>


#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public sf::RectangleShape {
private:
	int health;
	int type;
	float speed;
public:
	
	Enemy();

	void setHealth(int health);
	int getHealth();

	void setType(int type);
	int getType();

	void setSpeed(float speed);
	float getSpeed();
};

#endif

