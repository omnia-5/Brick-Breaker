#ifndef FPS_H
#define FPS_H
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

class TimeManager {
private:
	sf::Clock framesClock;
	sf::Clock deltaTimeClock;
	unsigned int frame;
	unsigned int fps;
	float delatTime;

public:
	TimeManager();
	~TimeManager();
	unsigned int getFPS();
	float getDeltaTime();
	void update();
	void sleepFor(int);
};

#endif // !FPS