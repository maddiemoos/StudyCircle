#pragma once
#include <SFML/Graphics.hpp>

// Abstract class (Parent) with useful tools from SFML
// We use a "retained-mode" UI
// This means
//  - UI Elements persist as Objects
//  - Each element owns it's own State, Bounds, and Children
//  - We traverse a tree every frame
//    -> handleEvent -> update -> render
class UIElement {
protected:
    // Protected elements for use by elements
    sf::Vector2f position;
    sf::Vector2f size;
    bool visible = true;
    bool hovered = false;
    bool focused = false;


    UIElement* parent = nullptr;
    std::vector<std::unique_ptr<UIElement>> children;

public:
    virtual ~UIElement() = default;

    // Handles inputs (for use in buttons or text box)
    virtual void handleEvent(const sf::Event& event, const sf::Vector2f& mousePos) {
        // Traverse children FIRST (top-most last)
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            (*it)->handleEvent(event, mousePos);
        }
    }

    virtual void update(float dt) {}
    virtual void draw(sf::RenderWindow& window) {
        for (auto& child : children)
            child->draw(window);
    }

    void addChild(std::unique_ptr<UIElement> child) {
        child->parent = this;
        children.push_back(std::move(child));
    }

    sf::FloatRect getBounds() const {
        return { position, size };
    }

    bool contains(sf::Vector2f point) const {
        return getBounds().contains(point);
    }

    virtual void setPosition(float x, float y) { position = { x, y }; }
    virtual void setSize(float w, float h) { size = { w, h }; }
};