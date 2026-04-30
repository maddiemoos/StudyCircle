#include "uimanager.hpp"

UIEvent UIManager::translate(const sf::Event& e, const sf::RenderWindow& window) {
    UIEvent out{};

    const sf::Vector2f mouse =
        static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    out.mousePos = mouse;

    // I would love to use a switch statement here
    // But SFML recently went "type-safe", so it would be illegal
    // However, I want to handle events still, so here we are

    if (e.getIf<sf::Event::MouseMoved>()) {
        out.type = UIEventType::MouseMove;
    }
    else if (e.getIf<sf::Event::MouseButtonPressed>()) {
        out.type = UIEventType::MouseDown;
    }
    else if (e.getIf<sf::Event::MouseButtonReleased>()) {
        out.type = UIEventType::MouseUp;
    }
    else if (const auto* text = e.getIf<sf::Event::TextEntered>()) {
        out.type = UIEventType::TextEntered;
        out.unicode = text->unicode;
    }
    else if (const auto* key = e.getIf<sf::Event::KeyPressed>()) {
        out.type = UIEventType::KeyPressed;
        out.key = key->scancode;
    }
    else {
        out.type = UIEventType::None;
    }

    return out;
}

void UIManager::setRoot(std::unique_ptr<UIElement> r) {
    root = std::move(r);
}

void UIManager::processEvent(const sf::Event& e, const sf::RenderWindow& window) {
    if (!root) return;

    UIEvent uie = translate(e, window);
    if (uie.type != UIEventType::None) {
        root->handleEvent(uie);
    }
}

void UIManager::update(float dt) {
    if (root) root->update(dt);
}

void UIManager::draw(sf::RenderWindow& window) {
    if (root) root->draw(window);
}