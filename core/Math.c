#include "Math.h" 


iceCreamVec3 vec3_add(iceCreamVec3 a, iceCreamVec3 b) {

    iceCreamVec3 results = { 
        results.x = a.x + a.x, 
        results.y = a.y + a.y, 
        results.z = a.z + a.z
    };

    return results; 
} 

iceCreamVec3 vec3_subtract(iceCreamVec3 a, iceCreamVec3 b) {

    iceCreamVec3 results = { 
        results.x = a.x - a.x, 
        results.y = a.y - a.y, 
        results.z = a.z - a.z
    };

    return results;
}

iceCreamVec3 vec3_scaler(iceCreamVec3 v, float scale) {

    iceCreamVec3 results = { 
        results.x = v.x * scale, 
        results.y = v.y * scale, 
        results.z = v.z * scale 
    };
    
    return results;

}

mat4 mat4_identity() {
    mat4 result = {{{0}}};
    for (int i = 0; i < 4; i++) {
        result.m[i][i] = 1.0f;
    }
    return result;
}

mat4 iceCreamMat4Translate(float x, float y, float z) {
    mat4 results = mat4_identity();
    
    results.m[3][0] = x; 
    results.m[3][1] = y; 
    results.m[3][2] = z; 

    return results; 
}

iceCreamVec4 vec4(float x, float y, float z) {

    return (iceCreamVec4){x, y, z, 1.0f};
}

