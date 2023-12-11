#include <functional>
#include "SFML/Graphics.hpp"

#include "rounded_rectangle.h"
#include "general_data.h"

class InputWindow : public sf::Drawable {
 public:
    InputWindow(sf::Vector2f pos, sf::Vector2f size);

    void Click(sf::Vector2f pos);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void Write(sf::Uint32 event);

    void Activate();

    void SetSwitchActivated(std::function<void()> new_val);

    std::string GetText() const {
        return data_;
    }
 private:
    sf::Vector2f pos_, size_;
    std::string data_;
    bool active_ = false;
    std::function<void()> switch_activated;
};
