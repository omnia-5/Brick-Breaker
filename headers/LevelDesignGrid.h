#ifndef LEVELDESIGNGRID_H
#define LEVELDESIGNGRID_H

#include "./Vector.h"
#include "./Global.h"
#include "./EditableBrick.h"
#include "./ColorPicker.h"
#include <filesystem>
#include <fstream>

struct LevelDesignGrid {
private:
    sp::Vector<sp::Vector<EditableBrick*>> grid;
    sp::Vector<sp::Vector<char>> serializedGrid;
    const int padding;
    sf::Vector2f startingPoint;

public:
    LevelDesignGrid(const int rows = 12, const int columns = 12, sf::Vector2f _startingPoint = sf::Vector2f(0, 0)) :padding(5), startingPoint(_startingPoint) {
        if (startingPoint == sf::Vector2f(0, 0))
            startingPoint = { (APP_SIZE.x - (rows * BRICK_SIZE.x + (rows * padding))) / 2, 50 };
        for (int i = 0; i < rows; i++) {
            sp::Vector<EditableBrick*> row;
            sp::Vector<char> serializedGridRow;
            for (int j = 0; j < columns; j++) {
                EditableBrick* editableBrick = new EditableBrick(sf::Vector2f(startingPoint.x + (i * BRICK_SIZE.x) + ((i + 1) * 5), startingPoint.y + (j * BRICK_SIZE.y) + ((j + 1) * 5)));
                row.push_back(editableBrick);
                serializedGridRow.push_back('*');
            }
            grid.push_back(row);
            row.clear();
            serializedGrid.push_back(serializedGridRow);
            serializedGridRow.clear();
        }
    };

    void draw(sf::RenderWindow* window) {
        for (unsigned int i = 0; i < this->grid.size(); i++) {
            for (unsigned int j = 0; j < this->grid[i].size(); j++)
                grid[i][j]->draw(window);
        }
    };

    bool isPositionOnBrick(sf::Vector2f mousePosition, EditableBrick* brick) {
        return (brick->getPostion().x <= mousePosition.x && mousePosition.x <= brick->getPostion().x + brick->getWidth())
            && (brick->getPostion().y <= mousePosition.y && mousePosition.y <= brick->getPostion().y + brick->getHeight());
    };

    void saveSerializedGrid() {
        std::string path = "./levels/custom/";
        int count = 0;
        for (const auto& entry : std::filesystem::directory_iterator(path)) count++;
        std::ofstream levelFile("./levels/custom/level-" + std::to_string(count + 1) + ".txt", std::ios_base::app);
        if (levelFile.is_open()) {
            for (unsigned int i = 0; i < this->serializedGrid.size(); i++) {
                for (unsigned int j = 0; j < this->serializedGrid[i].size(); j++) levelFile << serializedGrid[j][i];
                levelFile << "\n";
            }
        }
        levelFile.close();
    };

    void reset() {
        for (unsigned int i = 0; i < this->grid.size(); i++) {
            for (unsigned int j = 0; j < this->grid[i].size(); j++) {
                this->grid[j][i]->reset();
                this->serializedGrid[i][j] = '*';
            }
        }
    }

    void update(sf::Vector2f mousePosition, bool ismouseClicked, SelectedColor selected) {
        for (unsigned int i = 0; i < this->grid.size(); i++) {
            for (unsigned int j = 0; j < this->grid[i].size(); j++) {
                if (this->isPositionOnBrick(mousePosition, this->grid[i][j])) {
                    if (!(this->grid[i][j]->getState() == EditableBrickState::Filled))
                        this->grid[i][j]->setState(EditableBrickState::Hovered);
                    if (ismouseClicked) {
                        if ((this->grid[i][j]->getState() == EditableBrickState::Filled)) {
                            this->grid[i][j]->setState(EditableBrickState::Empty);
                            this->serializedGrid[i][j] = '*';
                        }
                        else {
                            this->grid[i][j]->setState(EditableBrickState::Filled);
                            this->serializedGrid[i][j] = ((selected.index >= 5) ? '#': (char) ('0' + selected.index));
                        }
                    }
                }
                else {
                    if (!this->grid[i][j]->isFilled()) this->grid[i][j]->setState(EditableBrickState::Empty);
                }
                this->grid[i][j]->update(selected.color);
            }
        }
    };
};


#endif // !LEVELDESIGNGRID_H