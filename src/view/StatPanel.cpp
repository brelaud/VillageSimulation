#include "StatsPanel.hpp"
#include <sstream>
#include <iomanip>

StatsPanel::StatsPanel(const World& w, sf::Font& f) : world(w), font(f) {
    statsText.setFont(f);
    statsText.setCharacterSize(20);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition(10, 10);
}

void StatsPanel::update() {
    std::ostringstream oss;
    
    // Timer MM:SS
    int minutes = static_cast<int>(world.getGameTime()) / 60;
    int seconds = static_cast<int>(world.getGameTime()) % 60;
    oss << "⏱️ Temps: " << std::setfill('0') << std::setw(2) 
        << minutes << ":" << std::setw(2) << seconds << "\n\n";
    
    oss << "👥 Villageois: " << world.getStats().at("villagers") << "\n";
    oss << "💰 Ressources: " << world.getGlobalResources() << "\n";
    oss << "📊 Seuil spawn: " << world.resourceThreshold << "\n\n";
    
    // Stats détaillées
    int totalPV = 0, totalAge = 0, hunterCount = 0, gathererCount = 0;
    for (const auto& e : world.getEntities()) {
        if (auto* v = dynamic_cast<Villager*>(e.get())) {
            totalPV += v->getPV();
            totalAge += v->getAge();
            if (v->getJob() == "Chasseur") hunterCount++;
            else gathererCount++;
        }
    }
    
    if (world.getStats().at("villagers") > 0) {
        oss << "❤️ PV moyen: " << (totalPV / world.getStats().at("villagers")) << "\n";
        oss << "👴 Âge moyen: " << (totalAge / world.getStats().at("villagers")) << "\n";
        oss << "⚔️ Chasseurs: " << hunterCount << " | 🌾 Ramasseurs: " << gathererCount;
    }
    
    statsText.setString(oss.str());
}

void StatsPanel::draw(sf::RenderTarget& target) {
    update();
    target.draw(statsText);
}
