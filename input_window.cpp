#include "input_window.h"

InputWindow::InputWindow(sf::Vector2f pos, sf::Vector2f size)
    : pos_(pos)
    , size_(size)
{}

void InputWindow::Click(sf::Vector2f pos) {
    active_ = std::abs(pos.x - (pos_.x + size_.x / 2)) <= size_.x / 2 &&
              std::abs(pos.y - (pos_.y + size_.y / 2)) <= size_.y / 2;
}

void InputWindow::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RoundedRectangleShape rect(size_);
    rect.setPosition(pos_);
    rect.setOutlineColor(outline_color);
    rect.setRoundRadius(10.f);
    rect.setFillColor(fill_color);
    rect.setOutlineThickness(2);
    target.draw(rect);

    sf::Text text;
    text.setFont(font);
    text.setString(data_);
    text.setCharacterSize(letter_size);
    text.setPosition(sf::Vector2f(pos_.x, pos_.y + size_.y / 2 - letter_size));
    text.setFillColor(text_color);
    target.draw(text);
}

void InputWindow::Write(sf::Uint32 event) {
    if (active_) {
        switch (event) {
            case 8:
                if (!data_.empty()) {
                    data_.pop_back();
                }
                break;
            case 42:
                return;
            default:
                data_.push_back(event);
        }
    }
}

void InputWindow::Activate() {
    active_ = true;
}

void InputWindow::SetSwitchActivated(std::function<void()> new_val) {
    switch_activated = std::move(new_val);
}
