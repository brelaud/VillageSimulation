#pragma once
#include <SFML/System/Vector2.hpp>
#include <memory>

class Entity {
protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
public:
    virtual ~Entity() = default;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual float getRadius() const = 0;
    sf::Vector2f getPosition() const { return position; }
    virtual bool isAlive() const = 0;
};
