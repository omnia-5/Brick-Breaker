#include "../../headers/Brick.h"

Brick::Brick(const sf::Vector2f position, const int _hitsNeededToDestroy, sf::Color color, bool isBreakable)
    :Rectangle(position, BRICK_SIZE, sf::Color::Color(color.r, color.g, color.b, opacity)),
    hitsTaken(0), hitsNeededToDestroy(_hitsNeededToDestroy), _isDone(false), opacity(255),
    _isBreakable(isBreakable), initalColor(color) {};

bool Brick::isDone() {
    return this->_isDone;
};

bool Brick::isBreakable() {
    return this->_isBreakable;
};

void Brick::updateColor() {
    this->setFillColor(sf::Color::Color(this->initalColor.r, this->initalColor.g, this->initalColor.b, (sf::Uint8)this->opacity));
};

void Brick::takeHit() {
    if (this->isBreakable()) {
        if (!this->isDone()) {
            this->hitsTaken++;
            this->opacity -= (255 / this->hitsNeededToDestroy);
            this->updateColor();
            if (this->hitsTaken == this->hitsNeededToDestroy) this->_isDone = true;
        }
    }
};