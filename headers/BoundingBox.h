#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "./Global.h"

struct BoundingBox {
private:
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;

    sf::Sprite* spritePointer = NULL;
    sf::Shape* shpePointer = NULL;
public:
    // Constructor That takes Sprite Pointer
    BoundingBox(sf::Sprite*);
    // Constructor That takes Shape Pointer
    BoundingBox(sf::Shape*);
    // Default Destructor that deletes the spritePointer & the shpePointer
    ~BoundingBox();
    // Method to update Postion to be in the same position Of the Pointers
    void update();
    // Method to draw the Bounding Box (For Debug)
    void draw(sf::RenderWindow*);
    // Method that retarns the Top line of the Box
    sf::RectangleShape getTop();
    // Method that retarns the Bottom line of the Box
    sf::RectangleShape getBottom();
    // Method that retarns the Left line of the Box
    sf::RectangleShape getLeft();
    // Method that retarns the Right line of the Box
    sf::RectangleShape getRight();
};

#endif // !BOUNDINGBOX_H
