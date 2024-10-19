#pragma once

#include "iceCreamRender.h"

typedef struct {
	u32 VBO; 
	u32 EBO; 
	u32 VAO;
	u32 ShaderDefault; 
	u32 TextureColor; 
	mat4x4 projection; 
} IceCreamPipeline;   

SDL_Window* IcreamWindowInit(u32 width, u32 height);
void IceCreamRenderInitQaud(u32* vbo, u32* ebo, u32* vao); 
void IceCreamInitShaders(IceCreamPipeline* state); 
void IceCreamInitColorTexture(u32* texture);
u32 IceCreamCompileShader(const char* pathVertex, const char* pathFrag); 

