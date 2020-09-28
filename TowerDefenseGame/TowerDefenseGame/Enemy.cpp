#include "Enemy.h"

Enemy::Enemy() {

	this->health = 30;
	this->speed = 2.5;
	this->type = 1;

}

void Enemy::setHealth(int health) {
	this->health = health;
}

int Enemy::getHealth() {
	return this->health;
}

void Enemy::setType(int type) {
	this->type = type;
}
int Enemy::getType() {
	return this->type;
}

void Enemy::setSpeed(float speed) {
	this->speed = speed;
}

float Enemy::getSpeed() {
	return this->speed;
}

