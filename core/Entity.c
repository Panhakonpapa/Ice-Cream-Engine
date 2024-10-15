#include "Entity.h"

#include <stdlib.h>


Entity creation(float x, float y, float z) {
    
    Entity entity = {x, y, z}; 

    return entity;
}

EntityManager* createEntityManager(size_t initialize_size) {
    EntityManager* manager = (EntityManager *)malloc(sizeof(EntityManager)); 
    manager->entitise = (Entity*)malloc(initialize_size * sizeof(Entity));
    manager->size = 0; 
    manager->capacity = initialize_size;
    return manager; 
}


void addEntity(EntityManager* manager, Entity entity) {
    if (manager->size == manager->capacity) {
        manager->capacity *= 2; 
        manager->entitise = (Entity*)realloc(manager->entitise, manager->capacity * sizeof(Entity));
    }
    manager->entitise[manager->size] = entity; 
    manager->size++; 
}

void freeEntity(EntityManager *manager) {
    free(manager->entitise); 
    free(manager);
}

