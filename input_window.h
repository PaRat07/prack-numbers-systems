#include "SFML/Graphics.hpp"

class InputWindow : sf::Drawable {
 public:
    InputWindow(sf::Vector2f pos, sf::Vector2f size)
        : pos_(pos)
        , size_(size)
    {}

    void Click(sf::Vector2f pos) {
        if (abs(pos.x - pos_.x) <= size_.x / 2 && abs(pos.y - pos_.y) <= size_.y / 2) {
            active_ = true;
        }
    }


    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

    }

    void Write(sf::Event::TextEvent event) {
        if (active_) {
            data.push_back(event.unicode);
        }
    }

    std::string GetText() const {
        return data;
    }
 private:
    sf::Vector2f pos_, size_;
    int draw_from_ = 0;
    std::string data;
    bool active_ = false;
};