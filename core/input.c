#include "input.h"
#include "utils.h" 
#include "iceCreamGlobal.h"
#include <SDL2/SDL.h>

static void updateKeys(u8 current_state, key_State* keyState) {
    if (current_state) {

        if (*keyState > 0) { 

            *keyState = KEY_HELD; 
        }
        else {
            *keyState = KEY_PRESSED; 
        }
    } 
    else {
        *keyState = KEY_UNPRESSED; 
    }
}
void iceCreamkeyboardInput(void) {

    const u8* keyboard_state = SDL_GetKeyboardState(NULL); 
    //printf("Processing input ...\n"); 
    updateKeys(keyboard_state[engine.keyConf.keyBinding[INPUT_KEY_UP]], &engine.keyInput.up); 
    updateKeys(keyboard_state[engine.keyConf.keyBinding[INPUT_KEY_LEFT]], &engine.keyInput.left); 
    updateKeys(keyboard_state[engine.keyConf.keyBinding[INPUT_KEY_RIGHT]], &engine.keyInput.right); 
    updateKeys(keyboard_state[engine.keyConf.keyBinding[INPUT_KEY_DOWN]], &engine.keyInput.down); 
    updateKeys(keyboard_state[engine.keyConf.keyBinding[INPUT_KEY_ESCAPE]], &engine.keyInput.escape); 

}



