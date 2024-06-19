#ifndef GRID_H
#define GRID_H

#include "./Global.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>

struct Grid {
protected:
    const int padding;
    sf::Vector2f startingPoint;
    std::map<char, sf::Color> colorsMap;

public:
    Grid(const int rows, const int columns, float top, sf::Vector2f _startingPoint = sf::Vector2f(0, 0)) :padding(5), startingPoint(_startingPoint) {
        this->loadColorsMap(1);
        if (startingPoint == sf::Vector2f(0, 0))
            startingPoint = { (APP_SIZE.x - (rows * BRICK_SIZE.x + (rows * padding))) / 2, top };
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
};


#endif // !GRID_H