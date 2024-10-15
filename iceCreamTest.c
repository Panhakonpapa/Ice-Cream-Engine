#include "core/IceCreamRender.h"

int main() {
  
  char* filePathShadeer = "/home/panha/Ice-Cream-Engine/core/ShaderBatchFile.glsl"; 
  
  loadShaderFile(filePathShadeer); 

  printInfo(filePathShadeer); 

  return 0; 
}
