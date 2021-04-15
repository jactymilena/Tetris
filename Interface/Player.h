/*===================================
Auteur:         fona1101 elka0602 saej3101
Nom du fichier: Player.h
Date:           15 avril 2021
But:            Déclarer Player.h
====================================*/
#pragma once

#include <iostream>
#include <QObject>
#include <QWidget>
#include <QDebug>

class Player : public QWidget {
	Q_OBJECT
public:
	Player();
	Player(int score, std::string user);
	Player(const Player& p);
	int getScore();
	void setScore(int score);
	int getLevel();
	void setLevel(int level);
	std::string getUsername();
	void setUsername(std::string nom);
	bool getNameSetted();
	void setNameSetted(bool setted);
signals:
	void scoreChanged();
	void levelChanged();

private:
	int level;
	int score;
	std::string username;
	bool nameSetted;
};
