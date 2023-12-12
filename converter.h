#include <iostream>
#include "SFML/Graphics.hpp"

#include "input_window.h"
#include "button.h"
#include "general_data.h"
#include "output_window.h"
#include "fraction.h"
#include "error_message.h"

class Converter {
 public:
    Converter()
        : number_("Number", font, letter_size)
        , num_(sf::Vector2f(10, 60), sf::Vector2f(1900, 100))
        , old_base_("Old Base", font, letter_size)
        , p_(sf::Vector2f(10, 260), sf::Vector2f(1900, 100))
        , new_base_("New Base", font, letter_size)
        , q_(sf::Vector2f(10, 460), sf::Vector2f(1900, 100))
        , result_("Result", font, letter_size)
        , res_(sf::Vector2f(10, 660), sf::Vector2f(1900, 100))
        , ok_(sf::Vector2f(1670, 930), sf::Vector2f(200, 100), "Convert", [&] { Convert(); })
        , win_(sf::VideoMode(1920, 1080), "Numbers converter", sf::Style::Fullscreen)
    {
        number_.setPosition(10, 10);
        old_base_.setPosition(10, 210);
        new_base_.setPosition(10, 410);
        result_.setPosition(10, 610);

        number_.setFillColor(text_color);
        old_base_.setFillColor(text_color);
        new_base_.setFillColor(text_color);
        result_.setFillColor(text_color);

        Render();
        while (win_.isOpen()) {
            sf::Event event{};
            while (win_.pollEvent(event)) {
                if (err_.has_value()) {
                    err_.reset();
                } else {
                    switch (event.type) {
                        case sf::Event::TextEntered: {
                            q_.Write(event.text.unicode);
                            p_.Write(event.text.unicode);
                            num_.Write(event.text.unicode);
                            Render();
                            break;
                        }
                        case sf::Event::MouseButtonPressed: {
                            ok_.Click(sf::Vector2f(event.touch.x, event.touch.y));
                            num_.Click(sf::Vector2f(event.touch.x, event.touch.y));
                            p_.Click(sf::Vector2f(event.touch.x, event.touch.y));
                            q_.Click(sf::Vector2f(event.touch.x, event.touch.y));
                            Render();
                            break;
                        }
                        case sf::Event::Closed:
                            win_.close();
                    }
                }
            }
        }
    }

    void Convert() {
        try {
            Fraction frac;
            frac.Input(num_.GetText(), std::stoi(p_.GetText()));
            res_.SetOutput(Print(frac, std::stoi(q_.GetText())));
        } catch (const std::exception &err) {
            err_.emplace(err.what());
        }
    }
 private:
    std::optional<ErrorMessage> err_;
    Button ok_;
    sf::Text number_, old_base_, new_base_, result_;
    InputWindow num_, p_, q_;
    OutputWindow res_;
    sf::RenderWindow win_;

    void Render() {
        win_.clear(background_color);
        win_.draw(ok_);
        win_.draw(num_);
        win_.draw(number_);
        win_.draw(p_);
        win_.draw(q_);
        win_.draw(old_base_);
        win_.draw(new_base_);
        win_.draw(result_);
        win_.draw(res_);
        if (err_.has_value()) {
            win_.draw(*err_);
        }
        win_.display();
    }
};