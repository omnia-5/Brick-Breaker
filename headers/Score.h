#ifndef SCORE_H
#define SCORE_H

#include <string>

struct Score {
private:
	std::string name;
	int value;
public:
	Score(std::string _name = "", int _value = 0) :name(_name), value(_value) {};

	std::string getFinalFormat() {
		return this->name + " " + std::to_string(this->value);
	}

	std::string getName() {
		return this->name;
	}

	int getValue() {
		return this->value;
	}
};
#endif // !SCORE_H