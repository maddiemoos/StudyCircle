#pragma once
#include "../uielement.hpp"
#include "uievent.hpp"

class UIManager {
private:
    std::unique_ptr<UIElement> root;

    UIEvent translate(const sf::Event& e, const sf::RenderWindow& window);

public:
    void setRoot(std::unique_ptr<UIElement> r);

    void processEvent(const sf::Event& e, const sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow& window);
};