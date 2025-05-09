#pragma once

// 3rdparty lib includes
#include <espchrono.h>

namespace bicycle::debug
{

void init();

void update();

extern enum MemoryDebugMode
{
    Off,
    Fast,
    Slow
} memoryDebugMode;

extern espchrono::millis_clock::time_point lastMemoryDebugMessage;

} // namespace bicycle::debug