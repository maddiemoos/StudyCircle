// Handles SFML identites
#pragma once
#include <SFML/Window.hpp>

enum class UIEventType {
    None,
    MouseMove,
    MouseDown,
    MouseUp,
    TextEntered,
    KeyPressed
};

struct UIEvent {
    UIEventType type = UIEventType::None;

    sf::Vector2f mousePos{ 0.f, 0.f };

    // payloads - for text input and keyboard scanning
    char32_t unicode = 0;
    sf::Keyboard::Scancode key = sf::Keyboard::Scancode::Unknown;
};