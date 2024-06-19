#ifndef BRICK_H
#define BRICK_H
#include "./Global.h"
#include "./Rectangle.h"

struct Brick : Rectangle {
private:
    int hitsTaken;
    int hitsNeededToDestroy;
    bool _isDone;
    bool _isBreakable;
    int opacity;
    sf::Color initalColor;
public:
    // Default constructor that takes positon, max times to hit the brick, color, and is it break able or not
    Brick(sf::Vector2f, int, sf::Color, bool);
    // Return bool that indicates if the brick is done (took enough hits to be deleted)
    bool isDone();
    // Return bool that indicates if the brick Breakable
    bool isBreakable();
    // Method to Update Brick Color After Taking a Hit
    void updateColor();
    // the method that will be called when collision happens betwen ball and brick
    void takeHit();
};

#endif // !BRICK_H