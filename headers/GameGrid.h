#ifndef GAMEGRID_H
#define GAMEGRID_H

#include "./Vector.h"
#include "./Global.h"
#include "./Brick.h"
#include "./Ball.h"
#include "./Player.h"
#include "./TextEffectsManager.h"
#include "./TimeManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>

struct GameGrid {
private:
    sp::Vector<sp::Vector<Brick*>> bricks;
    const int padding;
    sf::Vector2f startingPoint;
    std::map<char, sf::Color> colorsMap;
    TextEffectsManager textEffectsManager;
    TimeManager timeManager;
    int remainingCount;
public:
    GameGrid(const int rows = 12, const int columns = 12, sf::Vector2f _startingPoint = sf::Vector2f(0, 0))
        :padding(5), startingPoint(_startingPoint), remainingCount(0){
        this->loadColorsMap(1);
        if (startingPoint == sf::Vector2f(0, 0))
            startingPoint = { (APP_SIZE.x - (rows * BRICK_SIZE.x + (rows * padding))) / 2,70 };
        for (int i = 0; i < rows; i++) {
            sp::Vector<Brick*> row;
            for (int j = 0; j < columns; j++) {
                Brick* brick = new Brick(sf::Vector2f(startingPoint.x + (i * BRICK_SIZE.x) + ((i + 1) * padding), startingPoint.y + (j * BRICK_SIZE.y) + ((j + 1) * padding)), 1, colorsMap['1'], true);
                row.push_back(brick);
            }
            bricks.push_back(row);
            row.clear();
        }
    };

    GameGrid(std::string fileName, sf::Vector2f _startingPoint = sf::Vector2f(0, 0))
        :padding(5), startingPoint(_startingPoint), remainingCount(0) {
        this->loadColorsMap(1);
        if (startingPoint == sf::Vector2f(0, 0))
            startingPoint = { 0,70 };
        std::ifstream levelFile("./levels/" + fileName + ".txt");
        if (levelFile.is_open()) {
            std::string line;
            int lineCount = 0;
            while (std::getline(levelFile, line)) {
                sp::Vector<Brick*> row;

                for (unsigned int column = 0; column < line.length(); column++) {
                    if (line[column] == '*') continue;
                    Brick* brick = new Brick(sf::Vector2f(startingPoint.x + (column * BRICK_SIZE.x) + ((column + 1) * padding), startingPoint.y + (lineCount * BRICK_SIZE.y) + ((lineCount + 1) * padding)), 1, colorsMap[line[column]], (line[column] != '#'));
                    row.push_back(brick);
                }
                bricks.push_back(row);
                row.clear();
                lineCount++;
            }
        }
        levelFile.close();
    };

    void loadFromFile(std::string path) {
        this->clearGrid();
        this->startingPoint = { 0,70 };
        std::ifstream levelFile(path);
        if (levelFile.is_open()) {
            std::string line;
            int lineCount = 0;
            while (std::getline(levelFile, line)) {
                sp::Vector<Brick*> row;
                for (unsigned int column = 0; column < line.length(); column++) {
                    if (line[column] == '*') continue;
                    Brick* brick = new Brick(sf::Vector2f(startingPoint.x + (column * BRICK_SIZE.x) + ((column + 1) * padding), startingPoint.y + (lineCount * BRICK_SIZE.y) + ((lineCount + 1) * padding)), (int)(line[column] - '0'), colorsMap[line[column]], (line[column] != '#'));
                    row.push_back(brick);
                }
                bricks.push_back(row);
                row.clear();
                lineCount++;
            }
        }
        levelFile.close();
    };

    void loadColorsMap(int themeColorNumber) {
        std::ifstream colorsFile("./loaders/colorThemes/colorTheme-" + std::to_string(themeColorNumber) + ".txt");
        if (colorsFile.is_open()) {
            std::string line;
            char type;
            int r, g, b;
            while (std::getline(colorsFile, line)) {
                std::istringstream in(line);
                in >> type >> r >> g >> b;
                colorsMap[type] = sf::Color::Color(r, g, b);
            }
        }
        colorsFile.close();
    };

    void update(float deltaTime, Ball* ball, Player* player) {
        this->remainingCount = 0;
        if (ball->getPostion().y + ball->getHeight() / 2 + 1 > APP_SIZE.y) {
            sf::Vector2 lastPosition = ball->getPostion();
            textEffectsManager.addNewEffect("-1", TextEffectTypes::FALIUER, sf::Vector2f(lastPosition.x, APP_SIZE.y - 10));
            timeManager.sleepFor(100);
            player->decrementScore();
            player->loseLife();
            ball->reset();
            player->resetPosition();
        }
        if (ball->getPostion().y - ball->getHeight() / 2 - 1 < 0)
            ball->flipYDirction();
        if (ball->getPostion().x + ball->getWidth() / 2 + 1 > APP_SIZE.x)
            ball->flipXDirction();
        else if (ball->getPostion().x - ball->getWidth() / 2 - 1 < 0)
            ball->flipXDirction();

        if (ball->getGlobalBounds().intersects(player->getBoundingBox()->getLeft().getGlobalBounds())) {
            ball->flipXDirction();
            ball->setPosition(sf::Vector2f(ball->getPostion().x - 1, ball->getPostion().y));
        }
        if (ball->getGlobalBounds().intersects(player->getBoundingBox()->getRight().getGlobalBounds())) {
            ball->flipXDirction();
            ball->setPosition(sf::Vector2f(ball->getPostion().x + 1, ball->getPostion().y));
        }
        if (ball->getGlobalBounds().intersects(player->getBoundingBox()->getTop().getGlobalBounds())) {
            ball->flipYDirction();
            ball->setPosition(sf::Vector2f(ball->getPostion().x, ball->getPostion().y - 1));
        }
        for (unsigned int i = 0; i < this->bricks.size(); i++) {
            for (unsigned int j = 0; j < this->bricks[i].size(); j++) {
                if (this->bricks[i][j]->isBreakable())
                    this->remainingCount++;
                if (this->bricks[i][j]->isDone()) {
                    this->bricks[i].erase(j);
                    break;
                }
                if (ball->getGlobalBounds().intersects(this->bricks[i][j]->getBoundingBox()->getLeft().getGlobalBounds())) {
                    ball->flipXDirction();
                    ball->setPosition(sf::Vector2f(ball->getPostion().x - 1, ball->getPostion().y));
                    this->bricks[i][j]->takeHit();
                    player->incrementScore();
                    textEffectsManager.addNewEffect("+1", TextEffectTypes::SUCCESS, this->bricks[i][j]->getPostion());
                    break;
                }
                if (ball->getGlobalBounds().intersects(this->bricks[i][j]->getBoundingBox()->getRight().getGlobalBounds())) {
                    ball->flipXDirction();
                    ball->setPosition(sf::Vector2f(ball->getPostion().x + 1, ball->getPostion().y));
                    this->bricks[i][j]->takeHit();
                    player->incrementScore();
                    textEffectsManager.addNewEffect("+1", TextEffectTypes::SUCCESS, this->bricks[i][j]->getPostion());
                    break;
                }
                if (ball->getGlobalBounds().intersects(this->bricks[i][j]->getBoundingBox()->getTop().getGlobalBounds())) {
                    ball->flipYDirction();
                    ball->setPosition(sf::Vector2f(ball->getPostion().x, ball->getPostion().y - 1));
                    this->bricks[i][j]->takeHit();
                    player->incrementScore();
                    textEffectsManager.addNewEffect("+1", TextEffectTypes::SUCCESS, this->bricks[i][j]->getPostion());
                    break;
                }
                if (ball->getGlobalBounds().intersects(this->bricks[i][j]->getBoundingBox()->getBottom().getGlobalBounds())) {
                    ball->flipYDirction();
                    ball->setPosition(sf::Vector2f(ball->getPostion().x, ball->getPostion().y + 1));
                    this->bricks[i][j]->takeHit();
                    player->incrementScore();
                    textEffectsManager.addNewEffect("+1", TextEffectTypes::SUCCESS, this->bricks[i][j]->getPostion());
                    break;
                }
            }
        }

        textEffectsManager.update(deltaTime);
    };

    void clearGrid() {
        for (unsigned int i = 0; i < this->bricks.size(); i++) this->bricks[i].clear();
        this->bricks.clear();
    };

    int getRemaining() {
        return this->remainingCount;
    };

    bool isFinished() {
        return this->remainingCount == 0;
    };

    void draw(sf::RenderWindow* window) {
        for (unsigned int i = 0; i < this->bricks.size(); i++) {
            for (unsigned int j = 0; j < this->bricks[i].size(); j++)
                this->bricks[i][j]->draw(window);
        }
        this->textEffectsManager.draw(window);
    };
};


#endif // !GAMEGRID_H