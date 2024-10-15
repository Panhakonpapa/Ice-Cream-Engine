#include "IceCreamRender.h"
#include "Entity.h"
#include "Math.h"
#include <stdio.h>

extern GraphicShader* iceCreamShader; 
extern GraphicBuffer* iceCreamRenderBuffer; 
extern EntityManager* manager;  


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
void printInfo(char* filtPath) {

    FILE* fileopen = fopen(filtPath, "r");

    if (fileopen == NULL) {
        perror("Error file reading\n"); 
        exit(EXIT_FAILURE); 
    } 

    char buffer[256]; 

    while (fgets(buffer, sizeof(buffer), fileopen) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(fileopen); 
}

void IceCreamCompileShader(char* VertexShaderProgram, char* FragmentShaderProgram) {
    unsigned int vertexShader, fragmentShader;
   
    const char* loadVertexShader = loadShaderFile(VertexShaderProgram);
    const char* loadFragmentShader = loadShaderFile(FragmentShaderProgram);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &loadVertexShader, NULL); 
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &loadFragmentShader , NULL); 
    glCompileShader(fragmentShader);

    iceCreamShader->ShaderProgram = glCreateProgram(); 
    glAttachShader(iceCreamShader->ShaderProgram, vertexShader); 
    glAttachShader(iceCreamShader->ShaderProgram, fragmentShader);
    glLinkProgram(iceCreamShader->ShaderProgram); 

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void IceCreamRenderPipeline() {
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    glGenVertexArrays(1, &iceCreamRenderBuffer->VAO);
    glGenBuffers(1, &iceCreamRenderBuffer->EBO); 
    glGenBuffers(1, &iceCreamRenderBuffer->VBO);

    glBindVertexArray(iceCreamRenderBuffer->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, iceCreamRenderBuffer->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iceCreamRenderBuffer->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    iceCreamShader->renderID = iceCreamRenderBuffer->VAO;  

    glBindVertexArray(0); 

}

void initialize_graphic() {
    
    char* ShaderFile = "/home/panha/Ice-Cream-Engine/core/ShaderBatchFile.glsl";
    char* FragmentrFile = "/home/panha/Ice-Cream-Engine/core/FragmentBatchFile.glsl";

    IceCreamCompileShader(ShaderFile, FragmentrFile);
    IceCreamRenderPipeline();

}

void draw() {
    
    float translateX = manager->entitise[0].ex; 
    float translateY = manager->entitise[0].ey; 
    float translateZ = manager->entitise[0].ez;

    float scaleX = 0.5f; // Scale down by half in x
    float scaleY = 0.5f; // Scale down by half in y
    float scaleZ = 0.5f; // Scale down by half in z

    mat4 modal = mat4_transformation(translateX, translateY, translateZ, scaleX, scaleY, scaleZ); 

    unsigned int transformLoc = glGetUniformLocation(iceCreamShader->ShaderProgram, "transform");

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, modal.m);

    glUseProgram(iceCreamShader->ShaderProgram);
    glBindVertexArray(iceCreamShader->renderID); 
    glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_INT, 0);

}









