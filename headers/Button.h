#ifndef BUTTON_H
#define BUTTON_H

#include "./Global.h"
#include "./Title.h"
#include "./Rectangle.h"
#include <functional>

struct Button : Rectangle {
private:
    Title* title;
    std::function<void()> callback;
    bool isClicked;
public:
    Button(sf::Vector2f, sf::Vector2f, std::string);
    ~Button();
    void setCallBack(std::function<void()>);
    void draw(sf::RenderWindow*);
    bool isPositionOnButton(sf::Vector2f);
    void update(sf::Vector2f, bool);
};

#endif // !BUTTON_H