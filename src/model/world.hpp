#pragma once
#include "Entity.hpp"
#include "villager.hpp"
#include "Ressource.hpp"
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>

class World {
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::unordered_map<std::string, int> stats;
    std::queue<std::unique_ptr<Entity>> spawnQueue;
    int globalResources = 0;
    int villagerCount = 0;
    int resourceThreshold = 20;
    uint64_t tick = 0;
    float gameTime = 0.f;
    float spawnTimer = 0.f;
    
public:
    void update(float dt);
    void spawnVillager();
    void spawnResourceZone(bool huntZone);
    const auto& getEntities() const { return entities; }
    const auto& getStats() const { return stats; }
    int getGlobalResources() const { return globalResources; }
    float getGameTime() const { return gameTime; }
    uint64_t getTick() const { return tick; }
    void cleanup();
    void addResources(int amount) { globalResources += amount; }
};
