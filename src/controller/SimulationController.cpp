#include "SimulationController.hpp"
#include <SFML/Window/Event.hpp>

SimulationController::SimulationController(sf::RenderWindow& w) 
    : window(w), view(w, model) {}

void SimulationController::init() {
    model = World();  // Reset complet
    for (int i = 0; i < 3; i++) model.spawnVillager();  // 3 chasseurs
    for (int i = 0; i < 3; i++) model.spawnVillager();  // 3 ramasseurs
    for (int i = 0; i < 4; i++) model.spawnResourceZone(false);
    for (int i = 0; i < 2; i++) model.spawnResourceZone(true);
    model.addResources(50);
}

void SimulationController::update(float deltaTime) {
    handleEvents();
    
    if (!paused) {
        dtAccumulator += deltaTime;
        if (dtAccumulator > 1.f/60.f) {
            model.update(dtAccumulator);
            dtAccumulator = 0.f;
        }
    }
}

void SimulationController::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) paused = !paused;
            if (event.key.code == sf::Keyboard::R) init();
        }
    }
}

void SimulationController::render() {
    view.render();
}
