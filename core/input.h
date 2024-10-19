#pragma once 

typedef enum key {
	INPUT_KEY_LEFT,  
	INPUT_KEY_RIGHT, 
	INPUT_KEY_UP, 
	INPUT_KEY_DOWN, 
	INPUT_KEY_SHOOT,
	INPUT_KEY_ESCAPE, 
} Input_key; 

typedef enum key_state {
	KEY_PRESSED, 
	KEY_UNPRESSED, 
	KEY_HELD
} key_State; 

typedef struct keyInput {
	key_State left; 
	key_State right; 
	key_State up; 
	key_State down; 
	key_State shoot; 
	key_State escape; 
} keyboard_input; 

void iceCreamkeyboardInput(void); 

