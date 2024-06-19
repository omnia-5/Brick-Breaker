#include "../headers/AnimatedTitle.h"

AnimatedTitle::AnimatedTitle(std::string filname)
    :movingSpeed(70) {
    std::string textContent;
    std::ifstream dataFile("./loaders/" + filname + ".txt");
    if (dataFile.is_open()) {
        std::string line;
        while (std::getline(dataFile, line)) textContent += line + "\n";
    }
    dataFile.close();
    this->title = new Title(textContent, sf::Vector2f(APP_SIZE.x / 3, APP_SIZE.y + 50), 56, "Joystick-5KjV");
    this->poistion = sf::Vector2f(APP_SIZE.x / 3, APP_SIZE.y + 50);
};

AnimatedTitle::~AnimatedTitle() {
    delete this->title;
};

void AnimatedTitle::update(float deltaTime) {
    if (this->poistion.y + this->title->getHeight() + 10 > 0) 
        this->poistion.y -= this->movingSpeed * deltaTime;
    else 
        this->poistion = sf::Vector2f(APP_SIZE.x / 3, APP_SIZE.y + 50);
    this->title->updatePosition(this->poistion);
};

void AnimatedTitle::draw(sf::RenderWindow* window) {
    this->title->draw(window);
};