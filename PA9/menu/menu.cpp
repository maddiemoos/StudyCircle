#include "menu.hpp"

void drawRectangle()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "PA9 SFML Test");

    sf::RectangleShape box(sf::Vector2f(200.f, 150.f));
    box.setFillColor(sf::Color::Green);
    box.setPosition(sf::Vector2f(300.f, 225.f));

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(box);
        window.display();
    }
}