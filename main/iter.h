#pragma once

// local includes
#include "configs.h"

template <typename T> void forEveryButton(T &&callback)
{
#define REGISTER_BUTTON(x) \
    if (callback(x))       \
        return;

    REGISTER_BUTTON(&configs.dpad.mappingUp)
    REGISTER_BUTTON(&configs.dpad.mappingDown)
    REGISTER_BUTTON(&configs.dpad.mappingLeft)
    REGISTER_BUTTON(&configs.dpad.mappingRight)

#undef REGISTER_BUTTON
}

template <typename T> void forEveryCustomButton(T &&callback)
{
#define REGISTER_CUSTOM_BUTTON(x) \
    if (callback(x))              \
        return;

    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom1);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom2);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom3);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom4);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom5);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom6);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom7);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom8);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom9);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom10);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom11);
    REGISTER_CUSTOM_BUTTON(&configs.dpad.mappingCustom12);

#undef REGISTER_CUSTOM_BUTTON
}
