#pragma once

#include <iostream>
#include <QString>

class Player {

public:
	Player();
	Player(int score, std::string user);
	int getScore();
	void setScore(int score);
	std::string getUsername();
	void setUsername(std::string nom);

private:
	int score;
	std::string username;
};



