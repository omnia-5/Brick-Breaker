#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "./Global.h"
#include "./Color.h"
#include "./Vector.h"
#include <sstream>

struct SelectedColor {
    sf::Color color;
    int index;
};

struct ColorPicker {
private:
    sp::Vector<Color*> colors;
    int yStart;
    SelectedColor selcted;
public:
    ColorPicker(int yPosition, int colorThemeNumber) :yStart(yPosition), selcted({sf::Color::White, -1}) {
        std::ifstream colorsFile("./loaders/colorThemes/colorTheme-" + std::to_string(colorThemeNumber) + ".txt");
        if (colorsFile.is_open()) {
            std::string line;
            char type;
            int r, g, b;
            while (std::getline(colorsFile, line)) {
                std::istringstream in(line);
                in >> type >> r >> g >> b;
                this->addNewColor(sf::Color::Color(r, g, b));
            }
        }
        colorsFile.close();
    };

    void addNewColor(sf::Color fillColor) {
        Color* newColorCell = new Color(sf::Vector2f((APP_SIZE.x / COLOR_SIZE.x) + (COLOR_SIZE.x * (2 * (colors.size() + 1))), (float)yStart), fillColor);
        colors.push_back(newColorCell);
    };

    void draw(sf::RenderWindow* window) {
        for (unsigned int i = 0; i < this->colors.size(); i++)
            this->colors[i]->draw(window);
    };

    bool isPositionOnColor(sf::Vector2f mousePosition, Color* color) {
        return (color->getPostion().x <= mousePosition.x && mousePosition.x <= color->getPostion().x + color->getWidth())
            && (color->getPostion().y <= mousePosition.y && mousePosition.y <= color->getPostion().y + color->getHeight());
    };

    void setSelectedColor(sf::Color newColor, int index) {
        this->selcted = {newColor , index + 1};
    };

    SelectedColor getSelectedColor() {
        return this->selcted;
    };

    void update(sf::Vector2f mousePosition, bool ismouseClicked) {
        if (this->selcted.index == -1) {
            this->colors[0]->setState(ColorCellState::Active);
            this->setSelectedColor(this->colors[0]->getFillColor(), 0);
        }        
        for (unsigned int i = 0; i < this->colors.size(); i++) {
            if (this->isPositionOnColor(mousePosition, this->colors[i])) {
                if (!(this->colors[i]->getState() == ColorCellState::Active))
                    this->colors[i]->setState(ColorCellState::Hovered);
                if (ismouseClicked) {
                    for (unsigned int j = 0; j < this->colors.size(); j++)
                        this->colors[j]->setState(ColorCellState::Inactive);
                    if ((this->colors[i]->getState() == ColorCellState::Active)) {
                        this->colors[i]->setState(ColorCellState::Inactive);
                    }
                    else {
                        this->colors[i]->setState(ColorCellState::Active);
                        this->setSelectedColor(this->colors[i]->getFillColor(), i);
                    }
                }
            }
            else {
                if (!this->colors[i]->isActive()) this->colors[i]->setState(ColorCellState::Inactive);
            }
            this->colors[i]->update();
        }
    };
};


#endif // !COLORPICKER_H