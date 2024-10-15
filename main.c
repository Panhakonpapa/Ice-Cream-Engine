#include "core/OpenGL.h"
#include "core/IceCreamRender.h"
#include "core/imageLoader.h"
#include <GLFW/glfw3.h>
#include <complex.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_ENTITY 10



void InputHandler(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    printf("Keyprss is W\n");
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    printf("Keyprss is A\n");
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    printf("Keyprss is D\n");
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    printf("Keyprss is S\n");
  }
}
int main() {

  /* game initlaization */
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
  


  while (!glfwWindowShouldClose(window)) {
    
    /*inputProcess(); */
    InputHandler(window); 

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  glfwTerminate(); 

  /* game engine close */
}


