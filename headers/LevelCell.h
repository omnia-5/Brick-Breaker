#ifndef LEVELCELL_H
#define LEVELCELL_H

#include "./Title.h"
#include "./SelectableCell.h"
#include <filesystem>

struct LevelCell : SelectableCell {
private:
    Title title;
    std::filesystem::path path;
public:
    LevelCell(const sf::Vector2f position, std::filesystem::path _path)
        :SelectableCell(position), path(_path),
        title(_path.filename().stem().string(), sf::Vector2f(position.x + 10, position.y + 10), ((_path.filename().stem().string().size() < 7) ? 20 : 18), "Joystick-5KjV") {};

    void draw(sf::RenderWindow* window) {
        window->draw(this->sprite);
        this->title.draw(window);
    };

    std::string getPath() {
        return this->path.string();
    };
};

#endif // !LEVELCELL_H