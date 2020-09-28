#include "Tower.h"

Tower::Tower() {
	this->cost = 100;
	this->towerAttackTimer = 0;
	this->towerAttackTimerMax = 1000;
	this->range.setRadius(250);
	this->range.setFillColor(sf::Color(255, 255, 255, 170));
}

//Setters and Getters
void Tower::setCost(int cost) {
	this->cost = cost;
}

int Tower::getCost() {
	return this->cost;
}

void Tower::setDamagePerHit(int damage) {
	this->damagePerHit = damage;
}

int Tower::getDamagePerHit() {
	return this->damagePerHit;
}

void Tower::setAttackSpeed(float attackSpeed) {
	this->attackSpeed = attackSpeed;
}

float Tower::getAttackSpeed() {
	return this->attackSpeed;
}

void Tower::setAttackReady(bool attackReady) {
	this->attackReady = attackReady;
}

bool Tower::getAttackReady() {
	return this->attackReady;
}

void Tower::setTowerAttackTimer(float attTimer) {
	this->towerAttackTimer = attTimer;
}

float Tower::getTowerAttackTimer() {
	return this->towerAttackTimer;
}

void Tower::setTowerAttackTimerMax(float attTimerMax) {
	this->towerAttackTimerMax = attTimerMax;
}

float Tower::getTowerAttackTimerMax() {
	return this->towerAttackTimerMax;
}

void Tower::setRange(float range) {
	this->range.setRadius(range);
}

float Tower::getRange() {
	return this->range.getRadius();
}

sf::CircleShape Tower::getRangeCircle() {
	return this->range;
}

void Tower::setRangePos(sf::Vector2f pos) {
	this->range.setPosition(pos);
}

/*
void Tower::centerRangeOnMouse(sf::Vector2f center) {
	this->range.setOrigin(center);
}
*/
