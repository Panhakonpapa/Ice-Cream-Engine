#ifndef ENTITY_CORE_H 
#define ENTITY_CORE_H

#include <stdio.h>

typedef struct {
    float ex; 
    float ey; 
    float ez; 
} Entity;

typedef struct {
    Entity* entitise; 
    size_t size; 
    size_t capacity; 
} EntityManager;

Entity creation(float x, float y, float z); 
EntityManager* createEntityManager(size_t initialize_size); 

void addEntity(EntityManager* manager, Entity entity); 
void freeEntity(EntityManager* manager); 


#endif 
