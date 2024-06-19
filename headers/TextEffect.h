#ifndef TEXTEFFECT_H
#define TEXTEFFECT_H

#include "./Title.h"
#include "./TextEffectColor.h"

enum class TextEffectTypes {
    SUCCESS = 1,
    FALIUER = -1
};

sf::Color getColor(TextEffectTypes type) {
    switch (type) {
    case TextEffectTypes::SUCCESS:
        return sf::Color(50, 205, 50, 255);
        break;
    case TextEffectTypes::FALIUER:
        return sf::Color(255, 0, 56, 255);
        break;
    }
};

struct TextEffect : Title {
private:
    float maxPosition;
    TextEffectColor color;
public:
    TextEffect(std::string _text, TextEffectTypes type, sf::Vector2f startPosition)
        :Title(_text, startPosition, 24, "Joystick-5KjV", getColor(type)),
        maxPosition(startPosition.y - 100), color(getColor(type).r, getColor(type).g, getColor(type).b) {};

    float getMaxPosition() {
        return this->maxPosition;
    };

    void decrementOpacity() {
        if (this->color.getOpacity() > 0)
            this->color.setOpacity(this->color.getOpacity() - 0.1f);
    };

    void changeColor() {
        this->updateFillColor(sf::Color::Color(this->color.getColor()));
    };
};


#endif TEXTEFFECTCOLOR_H
