#include "../headers/Ball.h"

Ball::Ball() :Circle(sf::Vector2f(APP_SIZE.x / 2, APP_SIZE.y - 100), 20, sf::Color::Color(85, 203, 148)),
state(BallState::Stopped), velocity({ 0, 0 }), angle(90 * (PI / 180)) {
    this->sprite.setOrigin(this->getWidth() / 2, this->getHeight() / 2);
};

void Ball::update(float deltaTime) {
    this->move(deltaTime);
};

void Ball::start() {
    if (this->state == BallState::Stopped) {
        this->state = BallState::Moving;
        this->velocity = { -150, -150 };
    }
};

void Ball::reset() {
    this->state = BallState::Stopped;
    this->velocity = { 0, 0 };
    this->setPosition(sf::Vector2f(APP_SIZE.x / 2, APP_SIZE.y - 100));
};

void Ball::move(float deltaTime) {
    if (this->state == BallState::Moving)
        this->sprite.move(sf::Vector2f(velocity.x * deltaTime, velocity.y * deltaTime));
};

void Ball::flipYDirction() {
    this->velocity.y *= -1;
};

void Ball::flipXDirction() {
    this->velocity.x *= -1;
};