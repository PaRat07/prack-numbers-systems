#include "button.h"

template<class Func>
void Button<Func>::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape rect(size_);
    rect.setPosition(pos_.x - size_.x / 2, pos_.y - size_.y / 2);
    target.draw(rect);
}

template<class Func>
void Button<Func>::Click(sf::Vector2f pos) const {
    if (abs(pos.x - pos_.x) <= size_.x / 2 && abs(pos.y - pos_.y) <= size_.y / 2) {
        callback_();
    }
}

template<class Func>
Button<Func>::Button(sf::Vector2f sz, sf::Vector2f pos, const Func &cb)
        : callback_(cb)
        , size_(sz)
        , pos_(pos)
{}
