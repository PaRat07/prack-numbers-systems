#include "SFML/Graphics.hpp"

#include "general_data.h"
#include "rounded_rectangle.h"

 class OutputWindow : public sf::Drawable {
 public:
    OutputWindow(sf::Vector2f pos, sf::Vector2f size);

    void SetOutput(std::string output);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 private:
    sf::Vector2f pos_, size_;
    std::string output_;
};
