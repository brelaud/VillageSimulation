#include "world.hpp"
#include <random>

void World::update(float dt) {
    tick++;
    gameTime += dt;
    spawnTimer += dt;
    
    // Mise à jour entités
    for (auto& entity : entities) {
        entity->update(dt);
    }
    
    // Stats
    stats["villagers"] = 0;
    stats["resources"] = 0;
    villagerCount = 0;
    for (const auto& e : entities) {
        if (dynamic_cast<Villager*>(e.get())) {
            stats["villagers"]++;
            villagerCount++;
        } else if (dynamic_cast<ResourceZone*>(e.get())) {
            stats["resources"]++;
        }
    }
    
    // Spawn villageois (90s ou ressources suffisantes)
    if (spawnTimer > 90.f && globalResources >= resourceThreshold) {
        spawnVillager();
        spawnTimer = 0.f;
        if (villagerCount % 2 == 0) resourceThreshold += 10;
    }
    
    // Spawn zones ressources
    if (tick % 600 == 0) spawnResourceZone(false);  // Récolte
    if (tick % 900 == 0) spawnResourceZone(true);   // Chasse
    
    // Spawning
    while (!spawnQueue.empty()) {
        entities.push_back(std::move(spawnQueue.front()));
        spawnQueue.pop();
    }
    
    cleanup();
}

void World::spawnVillager() {
    spawnQueue.push(std::make_unique<Villager>(
        sf::Vector2f(600 + (rand()%100-50), 400 + (rand()%100-50))
    ));
}

void World::spawnResourceZone(bool huntZone) {
    float angle = rand() % 360 * 3.14159f / 180.f;
    float dist = 200 + rand() % 150;
    sf::Vector2f pos(600 + cos(angle) * dist, 400 + sin(angle) * dist);
    spawnQueue.push(std::make_unique<ResourceZone>(pos, huntZone));
}

void World::cleanup() {
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [](const auto& e){ return !e->isAlive(); }),
        entities.end()
    );
}
