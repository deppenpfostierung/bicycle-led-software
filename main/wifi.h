#pragma once

// system includes
#include <expected>
#include <string>

namespace bicycle::wifi
{

void begin();

void update();

std::expected<void, std::string> startScan();

bool isStaConnected();

bool isApUp();

} // namespace bicycle::wifi
