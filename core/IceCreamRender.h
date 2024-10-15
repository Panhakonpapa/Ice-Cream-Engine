#ifndef RENDER_CORE_H
#define RENDER_CORE_H

#include "OpenGL.h"
#include "Entity.h"
#include "Math.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int ShaderProgram; 
    unsigned int renderID; 
}GraphicShader;

typedef struct {
    unsigned int VBO;
    unsigned int VAO; 
    unsigned int EBO;  
} GraphicBuffer;

char* loadShaderFile(char* filePath); 
void IceCreamCompileShader(char* VertexShaderProgram, char* FragmentShaderProgram);  
void IceCreamRenderPipeline(); 
void initialize_graphic();  
void printInfo(char* filtPath);
void draw();

#endif 
