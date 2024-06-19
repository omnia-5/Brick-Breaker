#ifndef STORAGE_H
#define STORAGE_H
#include <string>
#include "./Vector.h"
#include "./Score.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Storage {
private:
	sp::Vector<Score> leaderBoard;
public:
	Storage();
	~Storage();
	void addData(std::string);
	std::string getStringLeaderBoard();
};

#endif // !STORAGE