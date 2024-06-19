#include "../../headers/Rectangle.h"

// Default constructor
Rectangle::Rectangle(const sf::Vector2f position, const sf::Vector2f size, const sf::Color color) {
    this->sprite.setPosition(position);
    this->sprite.setSize(size);
    this->sprite.setFillColor(color);
    this->boundingBox = new BoundingBox(&this->sprite);
};

// Default destructor
Rectangle::~Rectangle() {};

// Method to get the sprite Position
sf::Vector2f Rectangle::getPostion() {
    return this->sprite.getPosition();
};


// Method to set the sprite Position
void Rectangle::setPosition(sf::Vector2f newPosition) {
    this->sprite.setPosition(newPosition);
};

// Method to get the sprite width
float Rectangle::getWidth() {
    return this->sprite.getGlobalBounds().width;
};

// Method to get the sprite height
float Rectangle::getHeight() {
    return this->sprite.getGlobalBounds().height;
};

// Method to update sprite Color
void Rectangle::setFillColor(sf::Color newColor) {
    this->sprite.setFillColor(newColor);
};

// Method to get the sprite colr
sf::Color Rectangle::getFillColor() {
    return this->sprite.getFillColor();
};


// Method to draw the sprite in the screen
void Rectangle::draw(sf::RenderWindow* window) {
    boundingBox->update();
    window->draw(this->sprite);
};