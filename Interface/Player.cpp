#include "Player.h"


Player::Player() : QWidget() {
	score = 0;
	level = 0;
	username = "";
	nameSetted = false;
}

Player::Player(int score, std::string username) : QWidget() {
	this->score = score;
	this->username = username;
	nameSetted = true;
	level = 0;
}

int Player::getScore() {
	return score;
}

void Player::setScore(int score) {
	this->score = score;
	emit scoreChanged();
}

int Player::getLevel() {
	return level;
}

void Player::setLevel(int level) {
	qDebug() << level;
	this->level = level;
	emit levelChanged();
}

std::string Player::getUsername() {
	return username;
}

void Player::setUsername(std::string nom) {
	this->username = nom;
}

bool Player::getNameSetted() {
	return nameSetted;
}

void Player::setNameSetted(bool setted) {
	this->nameSetted = setted;
}
