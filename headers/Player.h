#ifndef PLAYER_H
#define PLAYER_H

#include "./Global.h"
#include "./Rectangle.h"
#include "./Ball.h"

struct CanMove {
    bool left;
    bool right;
};

struct Player : Rectangle {
private:
    CanMove canMove;
    float movingSpeed;
    int moveOnX = 0;
    int lives;
    int score;
    bool _isDead;

public:
    Player()
        :Rectangle(sf::Vector2f(APP_SIZE.x / 2, APP_SIZE.y - 50), PLAYER_SIZE, sf::Color::Color(95, 230, 243)),
        movingSpeed(250), canMove({ true, true }), lives(3), score(0), _isDead(false) {
        this->sprite.setOrigin(this->getWidth() / 2, this->getHeight() / 2);
    };

	void update(float deltaTime) {
        this->checkForDie();
        this->updateCanMove();
        this->move(deltaTime);
	}

    void move(float deltaTime) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->canMove.right)
            this->moveOnX += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->canMove.left)
            this->moveOnX += -1;
        this->sprite.move(this->moveOnX * this->movingSpeed * deltaTime, 0);
        this->moveOnX = 0;
    };

    void resetPosition() {
        this->setPosition(sf::Vector2f(APP_SIZE.x / 2, APP_SIZE.y - 50));
    };

    void reset() {
        this->resetPosition();
        this->lives = 3;
        this->score = 0;
    };

    void updateCanMove() {
        this->canMove = { true, true };
        if (this->getPostion().x + this->getWidth() / 2 + 1 > APP_SIZE.x)
            this->canMove.right = false;
        if (this->getPostion().x - this->getWidth() / 2 - 1 < 0)
            this->canMove.left = false;
    };

    void incrementScore() {
        this->score++;
    }

    void decrementScore() {
        if (this->score > 0)
        this->score--;
    }

    int getScore() {
        return this->score;
    }

    int getLives() {
        return this->lives;
    }

    void loseLife() {
        this->lives--;
    }

    void checkForDie() {
        if (this->lives < 0) this->_isDead = true;
    }

    bool isDead() {
        return this->_isDead;
    };
};

#endif // !PLAYER_H