#pragma once

// system includes
#include <atomic>

namespace bicycle::hardware
{

extern const std::atomic<bool> &i2c_initialized;

void init_i2c();
void update_i2c();

} // namespace bicycle::hardware