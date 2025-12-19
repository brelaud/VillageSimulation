#pragma once
#include "Entity.hpp"
#include <string>
#include <random>

class Villager : public Entity {
private:
    int age = 0;
    int pv = 10;
    std::string job;
    float successRate = 0.6f;
    bool isHarvesting = false;
    float harvestTimer = 0.f;
    float speed = 80.f;
    std::mt19937 rng;
    sf::Color color;
    sf::Vector2f targetPos;
    
public:
    Villager(sf::Vector2f pos);
    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;
    float getRadius() const override { return 12.f; }
    bool isAlive() const override { return pv > 0; }
    int getPV() const { return pv; }
    int getAge() const { return age; }
    std::string getJob() const { return job; }
    float getSuccessRate() const { return successRate; }
    void assignJob();
    void startHarvest(float harvestTime);
    bool attemptAction();
};
