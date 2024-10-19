#pragma once 

#include "../input.h"
#include "../utils.h"


typedef struct confing {
	u8 keyBinding[5];	
} IceCreamKeyConf; 

void iceInitConfig(void); 
void iceConfigkeybind(Input_key key, const char* keyName); 

