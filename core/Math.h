#ifndef MATH_CORE_H
#define MATH_CORE_H

#include <math.h>

typedef struct {
    float m[16];
} mat4;

mat4 mat4_identity(); 
mat4 transform(float x, float y, float z); 
mat4 scale(float scaleX, float scaleY, float scaleZ);  
mat4 multiply(mat4 a, mat4 b); 
mat4 mat4_transformation(float translateX, float translateY, float translateZ, float scaleX, float scaleY, float scaleZ); 

#endif 
