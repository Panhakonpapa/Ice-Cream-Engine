#ifndef CORE_RENDER_H
#define CORE_RENDER_H

typedef  struct {

  unsigned int vertexShader; 
  unsigned int fragmentShader;
  unsigned int ShaderProgram; 
  unsigned int texture; 

} GraphicShader;

typedef struct {

  unsigned int VBO; 
  unsigned int VAO; 
  unsigned int EBO;

} GraphicBuffer; 


  
/*GraphicBuffer iceCreamRenderBuffer; 
GraphicShader iceCreamShader;  
Graphic iceCreamRenderer; */

char* loadShaderFile(char* filePath); 
void IceCreamCompileShader(GraphicShader* iceCreamShader, char* VertexShaderProgram, char* FragmentShaderProgram);  
unsigned int IceCreamRenderTringle(GraphicBuffer* iceCreamRenderBuffer); 
unsigned int IceCreamTexture(char* filePath); 
void iceCreamDraw(GraphicShader* Program,GraphicBuffer* iceCreamRenderBuffer);  

#endif 
