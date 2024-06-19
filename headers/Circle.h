#ifndef CIRCLE_H
#define CIRCLE_H

#include "./Global.h"

struct Circle {
protected:
    sf::CircleShape sprite;
public:
    Circle(const sf::Vector2f position, float radius, const sf::Color color) {
        this->sprite.setPosition(position);
        this->sprite.setRadius(radius);
        this->sprite.setFillColor(color);
    };

    // Method to get the sprite Position
    sf::Vector2f getPostion() {
        return this->sprite.getPosition();
    };

    sf::FloatRect getGlobalBounds() {
        return this->sprite.getGlobalBounds();
    };

    // Method to set the sprite Position
    void setPosition(sf::Vector2f newPosition) {
        this->sprite.setPosition(newPosition);
    };

    // Method to get the sprite width
    float getWidth() {
        return this->sprite.getGlobalBounds().width;
    };

    // Method to get the sprite height
    float getHeight() {
        return this->sprite.getGlobalBounds().height;
    };

    // Method to update sprite Color
    void setFillColor(sf::Color newColor) {
        this->sprite.setFillColor(newColor);
    };

    // Method to get the sprite colr
    sf::Color getFillColor() {
        return this->sprite.getFillColor();
    };

    void draw(sf::RenderWindow* window) {
        window->draw(this->sprite);
    };
};

#endif // !CIRCLE_H