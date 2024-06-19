#ifndef COLOR_H
#define COLOR_H

#include "./Global.h"
#include "./Rectangle.h"

enum class ColorCellState {
    Inactive,
    Hovered,
    Active
};

struct Color : Rectangle {
private:
    ColorCellState state;
    int opacity;
    sf::Color initialColor;
public:
    Color(sf::Vector2f position, sf::Color color) : Rectangle(position, COLOR_SIZE, sf::Color::Color(color.r, color.g, color.b, this->opacity)),
        state(ColorCellState::Inactive), initialColor(color), opacity(170) {};
    
    void setState(const ColorCellState newState) {
        this->state = newState;
    };

    ColorCellState getState() {
        return this->state;
    };

    bool isActive() {
        return this->state == ColorCellState::Active;
    };

    void update() {
        switch (this->state) {
        case ColorCellState::Inactive:
            this->opacity = 170;
            this->sprite.setOutlineThickness(0);
            this->setFillColor(sf::Color::Color(initialColor.r, initialColor.g, initialColor.b, this->opacity));
            break;
        case ColorCellState::Hovered:
            this->opacity = 255;
            this->sprite.setOutlineThickness(0);
            this->setFillColor(sf::Color::Color(initialColor.r, initialColor.g, initialColor.b, this->opacity));
            break;
        case ColorCellState::Active:
            this->opacity = 255;
            this->sprite.setOutlineThickness(3);
            this->sprite.setOutlineColor(sf::Color::Color(224, 224, 224, 170));
            this->setFillColor(sf::Color::Color(initialColor.r, initialColor.g, initialColor.b, this->opacity));
            break;
        }
    };
};

#endif // !COLOR_H