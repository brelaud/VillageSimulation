#include "Renderer.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

Renderer::Renderer(sf::RenderWindow& w, const World& wld) : window(w), world(wld) {
    font.loadFromFile("assets/fonts/arial.ttf");
}

void Renderer::render() {
    window.clear(sf::Color(15, 30, 25));
    
    // Village central
    sf::RectangleShape village(sf::Vector2f(300, 300));
    village.setPosition(450, 250);
    village.setFillColor(sf::Color(80, 60, 40));
    village.setOutlineColor(sf::Color(150, 120, 80));
    village.setOutlineThickness(4);
    window.draw(village);
    
    // Entités
    for (const auto& entity : world.getEntities()) {
        entity->draw(window);
    }
    
    // HUD Stats
    StatsPanel stats(world, font);
    stats.draw(window);
    
    // Cadre HUD
    sf::RectangleShape frame(sf::Vector2f(280, 220));
    frame.setPosition(5, 5);
    frame.setFillColor(sf::Color(0, 0, 0, 200));
    frame.setOutlineColor(sf::Color::Gold);
    frame.setOutlineThickness(3);
    window.draw(frame);
    
    // Instructions
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("SPACE: Pause | R: Reset | Mouvements automatiques");
    instructions.setCharacterSize(16);
    instructions.setFillColor(sf::Color(200, 200, 200, 150));
    instructions.setPosition(10, 750);
    window.draw(instructions);
    
    window.display();
}
