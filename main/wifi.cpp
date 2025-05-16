#include "wifi.h"

constexpr const char *const TAG = "WIFI";

// system includes
#include <expected>
#include <format>
#include <optional>
#include <string>

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <espwifistack.h>
#include <recursivelockhelper.h>

// local includes
#include "clock.h"
#include "configs.h"
#include "global_lock.h"

namespace bicycle::wifi
{

namespace
{

wifi_stack::config createConfig();
std::optional<wifi_stack::sta_config> createStaConfig();
wifi_stack::wifi_entry createWiFiEntry(const WiFiConfig &wiFiConfig);
std::optional<wifi_stack::ap_config> createApConfig();

bool lastStaConnected { false };

} // namespace

void begin()
{
    ESP_LOGI(TAG, "begin");

    wifi_stack::init(createConfig());
}

void update()
{
    espcpputils::RecursiveLockHelper guard { global::global_lock->handle };
    wifi_stack::update(createConfig());

    const bool staConnected = isStaConnected();

    if (staConnected != lastStaConnected)
    {
        lastStaConnected = staConnected;
        if (staConnected)
        {
            ESP_LOGI(TAG, "STA connected");
            espclock::syncNow();
        }
        else
            ESP_LOGI(TAG, "STA disconnected");
    }
}

std::expected<void, std::string> startScan()
{
    const auto &staConfig = createStaConfig();
    if (!staConfig)
        return std::unexpected("WIFI_STA is not enabled");

    if (const auto result = wifi_stack::begin_scan(*staConfig); !result)
        return std::unexpected(std::format("wifi_stack::begin_scan() failed: {}", result.error()));

    return {};
}

bool isStaConnected()
{
    return wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED;
}

bool isApUp()
{
    if (!configs.network.apEnabled.value())
        return false;

    if (configs.network.apOnlyWhenNotConnected.value()
        && wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        return false;

    return true;
}

namespace
{

wifi_stack::config createConfig()
{
    return wifi_stack::config {
        .base_mac_override = configs.network.baseMacAddressOverride.value(),
        .sta = createStaConfig(),
        .ap = createApConfig(),
    };
}

std::optional<wifi_stack::sta_config> createStaConfig()
{
    if (!configs.network.staEnabled.value())
        return std::nullopt;

    return wifi_stack::sta_config {
        .hostname = configs.network.hostname.value(),
        .wifis =
            []() {
                std::array<wifi_stack::wifi_entry, CONFIG_WIFI_STA_CONFIG_COUNT> wifis;
                for (size_t i = 0; i < CONFIG_WIFI_STA_CONFIG_COUNT; ++i)
                    wifis[i] = createWiFiEntry(configs.network.wifis[i]);
                return wifis;
            }(),
        .min_rssi = -90,
        .long_range = false,
    };
}

wifi_stack::wifi_entry createWiFiEntry(const WiFiConfig &wiFiConfig)
{
    std::optional<wifi_stack::static_ip_config> staticIpConfig;

    if (wiFiConfig.useStaticIp.value())
    {
        staticIpConfig = wifi_stack::static_ip_config {
            .ip = wiFiConfig.staticIp.value(),
            .subnet = wiFiConfig.staticSubnet.value(),
            .gateway = wiFiConfig.staticGateway.value(),
        };
    }

    wifi_stack::static_dns_config staticDnsConfig;

    if (wiFiConfig.useStaticDns.value())
    {
        if (wiFiConfig.staticDns0.value().value())
            staticDnsConfig.main = wiFiConfig.staticDns0.value();
        if (wiFiConfig.staticDns1.value().value())
            staticDnsConfig.backup = wiFiConfig.staticDns1.value();
        if (wiFiConfig.staticDns2.value().value())
            staticDnsConfig.fallback = wiFiConfig.staticDns2.value();
    }

    return wifi_stack::wifi_entry {
        .ssid = wiFiConfig.ssid.value(),
        .key = wiFiConfig.key.value(),
        .static_ip = staticIpConfig,
        .static_dns = staticDnsConfig,
    };
}

std::optional<wifi_stack::ap_config> createApConfig()
{
    if (!isApUp())
        return std::nullopt;

    return wifi_stack::ap_config {
        .hostname = configs.network.hostname.value(),
        .ssid = configs.network.apName.value(),
        .key = configs.network.apKey.value(),
        .static_ip = { .ip = configs.network.apIp.value(),
                      .subnet = configs.network.apMask.value(),
                      .gateway = configs.network.apIp.value() },
        .channel = configs.network.apChannel.value(),
        .authmode = configs.network.apAuthmode.value(),
        .ssid_hidden = false,
        .max_connection = 4,
        .beacon_interval = 100,
        .long_range = false
    };
}

} // namespace

} // namespace bicycle::wifi
