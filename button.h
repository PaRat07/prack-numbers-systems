#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


template<class Func>
class Button : public sf::Drawable {
 public:
    Button(sf::Vector2f sz, sf::Vector2f pos, const Func &cb);

    void Click(sf::Vector2f pos) const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    Func callback_;
    sf::Vector2f size_, pos_;
};
