#pragma once

// system includes
#include <string_view>

namespace bicycle::screen
{

void init();

void reinit_tft();

void update();

void setBootMessage(std::string_view message);

} // namespace bicycle::screen
