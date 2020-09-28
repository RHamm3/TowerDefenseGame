#pragma once

#include <SFML/Graphics.hpp>

#ifndef TOWER_H
#define TOWER_H

class Tower : public sf::CircleShape {
private:
	int cost;
	int damagePerHit;
	float attackSpeed;
	bool attackReady;
	float towerAttackTimer;
	float towerAttackTimerMax;
	//Range Circle
	sf::CircleShape range;
public:
	//Constructor
	Tower();


	//Setters and Getters
	void setCost(int cost);
	int getCost();

	void setDamagePerHit(int damage);
	int getDamagePerHit();

	void setAttackSpeed(float attackSpeed);
	float getAttackSpeed();

	void setAttackReady(bool attackReady);
	bool getAttackReady();

	void setTowerAttackTimer(float attTimer);
	float getTowerAttackTimer();

	void setTowerAttackTimerMax(float attTimerMax);
	float getTowerAttackTimerMax();

	void setRange(float range);
	float getRange();

	sf::CircleShape getRangeCircle();

	void setRangePos(sf::Vector2f pos);
	//void centerRangeOnMouse(sf::Vector2f center);

};

#endif

