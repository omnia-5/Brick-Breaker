#ifndef SELECTABLECELL_H
#define SELECTABLECELL_H

#include "./Global.h"
#include "./Rectangle.h"


enum class SelectableCellState {
    Selected,
    Hovered,
    NotSelected
};

struct SelectableCell : Rectangle {
private:
    SelectableCellState state;
    int opacity;
    sf::Color initialColor;
public:
    SelectableCell(const sf::Vector2f position, const sf::Vector2f size = sf::Vector2f(128, 48), const sf::Color color = sf::Color::Color(32, 32, 32))
        :Rectangle(position, size, sf::Color::Color(color.r, color.g, color.b, this->opacity)),
        state(SelectableCellState::NotSelected),
        initialColor(color), opacity(170) {};

    void setState(const SelectableCellState newState) {
        this->state = newState;
    };

    SelectableCellState getState() {
        return this->state;
    };

    bool isSelected() {
        return this->state == SelectableCellState::Selected;
    };

    void update() {
        switch (this->state) {
        case SelectableCellState::NotSelected:
            this->opacity = 170;
            this->sprite.setOutlineThickness(0);
            this->setFillColor(sf::Color::Color(initialColor.r, initialColor.g, initialColor.b, this->opacity));
            break;
        case SelectableCellState::Hovered:
            this->opacity = 255;
            this->sprite.setOutlineThickness(0);
            this->setFillColor(sf::Color::Color(initialColor.r, initialColor.g, initialColor.b, this->opacity));
            break;
        case SelectableCellState::Selected:
            this->opacity = 255;
            this->sprite.setOutlineThickness(3);
            this->sprite.setOutlineColor(sf::Color::Color(224, 224, 224, 170));
            this->setFillColor(sf::Color::Color(initialColor.r, initialColor.g, initialColor.b, this->opacity));
            break;
        }
    };
};

#endif // !SELECTABLECELL_H