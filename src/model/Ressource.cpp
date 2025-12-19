#include "Ressource.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

ResourceZone::ResourceZone(sf::Vector2f pos, bool hunt) 
    : position(pos), isHuntZone(hunt) {
    harvestTime = hunt ? 8.f : 5.f;
}

void ResourceZone::consume() {
    quantity -= 3.f;
    respawnTimer = 10.f;
}

void ResourceZone::update(float dt) {
    if (quantity <= 0) {
        respawnTimer -= dt;
        if (respawnTimer <= 0) quantity = 50.f;
    }
}

void ResourceZone::draw(sf::RenderTarget& target) {
    sf::CircleShape circle(getRadius());
    circle.setPosition(position - sf::Vector2f(getRadius(), getRadius()));
    circle.setFillColor(isHuntZone ? sf::Color(200, 50, 50) : sf::Color(50, 200, 50));
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color::White);
    target.draw(circle);
}
