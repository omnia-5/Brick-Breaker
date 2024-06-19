#ifndef TITLE_H
#define TITLE_H

struct Title {
private:
    sf::Text text;

public:
    Title(const std::string textContent, const sf::Vector2f position, const unsigned int characterSize, const std::string fontName, const sf::Color fillColor = sf::Color::Color(224, 224, 224)) {
        sf::Font* font = new sf::Font;
        if (!font->loadFromFile("./fonts/" + fontName + ".ttf")) return;
        this->text.setFont(*font);
        this->text.setFillColor(fillColor);
        this->text.setString(textContent);
        this->text.setCharacterSize(characterSize);
        this->text.setPosition(position);
    };

    void updateFillColor(sf::Color newColor) {
        this->text.setFillColor(newColor);
    };

    sf::Vector2f getPosition() {
        return this->text.getPosition();
    };

    void move(sf::Vector2f velocity) {
        this->text.move(velocity);
    };

    void updatePosition(sf::Vector2f newPosition) {
        this->text.setPosition(newPosition);
    };

    float getWidth() {
        return this->text.getGlobalBounds().width;
    };

    float getHeight() {
        return this->text.getGlobalBounds().height;
    };

    void updateContent(std::string newTextContent) {
        this->text.setString(newTextContent);
    };

    void f() {
        std::cout << "gl\n";
    }

    void draw(sf::RenderWindow* window) {
        window->draw(this->text);
    };

};

#endif // !TITLE_H