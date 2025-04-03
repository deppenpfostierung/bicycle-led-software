#pragma once

// system includes
#include <cstdint>

// 3rdparty lib includes
#include <cpptypesafeenum.h>

#define ButtonActionValues(x) x(Unused) x(LeftBlinker) x(RightBlinker) x(ToggleHazards)
DECLARE_TYPESAFE_ENUM(ButtonAction, : uint8_t, ButtonActionValues)