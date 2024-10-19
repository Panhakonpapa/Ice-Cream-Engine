#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <glad/glad.h> 
#include "core/iceConfig/config.h"
#include "core/iceCreamGlobal.h"
#include "core/iceCreamRender.h"
//#include "core/iceConfig/config.h"
#include "core/input.h"
#include "core/time/time.h" 

static vec2 pos;
static bool winShoudQuit = false; 

static void input_handle(void) {
  if (engine.keyInput.left == KEY_PRESSED || engine.keyInput.left == KEY_HELD) {
    pos[0] -= 500 * engine.time.delta; 
  }

  if (engine.keyInput.right == KEY_PRESSED || engine.keyInput.right == KEY_HELD) {
    pos[0] += 500 * engine.time.delta; 
  }
  
  if (engine.keyInput.up == KEY_PRESSED || engine.keyInput.up == KEY_HELD) {
    pos[1] += 500 * engine.time.delta; 
  }

  if (engine.keyInput.down == KEY_PRESSED || engine.keyInput.down == KEY_HELD) {
    pos[1] -= 500 * engine.time.delta; 
  }

  if (engine.keyInput.escape == KEY_PRESSED || engine.keyInput.escape == KEY_HELD) {
    winShoudQuit = true; 
  }
}

int main() {

  iceInitConfig(); 
  IceCreamInitTime(60); 
  IceCreamGraphicInit();

  pos[0] = engine.render.with  * 0.5; 
  pos[1] = engine.render.height * 0.5; 

  printf("Staring program \n"); 

  while (!winShoudQuit) {

    IceCreamUpdate(); 
  
    SDL_Event event; 
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: 
          winShoudQuit = true; 
          break; 
      
      }
    }
     
    iceCreamkeyboardInput(); 
    input_handle(); 
    
    IceCreamRenderBegin(); 

    IceCreamRenderQuad(pos, (vec2){50, 50}, (vec4){0, 1, 0, 1});

    IceCreamRenderEnd(); 

    IceCreamUpdateLate(); 
  }


  return 0; 
}
