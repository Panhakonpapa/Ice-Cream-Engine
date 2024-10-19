#include <glad/glad.h>
#include <stdio.h>

#include "utils.h"
#include "io.h"
#include "internalRender.h"

u32 IceCreamCompileShader(const char *pathVertex, const char *pathFrag) {
    int success;
    char log[512];

    File VertexFile = IoiceCreamReadFile(pathVertex); 
    if (!VertexFile.inValid) {
        printf("Error reading shader: %s\n", pathVertex);
        exit(1); 
    } 

    u32 shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader_vertex, 1, (const char *const *)&VertexFile, NULL);
    glCompileShader(shader_vertex);
    glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader_vertex, 512, NULL, log);
                printf("Error compiling vertex shader. %s\n", log);
                exit(1); 
    }

    File FragFile = IoiceCreamReadFile(pathFrag); 
    if (!FragFile.inValid) {
        printf("Error reading shader: %s\n", pathFrag);
        exit(1); 
    } 
    u32 shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_fragment, 1, (const char *const *)&FragFile, NULL);
    glCompileShader(shader_fragment);
    glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
            glGetShaderInfoLog(shader_fragment, 512, NULL, log);
            printf("Error compiling fragment shader. %s\n", log);
            exit(1); 
    }
    u32 shader = glCreateProgram();
	glAttachShader(shader, shader_vertex);
	glAttachShader(shader, shader_fragment);
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, log);
		printf("Error linking shader. %s\n", log);
	}

    free(VertexFile.data);
    free(FragFile.data);
    
    return shader; 
}
