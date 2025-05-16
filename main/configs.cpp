#include "configs.h"

// system includes
#include <format>
#include <string>

// 3rdparty lib includes
#include <configmanager_priv.h>
#include <espwifistack.h>

std::string defaultHostname()
{
    if (const auto result = wifi_stack::get_default_mac_addr())
        return std::format("{}_{:02x}{:02x}{:02x}", APP_NAME, result->at(3), result->at(4), result->at(5));
    else
        ESP_LOGE(TAG, "get_default_mac_addr() failed: %.*s", result.error().size(), result.error().data());
    return APP_NAME;
}

ConfigManager<ConfigContainer> configs;

INSTANTIATE_CONFIGMANAGER_TEMPLATES(ConfigContainer)
