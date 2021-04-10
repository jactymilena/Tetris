#include "Player.h"


Player::Player() {
	score = 0;
	username = "";
}

Player::Player(int score, std::string username) {
	this->score = score;
	this->username = username;
}

int Player::getScore() {
	return score;
}

void Player::setScore(int score) {
	this->score = score;
}

std::string Player::getUsername() {
	return username;
}

void Player::setUsername(std::string nom) {
	this->username = nom;
}
