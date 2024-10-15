#include "Math.h" 

mat4 mat4_identity() {
    mat4 m; 
    for (int i = 0; i < 16; i++) {
        m.m[i] = (i % 5 == 0) ? 1.0f : 0.0f; 
    }
    return m;
}

mat4 trans(float x, float y, float z) {
    mat4 m = mat4_identity(); 

    m.m[12] = x; // Translation on x
    m.m[13] = y; // Translation on y
    m.m[14] = z; // Translation on z
    //
    return m;
} 

mat4 scale(float scaleX, float scaleY, float scaleZ) {

    mat4 m = mat4_identity();
    m.m[0] = scaleX; // Scale x
    m.m[5] = scaleY; // Scale y
    m.m[10] = scaleZ; // Scale z
    
    return m;
}

mat4 multiply(mat4 a, mat4 b) {
    mat4 results = {0}; 

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            results.m[i * 4 * j] = 
                a.m[i * 4 * 0] * b.m[0 * 4 * j]+  
                a.m[i * 4 * 1] * b.m[1 * 4 * j]+
                a.m[i * 4 * 2] * b.m[2 * 4 * j]+
                a.m[i * 4 * 3] * b.m[3 * 4 * j]; 
        }
    }
    return results; 
}

mat4 mat4_transformation(float translateX, float translateY, float translateZ, float scaleX, float scaleY, float scaleZ) {

    mat4 scaling = scale(scaleX, scaleY, scaleZ);
    mat4 transalation = trans(translateX, translateY, translateZ); 

    return multiply(transalation, scaling);
}
