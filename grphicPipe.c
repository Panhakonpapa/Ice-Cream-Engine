#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>

void error(unsigned int err) {
  int  success;
  char infoLog[512];
  glGetShaderiv(err, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(err, 512, NULL, infoLog);
    printf("Shader Compilation faliure %s\n", infoLog); 
  }
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

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
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
 
  while(!glfwWindowShouldClose(window)) {
    processInput(window);
  
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram); 
    glBindVertexArray(VAO);
    /* shape position vec3 */
    //glDrawArrays(GL_TRIANGLES, 0, 3); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

    glfwSwapBuffers(window);
    glfwPollEvents();    
}
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0; 

}

