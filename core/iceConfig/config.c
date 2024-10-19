
#include "config.h"
#include "../iceCreamGlobal.h"
#include "../io.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <stdio.h>
#include <string.h>

static const char *CONFIG_DEFAULT =
	"[controls]\n"
	"left = A\n"
	"right = D\n"
	"up = W\n"
	"down = S\n"
	"escape = Escape\n"
	"\n";

static char tempBuffer[20] = {0}; 

static char* getKeys(const char* buffer, const char* key) {
    
    char* line = strstr(buffer, key); 
    if (!line) {
	printf("Can't find the keyvalue %s\n", key); 
    }
    usize len = strlen(line); 

    /* get the end pointer */
    char* end = len + line; 
    char* curr = line; 
    char* tmp_buffer = &tempBuffer[0];  

    while (*curr != '=' && curr != end) 
	curr++; 
    
    curr++; 

    while (*curr == ' ') 
	curr++; 

    while (*curr != '\n' && *curr != 0 && curr != end) 
	*tmp_buffer++ = *curr++; 

    *(tmp_buffer + 1) = 0;  
    
    return tempBuffer; 
}

static void loadKeyControl(const char* buffer) {

    iceConfigkeybind(INPUT_KEY_LEFT, getKeys(buffer, "left")); 
    iceConfigkeybind(INPUT_KEY_RIGHT, getKeys(buffer,"right")); 
    iceConfigkeybind(INPUT_KEY_UP, getKeys(buffer,"up")); 
    iceConfigkeybind(INPUT_KEY_DOWN, getKeys(buffer,"down")); 
    iceConfigkeybind(INPUT_KEY_ESCAPE, getKeys(buffer,"escape")); 
}

static int loadConf(void) {

    File iceConf = IoiceCreamReadFile("/home/panha/Ice-Cream-Engine/core/iceConfig/config.ice"); 

    if (!iceConf.inValid) {
	printf("load configfie failure \n"); 
	return 1; 
	//exit(1);
    }

    loadKeyControl(iceConf.data); 
    
    free(iceConf.data); 

    return 0; 
}

void iceInitConfig(void) {

    loadConf(); 
    /*IoiceCreamWriteFile((void *)CONFIG_DEFAULT, strlen(CONFIG_DEFAULT), "/home/panha/Ice-Cream-Engine/core/iceConfig/config.ice"); */

}

void iceConfigkeybind(Input_key key, const char *keyName) {

    SDL_Scancode scan_code = SDL_GetScancodeFromName(keyName); 
    if (scan_code ==  SDL_SCANCODE_UNKNOWN) {
        printf("Unknwon keyBinding -> %s\n", keyName); 
    }
    engine.keyConf.keyBinding[key] = scan_code; 
    
}
