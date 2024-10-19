#pragma once

#include <SDL2/SDL.h>
#include "../utils.h"
typedef struct {
	f32 delta; 
	f32 now; 
	f32 last; 

	f32 frame_last; 
	f32 frame_delay; 
	f32 frame_time; 

	u32 frame_rate; 
	u32 frame_count; 

} IceCreamTimer; 

void IceCreamInitTime(u32 frame_rate); 
void IceCreamUpdateLate(void); 
void IceCreamUpdate(void);
