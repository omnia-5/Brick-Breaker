#ifndef EDITABLEBRICK_H
#define EDITABLEBRICK_H
#include "./Global.h"
#include "./Rectangle.h"

enum class EditableBrickState {
    Empty,
    Hovered,
    Filled
};

struct EditableBrick : Rectangle {
private:
    EditableBrickState state;
    sf::Color defaulteColor;
    sf::Color color;
    sf::Color hoverColor;
public:
    EditableBrick(const sf::Vector2f position) :Rectangle(position, BRICK_SIZE, this->defaulteColor),
        state(EditableBrickState::Empty), defaulteColor(sf::Color::Color(220, 220, 220, 128)),
        hoverColor(sf::Color::Color(220, 220, 220)), color(sf::Color::Transparent){};

    void setState(const EditableBrickState newState) {
        this->state = newState;
    };

    EditableBrickState getState() {
        return this->state;
    };

    void reset() {
        this->setState(EditableBrickState::Empty);
    };

    void update(const sf::Color fillColor) {
        switch (this->state) {
        case EditableBrickState::Empty:
            this->setFillColor(this->defaulteColor);
            this->color = sf::Color::Transparent;
            break;
        case EditableBrickState::Hovered:
            this->setFillColor(this->hoverColor);
            break;
        case EditableBrickState::Filled:
            if (this->color == sf::Color::Transparent)
                this->color = fillColor;
            setFillColor(this->color);
            break;
        }
    }

    bool isFilled() {
        return this->state == EditableBrickState::Filled;
    };

    void setFillColor(sf::Color color) {
        this->sprite.setFillColor(color);
    };

};


#endif // !EDITABLEBRICK_H