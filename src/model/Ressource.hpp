#pragma once
#include "Entity.hpp"

class ResourceZone : public Entity {
private:
    float quantity = 50.f;
    float respawnTimer = 0.f;
    bool isHuntZone;
    float harvestTime;  // 5s récolte, 8s chasse
    
public:
    ResourceZone(sf::Vector2f pos, bool hunt);
    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;
    float getRadius() const override { return 25.f; }
    bool isAlive() const override { return quantity > 0 || respawnTimer > 0; }
    bool isHuntZone() const { return isHuntZone; }
    float getHarvestTime() const { return harvestTime; }
    void consume();
};
