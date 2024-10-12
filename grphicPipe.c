#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {

  unsigned int VBO; 
  unsigned int VAO; 
  unsigned int EBO;

} GraphicBuffer; 

typedef  struct {

  unsigned int vertexShader; 
  unsigned int fragmentShader;
  unsigned int ShaderProgram; 

} GraphicShader;
  
typedef  struct {
  unsigned int QuadMesh; 
}Graphic;

/* Prodotype desgin */
typedef struct {

  GraphicBuffer iceCreamRenderBuffer; 
  GraphicShader iceCreamShader;  
  Graphic iceCreamRenderer; 

} IceCreamEngine;

IceCreamEngine engine;

GraphicBuffer iceCreamRenderBuffer; 
GraphicShader iceCreamShader;  
Graphic iceCreamRenderer; 

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vertexColor; \n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos, 1.0);"
    "    vertexColor = aColor;\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 vertexColor; "
    "void main()\n"
    "{\n"
    "   FragColor = vec4(vertexColor, 1.0);\n"
    "}\n\0";

unsigned int CompilingShader() {
   
  iceCreamShader.vertexShader = glCreateShader(GL_VERTEX_SHADER); 
  glShaderSource(iceCreamShader.vertexShader, 1, &vertexShaderSource, NULL); 
  glCompileShader(iceCreamShader.vertexShader); 
  int  success;
  char infoLog[512];
  glGetShaderiv(iceCreamShader.vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    printf("Vertex Shader Compling failure %s\n", infoLog); 
    exit(EXIT_FAILURE); 
  }
  
  iceCreamShader.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
  glShaderSource(iceCreamShader.fragmentShader , 1, &fragmentShaderSource, NULL); 
  glCompileShader(iceCreamShader.fragmentShader );

  glGetShaderiv(iceCreamShader.fragmentShader , GL_COMPILE_STATUS, &success);
  if (!success) {
    printf("Fragment Shader Compling failure %s\n", infoLog); 
    exit(EXIT_FAILURE); 
  }

  iceCreamShader.ShaderProgram = glCreateProgram(); 
  glAttachShader(iceCreamShader.ShaderProgram, iceCreamShader.vertexShader ); 
  glAttachShader(iceCreamShader.ShaderProgram, iceCreamShader.fragmentShader ); 
  glLinkProgram(iceCreamShader.ShaderProgram);

  glGetProgramiv(iceCreamShader.ShaderProgram , GL_LINK_STATUS, &success);
  if (!success) {
    printf("Shader linking failure %s\n", infoLog); 
    exit(EXIT_FAILURE); 
  }

  glDeleteShader(iceCreamShader.vertexShader); 
  glDeleteShader(iceCreamShader.fragmentShader);

  return iceCreamShader.ShaderProgram ; 
}

unsigned int IceCreamRenderTringle() {

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f 
  };

  
  glGenBuffers(1, &iceCreamRenderBuffer.VBO); 
  glGenBuffers(1, &iceCreamRenderBuffer.EBO); 
  glGenVertexArrays(1, &iceCreamRenderBuffer.VAO);
 
  /* requred by core OPEN GL */
  glBindVertexArray(iceCreamRenderBuffer.VAO);

  glBindBuffer(GL_ARRAY_BUFFER, iceCreamRenderBuffer.VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iceCreamRenderBuffer.EBO);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);  
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); 
  glEnableVertexAttribArray(1);  
 
  return iceCreamRenderBuffer.VAO;
}

int main() {

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  if (!glfwInit()) {
      printf("GLFW initialization failed!\n");
      return -1;
  }
  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL); 

  if (window == NULL) glfwTerminate();
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      printf("Failed to initialize GLAD");
      return -1;
  }

  // ------------------------------------
  /*unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); 
  glCompileShader(vertexShader); 

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); 
  glCompileShader(fragmentShader); 

  unsigned int shaderProgram = glCreateProgram(); 
  glAttachShader(shaderProgram, vertexShader); 
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram); 
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices[] = {
       0.5f,  0.5f, 0.0f,  // top right
       0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f,  0.5f, 0.0f   // top left 
  };
  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,   // first triangle
      1, 2, 3,    // second triangle
  };  
  unsigned int VBO; 
  unsigned int VAO;  
  unsigned int EBO;  

  glGenVertexArrays(1, &VAO); 
  glGenBuffers(1, &VBO); 
  glGenBuffers(1, &EBO);
  

   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); 
  glEnableVertexAttribArray(0); 

 // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  //glBindBuffer(GL_ARRAY_BUFFER, 0); 

   // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  glBindVertexArray(0); 
 */ 
  iceCreamShader.ShaderProgram = CompilingShader(); 
  iceCreamRenderer.QuadMesh = IceCreamRenderTringle(); 

  while(!glfwWindowShouldClose(window)) {
    processInput(window);
  
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(iceCreamShader.ShaderProgram); 
    glBindVertexArray(iceCreamRenderer.QuadMesh);
    glDrawArrays(GL_TRIANGLES, 0, 3); 
    /* shape position vec3 */
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

    glfwSwapBuffers(window);
    glfwPollEvents();    
}
  
  glDeleteVertexArrays(1, &iceCreamRenderer.QuadMesh);
  glDeleteBuffers(1, &iceCreamRenderBuffer.VBO);
  glDeleteBuffers(1, &iceCreamRenderBuffer.EBO);
  glDeleteProgram(iceCreamShader.ShaderProgram);
  glfwTerminate();
  return 0; 

}

