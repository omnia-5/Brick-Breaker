#include "../headers/BoundingBox.h"

BoundingBox::BoundingBox(sf::Sprite* sprite) {
    this->spritePointer = sprite;

    this->top.setSize(sf::Vector2f(sprite->getGlobalBounds().width, 1));
    this->bottom.setSize(sf::Vector2f(sprite->getGlobalBounds().width, 1));
    this->left.setSize(sf::Vector2f(1, sprite->getGlobalBounds().height));
    this->right.setSize(sf::Vector2f(1, sprite->getGlobalBounds().height));

    this->top.setPosition(sprite->getPosition().x - sprite->getPosition().x, sprite->getPosition().y - sprite->getPosition().y);
    this->bottom.setPosition(sprite->getPosition().x - sprite->getPosition().x, sprite->getPosition().y + sprite->getGlobalBounds().height - sprite->getPosition().y);
    this->left.setPosition(sprite->getPosition().x - sprite->getPosition().x, sprite->getPosition().y - sprite->getPosition().y);
    this->right.setPosition(sprite->getPosition().x + sprite->getGlobalBounds().width - sprite->getPosition().x, sprite->getPosition().y - sprite->getPosition().y);

};

BoundingBox::BoundingBox(sf::Shape* sprite) {
    this->shpePointer = sprite;

    this->top.setSize(sf::Vector2f(sprite->getGlobalBounds().width, 1));
    this->bottom.setSize(sf::Vector2f(sprite->getGlobalBounds().width, 1));
    this->left.setSize(sf::Vector2f(1, sprite->getGlobalBounds().height));
    this->right.setSize(sf::Vector2f(1, sprite->getGlobalBounds().height));

    this->top.setPosition(sprite->getPosition().x - sprite->getPosition().x, sprite->getPosition().y - sprite->getPosition().y);
    this->bottom.setPosition(sprite->getPosition().x - sprite->getPosition().x, sprite->getPosition().y + sprite->getGlobalBounds().height - sprite->getPosition().y);
    this->left.setPosition(sprite->getPosition().x - sprite->getPosition().x, sprite->getPosition().y - sprite->getPosition().y);
    this->right.setPosition(sprite->getPosition().x + sprite->getGlobalBounds().width - sprite->getPosition().x, sprite->getPosition().y - sprite->getPosition().y);

};

BoundingBox::~BoundingBox() {
    delete this->shpePointer;
    delete this->spritePointer;
};


void BoundingBox::update() {
    if (this->spritePointer != NULL) {
        this->top.setPosition(this->spritePointer->getPosition().x - this->spritePointer->getOrigin().x, this->spritePointer->getPosition().y - this->spritePointer->getOrigin().y);
        this->bottom.setPosition(this->spritePointer->getPosition().x - this->spritePointer->getOrigin().x, this->spritePointer->getPosition().y + this->spritePointer->getGlobalBounds().height - this->spritePointer->getOrigin().y);
        this->left.setPosition(this->spritePointer->getPosition().x - this->spritePointer->getOrigin().x, this->spritePointer->getPosition().y - this->spritePointer->getOrigin().y);
        this->right.setPosition(this->spritePointer->getPosition().x + this->spritePointer->getGlobalBounds().width - this->spritePointer->getOrigin().x, this->spritePointer->getPosition().y - this->spritePointer->getOrigin().y);
    }
    else if (this->shpePointer != NULL) {
        this->top.setPosition(this->shpePointer->getPosition().x - this->shpePointer->getOrigin().x, this->shpePointer->getPosition().y - this->shpePointer->getOrigin().y);
        this->bottom.setPosition(this->shpePointer->getPosition().x - this->shpePointer->getOrigin().x, this->shpePointer->getPosition().y + this->shpePointer->getGlobalBounds().height - this->shpePointer->getOrigin().y);
        this->left.setPosition(this->shpePointer->getPosition().x - this->shpePointer->getOrigin().x, this->shpePointer->getPosition().y - this->shpePointer->getOrigin().y);
        this->right.setPosition(this->shpePointer->getPosition().x + this->shpePointer->getGlobalBounds().width - this->shpePointer->getOrigin().x, this->shpePointer->getPosition().y - this->shpePointer->getOrigin().y);
    }
};

void BoundingBox::draw(sf::RenderWindow* window) {
    window->draw(this->top);
    window->draw(this->bottom);
    window->draw(this->left);
    window->draw(this->right);
};

sf::RectangleShape BoundingBox::getTop() {
    return this->top;
}

sf::RectangleShape BoundingBox::getBottom() {
    return this->bottom;
}

sf::RectangleShape BoundingBox::getLeft() {
    return this->left;
}

sf::RectangleShape BoundingBox::getRight() {
    return this->right;
}