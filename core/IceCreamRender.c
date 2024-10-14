#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

#include "OpenGL.h"
#include "IceCreamRender.h" 

#define STB_IMAGE_IMPLEMENTATION
#include "imageLoader.h"

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

void IceCreamCompileShader(GraphicShader* iceCreamShader, char* VertexShaderProgram, char* FragmentShaderProgram) {
  
  int  success;
  char infoLog[512];

  const char* vertexShaderSource = loadShaderFile(VertexShaderProgram); 
  const char* FragmentShaderSource = loadShaderFile(FragmentShaderProgram); 
  if (!vertexShaderSource || !FragmentShaderSource) {
      printf("Failed to load shaders\n");
      exit(EXIT_FAILURE); 
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
} 
unsigned int IceCreamRenderTringle(GraphicBuffer* iceCreamRenderBuffer) {
  /* Vertex data */
  float vertices[] = {
    /* Position */          /* RGBA */            /* Texture Cord */
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f  // top left 
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
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iceCreamRenderBuffer->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0); 
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float))); 
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float))); 
  glEnableVertexAttribArray(2);

  /* Unbind */
  glBindBuffer(GL_ARRAY_BUFFER, 0); 
  glBindVertexArray(0); 
 
  /* Data in render it vertex to the graphic and give back the user ID */
  unsigned int renderID = iceCreamRenderBuffer->VAO;

  return renderID; 
} 

unsigned int IceCreamTexture(char* filePath) {
    int width, height, bpp;
    unsigned char* SpriteData = stbi_load(
                            filePath, 
                             &width, &height, &bpp, 0); 
    unsigned int returnPtr; 
   
    glGenTextures(1, &returnPtr); 
    glBindTexture(GL_TEXTURE_2D, returnPtr); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (SpriteData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, SpriteData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(SpriteData);
    return returnPtr; 
}

void iceCreamDraw(GraphicShader* Program,GraphicBuffer* iceCreamRenderBuffer ) {

    glBindTexture(GL_TEXTURE_2D, Program->texture); 
    glUseProgram(Program->ShaderProgram); 
    glBindVertexArray(iceCreamRenderBuffer->VAO); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

