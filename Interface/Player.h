#pragma once

#include <iostream>

class Player {

public:
	Player();
	Player(int score, std::string user);
	int getScore();
	void setScore(int score);
	std::string getUsername();
	void setUsername(std::string nom);
	bool getNameSetted();
	void setNameSetted(bool setted);


private:
	int score;
	std::string username;
	bool nameSetted;
};



