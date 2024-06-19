#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "./Global.h"
#include "./BoundingBox.h"

struct Rectangle {
protected:
    sf::RectangleShape sprite;
    BoundingBox* boundingBox;
public:
    Rectangle(const sf::Vector2f, const sf::Vector2f, const sf::Color);
    ~Rectangle();
    sf::Vector2f getPostion();
    sf::FloatRect getGlobalBounds() {
        return this->sprite.getGlobalBounds();
    };
    BoundingBox* getBoundingBox() {
        return this->boundingBox;
    };
    float getWidth();
    float getHeight();
    void setPosition(sf::Vector2f);
    void setFillColor(sf::Color);
    sf::Color getFillColor();
    void draw(sf::RenderWindow*);

};

#endif // !RECTANGLE_H
