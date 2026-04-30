#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

// Abstract class (Parent) with useful tools from SFML
// We use a "retained-mode" UI
// This means
//  - UI Elements persist as Objects
//  - Each element owns it's own State, Bounds, and Children
//  - We traverse a tree every frame
//    -> handleEvent -> update -> render
class UIElement {
protected:
    sf::Vector2f position{ 0,0 };
    sf::Vector2f size{ 0,0 };

    UIElement* parent = nullptr;
    std::vector<std::unique_ptr<UIElement>> children;

public:
    virtual ~UIElement() = default;

    // --- Event handling ---
    virtual bool handleEvent(const UIEvent& e) {
        // children first (topmost last drawn = highest priority)
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            if ((*it)->handleEvent(e))
                return true;
        }
        // Outside of bounds of the element
        // This was a byproduct of the changes in uimanager.cpp
        return false;
    }

    // Frame lifecycle
    virtual void update(float dt) {
        for (auto& c : children)
            c->update(dt);
    }

    virtual void draw(sf::RenderWindow& window) {
        for (auto& child : children)
            child->draw(window);
    }

    // Tree Management
    void addChild(std::unique_ptr<UIElement> child) {
        child->parent = this;
        children.push_back(std::move(child));
    }

    // Geometry getters/setters
    sf::FloatRect getBounds() const {
        return { position, size };
    }

    bool contains(sf::Vector2f point) const {
        return getBounds().contains(point);
    }

    virtual void setPosition(float x, float y) { position = { x, y }; }
    virtual void setSize(float w, float h) { size = { w, h }; }
};