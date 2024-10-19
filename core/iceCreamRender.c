#include <SDL2/SDL_video.h>
#include <glad/glad.h>

#include "iceCreamGlobal.h"
#include "iceCreamRender.h"
#include "internalRender.h"
#include "linmath.h"

static IceCreamPipeline state = {0}; 

void IceCreamGraphicInit(void) {
    engine.render.with = 800;  
    engine.render.height = 600; 
    engine.render.window = IcreamWindowInit(engine.render.with, engine.render.height);
    IceCreamRenderInitQaud(&state.VBO, &state.EBO, &state.VAO); 
    IceCreamInitShaders(&state); 
    IceCreamInitColorTexture(&state.TextureColor); 

}
void IceCreamRenderBegin(void) {
    glClearColor(0.08, 0.1, 0.1, 1); 
    glClear(GL_COLOR_BUFFER_BIT);  
}
void IceCreamRenderEnd(void) {
    SDL_GL_SwapWindow(engine.render.window); 
}

void IceCreamRenderQuad(vec2 position, vec2 size, vec4 colors) {
    glUseProgram(state.ShaderDefault);

    mat4x4 model;
    mat4x4_identity(model);

    mat4x4_translate(model, position[0], position[1], 0);
    mat4x4_scale_aniso(model, model, size[0], size[1], 1);

    glUniformMatrix4fv(glGetUniformLocation(state.ShaderDefault, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4fv(glad_glGetUniformLocation(state.ShaderDefault, "color"), 1, colors);

    glBindVertexArray(state.VAO);
    
    glBindTexture(GL_TEXTURE_2D, state.TextureColor);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
}
