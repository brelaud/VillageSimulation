#include "villager.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <algorithm>

Villager::Villager(sf::Vector2f pos) : position(pos), rng(std::random_device{}()) {
    color = sf::Color(100 + (rng()%150), 100 + (rng()%150), 150);
    targetPos = pos + sf::Vector2f(rng()%200-100, rng()%200-100);
    assignJob();
}

void Villager::assignJob() {
    job = (rng() % 2) ? "Chasseur" : "Ramasseur";
    successRate = (job == "Ramasseur") ? 0.6f : 1.0f;
}

void Villager::startHarvest(float harvestTime) {
    isHarvesting = true;
    harvestTimer = harvestTime;
}

bool Villager::attemptAction() {
    std::uniform_real_distribution<float> dist(0.f, 1.f);
    
    if (job == "Chasseur") {
        if (dist(rng) < successRate) {
            pv += 1;  // +1 PV
            return true;  // +3 ressources dans World
        } else {
            pv -= 3;  // -3 PV
            return false;
        }
    } else {  // Ramasseur
        bool success = dist(rng) < successRate;
        if (success) {
            if (dist(rng) < 0.3f) successRate = std::min(1.0f, successRate + 0.05f);
            return true;
        } else {
            if (dist(rng) < 0.2f) successRate = std::max(0.2f, successRate - 0.05f);
            if (successRate < 0.2f) pv = 0;  // Exclusion
            return false;
        }
    }
}

void Villager::update(float dt) {
    age += dt / 15.f;  // +1 an toutes les 15s
    if (age > 40) pv = 0;
    
    if (isHarvesting) {
        harvestTimer -= dt;
        if (harvestTimer <= 0.f) {
            attemptAction();
            isHarvesting = false;
        }
        velocity = {0, 0};
    } else {
        // Déplacement vers cible
        sf::Vector2f dir = targetPos - position;
        float dist = std::sqrt(dir.x*dir.x + dir.y*dir.y);
        if (dist > 10.f) {
            dir /= dist;
            velocity = dir * speed;
        } else {
            // Nouvelle cible aléatoire
            targetPos = position + sf::Vector2f(rng()%400-200, rng()%400-200);
        }
        
        position += velocity * dt;
        
        // Bordures village (centre)
        if (position.x < 450 || position.x > 750) velocity.x *= -0.8f;
        if (position.y < 250 || position.y > 550) velocity.y *= -0.8f;
    }
    
    pv -= dt * 0.1f;  // Vieillissement naturel
}

void Villager::draw(sf::RenderTarget& target) {
    sf::CircleShape circle(getRadius());
    circle.setPosition(position - sf::Vector2f(getRadius(), getRadius()));
    circle.setFillColor(isHarvesting ? sf::Color::Yellow : color);
    circle.setOutlineColor(pv < 3 ? sf::Color::Red : sf::Color::White);
    circle.setOutlineThickness(2);
    target.draw(circle);
    
    // Debug job
    sf::CircleShape jobInd(4);
    jobInd.setPosition(position + sf::Vector2f(15, -15));
    jobInd.setFillColor(job == "Chasseur" ? sf::Color::Red : sf::Color::Green);
    target.draw(jobInd);
}
