#ifndef ANIMATEDTITLE_H
#define ANIMATEDTITLE_H

#include "./Global.h"
#include "./Title.h"
#include <fstream>

struct AnimatedTitle {
private:
    Title* title;
    sf::Vector2f poistion;
    float movingSpeed;
public:
    // Defualt Constructor That takes (string) file name and loads all data inside it line by line 
    AnimatedTitle(std::string);
    // Default Destructor that Deletes the title Pointer 
    ~AnimatedTitle();
    // a Method to Animate The Text and do its logic
    void update(float);
    // a Method to render the text
    void draw(sf::RenderWindow*);
};

#endif // !ANIMATEDTITLE_H