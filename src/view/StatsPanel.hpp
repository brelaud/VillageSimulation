#pragma once
#include "../model/world.hpp"
#include <SFML/Graphics.hpp>

class StatsPanel {
private:
    const World& world;
    sf::Font& font;
    sf::Text statsText;
    
public:
    StatsPanel(const World& w, sf::Font& f);
    void update();
    void draw(sf::RenderTarget& target);
};
