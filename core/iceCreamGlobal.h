#pragma once

#include "iceCreamRender.h"
#include "input.h"
#include "time/time.h"
#include "iceConfig/config.h"

typedef struct {
	IceCreamKeyConf keyConf;
	IceCreamRenderer render; 
	IceCreamTimer time; 
	keyboard_input keyInput;
} Engine;

extern Engine engine; 

