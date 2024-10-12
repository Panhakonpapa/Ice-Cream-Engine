#ifndef CORE_H
#define CORE_H

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

/*GraphicBuffer iceCreamRenderBuffer; 
GraphicShader iceCreamShader;  
Graphic iceCreamRenderer; 
*/

char* loadShaderFile(char* filePath); 
unsigned int IceCreamCompileShader(GraphicShader* iceCreamShader, char* VertexShaderProgram, char* FragmentShaderProgram);  
unsigned int IceCreamRenderTringle(GraphicBuffer* iceCreamRenderBuffer); 

#endif 
