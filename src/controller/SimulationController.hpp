#pragma once
#include "../model/world.hpp"
#include "../view/Renderer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class SimulationController {
private:
    World model;
    Renderer view;
    sf::RenderWindow& window;
    float dtAccumulator = 0.f;
    bool paused = false;
    
public:
    SimulationController(sf::RenderWindow& w);
    void init();
    void update(float deltaTime);
    void render();
    void handleEvents();
};
