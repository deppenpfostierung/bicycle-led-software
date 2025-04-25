#pragma once

namespace bicycle::hardware
{

extern bool portexpander_initialized;

void init_portexpander();

void update_portexpander();

} // namespace bicycle::hardware