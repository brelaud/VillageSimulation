#include "controller/SimulationController.hpp"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Village Simulation - BTS MVC");
    window.setFramerateLimit(60);
    
    SimulationController controller(window);
    controller.init();
    
    sf::Clock clock;
    while (window.isOpen()) {
        controller.update(clock.restart().asSeconds());
        controller.render();
    }
    return 0;
}
