#pragma once 

#include <SDL2/SDL.h>

#include "linmath.h"
#include "utils.h"

typedef struct {
	SDL_Window* window; 
	f32 with; 
	f32 height; 
} IceCreamRenderer; 

void IceCreamGraphicInit(void);
void IceCreamRenderBegin(void);
void IceCreamRenderEnd(void); 
void IceCreamRenderQuad(vec2 position, vec2 size, vec4 colors); 

