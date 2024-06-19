#include "../headers/TimeManager.h"

// Constructor
TimeManager::TimeManager() : frame(0), fps(0), delatTime(0) {};

// Destructor
TimeManager::~TimeManager() {};

// Getter for fps
unsigned int TimeManager::getFPS() {
	return this->fps;
};

// Getter for deltaTime
float TimeManager::getDeltaTime() {
	return this->delatTime;
};

void TimeManager::sleepFor(int millSeconds) {
	using namespace std::chrono_literals;
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(millSeconds));
};

void TimeManager::update() {
	if (this->framesClock.getElapsedTime().asSeconds() >= 1.f) {
		this->fps = this->frame;
		this->frame = 0;
		this->framesClock.restart();
	}
	++this->frame;
	this->delatTime = deltaTimeClock.restart().asSeconds();
};
