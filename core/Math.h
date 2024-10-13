#ifndef CORE_VEC_H
#define CORE_VEC_H

typedef struct {
  float x; 
  float y; 
  float z; 
} iceCreamVec3; 

typedef struct {
  float x; 
  float y; 
  float z; 
  float w; 
} iceCreamVec4; 

typedef struct {
  float m[4][4]; 
} mat4;

mat4 mat4_identity(); 
mat4 iceCreamMat4Translate(float x, float y, float z); 
iceCreamVec4 vec4(float x, float y, float z);
iceCreamVec3 vec3_add(iceCreamVec3 a, iceCreamVec3 b); 
iceCreamVec3 vec3_subtract(iceCreamVec3 a, iceCreamVec3 b); 
iceCreamVec3 vec3_scaler(iceCreamVec3 v, float scale); 
iceCreamVec3 vec3_normalize(iceCreamVec3 v); 
iceCreamVec3 vec3_cross(iceCreamVec3 a, iceCreamVec3 b);
float iceCreamFindMagnitude(iceCreamVec3 v); 
float vec3_dot(iceCreamVec3 a, iceCreamVec3 b);


#endif // CORE VECTOR MATH

