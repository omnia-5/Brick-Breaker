#ifndef TEXTEFFECTCOLOR_H
#define TEXTEFFECTCOLOR_H

#include "./Global.h"

struct TextEffectColor {
private:
    sf::Uint8 red;
    sf::Uint8 green;
    sf::Uint8 blue;
    float opacity;
public:
    TextEffectColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, float o = 255)
        :red(r), green(g), blue(b), opacity(o) {};

    void setOpacity(float newOpacity) {
        this->opacity = newOpacity;
    };

    float getOpacity() {
        return this->opacity;
    }
    sf::Color getColor() {
        return sf::Color::Color(this->red, this->green, this->blue, (sf::Uint8)this->opacity);
    };
};

#endif TEXTEFFECTCOLOR_H
