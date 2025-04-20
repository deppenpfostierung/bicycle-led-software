#pragma once

// esp-idf includes
#include <esp_err.h>

namespace bicycle::hardware
{

extern bool initialized;

void init_portexpander();

void update_portexpander();

} // namespace bicycle::hardware