#include "menu.hpp"

void drawRectangle()
{
    sf::RenderWindow window(sf::VideoMode({ 1600, 780 }), "PA9 SFML Test");

    sf::RectangleShape box(sf::Vector2f(1600.f, 780.f));
    box.setFillColor(sf::Color::White);
    box.setPosition(sf::Vector2f(0.f, 0.f));

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