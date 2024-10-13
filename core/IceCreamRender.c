#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

#include "OpenGL.h"
#include "IceCreamRender.h" 


char* loadShaderFile(char* filePath) {
  FILE* OpenFile = fopen(filePath, "r"); 
  if (OpenFile == NULL) {
      printf("Error open shaderFile \n"); 
      exit(EXIT_FAILURE); 
  }
  fseek(OpenFile, 0, SEEK_END);
  int lenght = ftell(OpenFile);
  fseek(OpenFile, 0, SEEK_SET); 

  char* readContent = (char *)malloc(lenght + 1);

  if (readContent == NULL) {
      printf("Error Reading shaderFile \n"); 
      exit(EXIT_FAILURE); 
  }
  fread(readContent, 1, lenght, OpenFile);
  readContent[lenght] = '\0'; 
  fclose(OpenFile); 

  return readContent; 
}

unsigned int IceCreamCompileShader(GraphicShader* iceCreamShader, char* VertexShaderProgram, char* FragmentShaderProgram) {
  
  int  success;
  char infoLog[512];

  const char* vertexShaderSource = loadShaderFile(VertexShaderProgram); 
  const char* FragmentShaderSource = loadShaderFile(FragmentShaderProgram); 
  if (!vertexShaderSource || !FragmentShaderSource) {
      printf("Failed to load shaders\n");
      return 0;
  }

  iceCreamShader->vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(iceCreamShader->vertexShader, 1, &vertexShaderSource, NULL); 
  glCompileShader(iceCreamShader->vertexShader); 

  /* Vertex shader Compiler error cheak */ 
  glGetShaderiv(iceCreamShader->vertexShader , GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(iceCreamShader->vertexShader , 512, NULL, infoLog);
      printf("Compling Shader Error\n"); 
      exit(EXIT_FAILURE); 
  }
  
  iceCreamShader->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
  glShaderSource(iceCreamShader->fragmentShader,  1, &FragmentShaderSource, NULL); 
  glCompileShader(iceCreamShader->fragmentShader ); 

  /* Fragment Shader Compiler error cheak */ 
  glGetShaderiv(iceCreamShader->fragmentShader , GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(iceCreamShader->vertexShader , 512, NULL, infoLog);
      printf("Compling fragment shader Error\n"); 
      exit(EXIT_FAILURE); 
  }
  
  iceCreamShader->ShaderProgram = glCreateProgram();  
  glAttachShader(iceCreamShader->ShaderProgram, iceCreamShader->vertexShader); 
  glAttachShader(iceCreamShader->ShaderProgram, iceCreamShader->fragmentShader); 
  glLinkProgram( iceCreamShader->ShaderProgram ); 

  glGetProgramiv( iceCreamShader->ShaderProgram,  GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(iceCreamShader->ShaderProgram, 512, NULL, infoLog);
      printf("Linker shader Error\n"); 
      exit(EXIT_FAILURE); 
  }
  
  glDeleteShader(iceCreamShader->vertexShader);
  glDeleteShader(iceCreamShader->fragmentShader);

  return iceCreamShader->ShaderProgram; 
} 
unsigned int IceCreamRenderTringle(GraphicBuffer* iceCreamRenderBuffer) {
  /* Vertex data */
  float vertices[] = {
    /* Position */          /* RGBA */ 
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f  // top left 
  };
  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
  };  

  /* Graphic Binding */
  glGenBuffers(1, &iceCreamRenderBuffer->VBO); 
  glGenBuffers(1, &iceCreamRenderBuffer->EBO); 
  glGenVertexArrays(1, &iceCreamRenderBuffer->VAO);

  /* Bind */
  glBindBuffer(GL_ARRAY_BUFFER, iceCreamRenderBuffer->VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0); 
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float))); 
  glEnableVertexAttribArray(1);

  /* Unbind */
  glBindBuffer(GL_ARRAY_BUFFER, 0); 
  glBindVertexArray(0); 
  
  return iceCreamRenderBuffer->VAO; 
} 

/* TODO: WORKING ON TEXTURE TONGIHT */

