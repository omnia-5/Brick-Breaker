#ifndef TEXTEFFECTSMANGER_H
#define TEXTEFFECTSMANGER_H

#include "./Global.h"
#include "./Vector.h"
#include "./TextEffect.h"


struct TextEffectsManager {
private:
    sp::Vector<TextEffect*> effects;

public:
    TextEffectsManager() {};

    void addNewEffect(std::string _text, TextEffectTypes type, sf::Vector2f startPosition) {
        TextEffect* effect = new TextEffect(_text, type, startPosition);
        this->effects.push_back(effect);
    };

    void update(float deltaTime) {
        for (unsigned int i = 0; i < this->effects.size(); i++) {
            // Will be Draw only if the TextEffect is in the Moving Range
            if (this->effects[i]->getPosition().y > this->effects[i]->getMaxPosition()) {
                this->effects[i]->move(sf::Vector2f(0, -100 * deltaTime));
                this->effects[i]->decrementOpacity();
                this->effects[i]->changeColor();
            }
            else // if it went out the Range it will be delete
                this->effects.erase(i);
        } // Score Text Effect Logic and Drawign
    };

    void draw(sf::RenderWindow* window) {
        for (unsigned int i = 0; i < this->effects.size(); i++)
            this->effects[i]->draw(window);
    }
};

#endif // !TEXTEFFECTSMANGER_K
