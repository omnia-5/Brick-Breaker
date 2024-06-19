#include "../headers/Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string textContent) :
    Rectangle(position, size, sf::Color::Color(32, 32, 32)),
    callback([]() { return; }), isClicked(false) {
    this->sprite.setOutlineThickness(3);
    this->sprite.setOutlineColor(sf::Color::Color(224, 224, 224, 170));
    this->title = new Title(textContent, sf::Vector2f(position.x + size.x / 5, position.y + size.y / 12), 32, "Joystick-5KjV");
};

Button::~Button() {
    delete this->title;
};

void Button::setCallBack(std::function<void()> newCallback) {
    this->callback = newCallback;
};

void Button::draw(sf::RenderWindow* window) {
    window->draw(this->sprite);
    this->title->draw(window);
};

bool Button::isPositionOnButton(sf::Vector2f mousePosition) {
    return (this->getPostion().x <= mousePosition.x && mousePosition.x <= this->getPostion().x + this->getWidth())
        && (this->getPostion().y <= mousePosition.y && mousePosition.y <= this->getPostion().y + this->getHeight());
};


void Button::update(sf::Vector2f mousePosition, bool ismouseClicked) {
    if (this->isPositionOnButton(mousePosition)) {
        this->setFillColor(sf::Color::Color(96, 96, 96));
        this->title->updateFillColor(sf::Color::Color(255, 255, 255));
        if (ismouseClicked && !this->isClicked) {
            this->callback();
            this->isClicked = true;
        }
    }
    else {
        this->setFillColor(sf::Color::Color(32, 32, 32));
        this->title->updateFillColor(sf::Color::Color(224, 224, 224));
    }
};