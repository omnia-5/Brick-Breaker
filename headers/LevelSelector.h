#ifndef LEVELSELECTOR_H
#define LEVELSELECTOR_H

#include "./Vector.h"
#include "./LevelCell.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct SelectedLevel {
    std::string path;
    int index;
};


struct LevelSelector {
private:
    sp::Vector<LevelCell*> levels;
    SelectedLevel selectedLevel;
public:
    LevelSelector(const std::string path) :selectedLevel({ "", -1 }){
        sp::Vector<std::filesystem::path> filnames;
        // To get all Fille names in givin path
        for (const auto& entry : std::filesystem::directory_iterator(path)) filnames.push_back(entry.path());
        // For Sorting
        unsigned int smallPosition;
        for (unsigned int i = 0; i < filnames.size(); i++) {
            smallPosition = i;
            for (unsigned int j = i + 1; j < filnames.size(); j++) {
                std::stringstream in1(filnames[j].stem().string().replace(filnames[j].stem().string().find('-'), 1, " "));
                std::stringstream in2(filnames[smallPosition].stem().string().replace(filnames[j].stem().string().find('-'), 1, " "));
                std::string s1, s2;
                int i1, i2;
                in1 >> s1 >> i1;
                in2 >> s2 >> i2;
                if (i1 < i2) smallPosition = j;
            }
            std::filesystem::path temp = filnames[smallPosition];
            filnames[smallPosition] = filnames[i];
            filnames[i] = temp;
        }
        // For acuall constructing
        for (unsigned int i = 0; i < filnames.size(); i++) {
            LevelCell* level = new LevelCell(sf::Vector2f((float) (32 + ((this->levels.size() % 7) * 128) + ((this->levels.size() % 7) * 8)), (float) (100 + ((this->levels.size() / 7) * 48) + ((this->levels.size() / 7) * 8))), filnames[i]);
            this->levels.push_back(level);
        }
    };

    void draw(sf::RenderWindow* window) {
        for (unsigned int i = 0; i < this->levels.size(); i++) {
            this->levels[i]->draw(window);
        }
    };

    bool isPositionOnLevel(sf::Vector2f mousePosition, LevelCell* levelCell) {
        return (levelCell->getPostion().x <= mousePosition.x && mousePosition.x <= levelCell->getPostion().x + levelCell->getWidth())
            && (levelCell->getPostion().y <= mousePosition.y && mousePosition.y <= levelCell->getPostion().y + levelCell->getHeight());
    };

    void setSelectedLevel(std::string path, int index) {
        this->selectedLevel = { path , index };
    };

    SelectedLevel getSelectedLevel() {
        return this->selectedLevel;
    };

    void update(sf::Vector2f mousePosition, bool ismouseClicked) {
        if (this->selectedLevel.index == -1) {
            this->levels[0]->setState(SelectableCellState::Selected);
            this->setSelectedLevel(this->levels[0]->getPath(), 0);
        }
        for (unsigned int i = 0; i < this->levels.size(); i++) {
            if (this->isPositionOnLevel(mousePosition, this->levels[i])) {
                if (!(this->levels[i]->getState() == SelectableCellState::Selected))
                    this->levels[i]->setState(SelectableCellState::Hovered);
                if (ismouseClicked) {
                    for (unsigned int j = 0; j < this->levels.size(); j++)
                        this->levels[j]->setState(SelectableCellState::NotSelected);
                    if ((this->levels[i]->getState() == SelectableCellState::Selected)) {
                        this->levels[i]->setState(SelectableCellState::NotSelected);
                    }
                    else {
                        this->levels[i]->setState(SelectableCellState::Selected);
                        this->setSelectedLevel(this->levels[i]->getPath(), i);
                    }
                }
            }
            else {
                if (!this->levels[i]->isSelected()) this->levels[i]->setState(SelectableCellState::NotSelected);
            }
            this->levels[i]->update();
        }
    };

};

#endif // !LEVELSELECTOR_H