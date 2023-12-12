#include "SFML/Graphics.hpp"

#include "rounded_rectangle.h"
#include "general_data.h"

class ErrorMessage : public sf::Drawable {
 public:
    ErrorMessage(std::string mes)
        : message_(std::move(mes))
    {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        sf::Text text;
        text.setString(message_);
        text.setFillColor(sf::Color::Red);
        text.setFont(font);
        text.setPosition(960 - text.getLocalBounds().width / 2, 540 - text.getLocalBounds().height / 2);
        text.setOutlineColor(outline_color);

        sf::RoundedRectangleShape win(sf::Vector2f(text.getLocalBounds().width + 20, 50));
        win.setPosition(sf::Vector2f(960 - text.getLocalBounds().width / 2 - 10, 540 - text.getLocalBounds().height / 2 - 10));
        win.setRoundRadius(15);
        win.setFillColor(background_color);

        sf::RectangleShape background;
        background.setSize({1e6, 1e6});
        background.setFillColor(sf::Color(255, 0, 0, 70));

        target.draw(background);
        target.draw(win);
        target.draw(text);
    }
 private:
    std::string message_;
};