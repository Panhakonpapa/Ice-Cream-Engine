#include "time.h"
#include "../iceCreamGlobal.h"
#include <SDL2/SDL_timer.h>

void IceCreamInitTime(u32 frame_rate) {
    engine.time.frame_rate = frame_rate; 
    engine.time.frame_delay = 1000.f / frame_rate; 
}

void IceCreamUpdate(void) {

    engine.time.now = (f32)SDL_GetTicks();  
    engine.time.delta = (engine.time.now - engine.time.last) / 1000.f; 
    engine.time.last = engine.time.now; 
    engine.time.frame_count++; 

    if (engine.time.now  - engine.time.frame_last >= 1000.f) {
        engine.time.frame_rate = engine.time.frame_count; 
        engine.time.frame_count = 0; 
        engine.time.frame_last = engine.time.now;
    }
}

void IceCreamUpdateLate(void) {

    engine.time.frame_time = (f32)SDL_GetTicks() - engine.time.now; 

    if (engine.time.frame_delay > engine.time.frame_time) {
        SDL_Delay(engine.time.frame_delay - engine.time.frame_time); 
    }
} 
