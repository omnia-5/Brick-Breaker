#ifndef BALL_H
#define BALL_H

#include "./Global.h"
#include "./Circle.h"

const float PI = 3.14159265f;

enum BallState {
    Moving,
    Stopped
};

struct Ball :Circle {
private:
    BallState state;
    sf::Vector2f velocity;
    float angle;
public:
    // Defalt Constrcutor
    Ball();
    // a Method To update the ball and do its logic
    void update(float);
    // a Method to start ball Movement by changing the state
    void start();
    // a Method to reset the ball to default
    void reset();
    // a Method To move the ball
    void move(float);
    // a Methos to Flip the ball on Y
    void flipYDirction();
    // a Methos to Flip the ball on X
    void flipXDirction();
};

#endif // !BALL_H