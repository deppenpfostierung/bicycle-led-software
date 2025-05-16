#pragma once

// system includes
#include <cstdint>

// 3rdparty lib includes
#include <cpptypesafeenum.h>

#define ButtonActionValues(x) \
    x(Unused) x(Left_Blinker) x(Right_Blinker) x(Toggle_Hazards) x(Toggle_Highbeam) x(Toggle_Lowbeam) x(Rear_Fog_Light)
DECLARE_TYPESAFE_ENUM(ButtonAction, : uint8_t, ButtonActionValues)
