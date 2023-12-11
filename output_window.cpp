#include "output_window.h"

OutputWindow::OutputWindow(sf::Vector2f pos, sf::Vector2f size)
        : pos_(pos)
        , size_(size)
{ }

void OutputWindow::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RoundedRectangleShape rect(size_);
    rect.setPosition(pos_);
    rect.setFillColor(cant_write_fill_color);
    rect.setRoundRadius(15.f);
    rect.setOutlineColor(outline_color);
    target.draw(rect);

    sf::Text text;
    text.setFont(font);
    text.setString(output_);
    text.setCharacterSize(letter_size);
    text.setPosition(sf::Vector2f(pos_.x, pos_.y + size_.y / 2 - letter_size));
    text.setFillColor(text_color);
    target.draw(text);
}

void OutputWindow::SetOutput(std::string output) {
    output_ = output;
}