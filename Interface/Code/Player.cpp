/*===================================
Auteur:         fona1101 elka0602 saej3101
Nom du fichier: Player.cpp
Date:           12 avril 2021
But:            Contient les informations pour un joueur
====================================*/

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

// Constructeur par copie
Player::Player(const Player& p) : QWidget()
{
	score = p.score;
	qDebug() << p.score;
	username = p.username;
	nameSetted = true;
	level = 0;
}

// Getter : retourne la valeur du score
int Player::getScore() {
	return score;
}

void Player::setScore(int score) {
	this->score = score;
	emit scoreChanged();
}

// Getter : retourne la valeur du level
int Player::getLevel() {
	return level;
}

// Setter : change la valeur du level selon le level rentré en paramètre
void Player::setLevel(int level) {
	this->level = level;
	emit levelChanged();
}

// Getter : retourne la valeur du username
std::string Player::getUsername() {
	return username;
}

// Setter : change la valeur du username selon le nom rentré en paramètre
void Player::setUsername(std::string nom) {
	this->username = nom;
}

bool Player::getNameSetted() {
	return nameSetted;
}

// Setter : change la valeur du namSetted selon le nom rentré en paramètre lorsque le username a été attribué
void Player::setNameSetted(bool setted) {
	this->nameSetted = setted;
}
