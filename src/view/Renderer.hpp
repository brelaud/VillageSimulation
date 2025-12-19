#pragma once
#include "../model/world.hpp"
#include "StatsPanel.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Renderer {
private:
    sf::RenderWindow& window;
    const World& world;
    sf::Font font;
    
public:
    Renderer(sf::RenderWindow& w, const World& wld);
    void render();
};
