#pragma once

#include "sdkconfig.h"

// system includes
#include <array>
#include <string>

// esp-idf includes
#include <esp_sntp.h>

// 3rdparty lib includes
#include <configmanager.h>
#include <configwrapper.h>
#include <espchrono.h>

// local includes
#include "configs_helper.h"

using namespace espconfig;
using namespace std::chrono_literals;

namespace config
{
constexpr const char *const TAG = "config";
} // namespace config

std::string defaultHostname();

class ConfigContainer;

extern ConfigManager<ConfigContainer> configs;

// clang-format off
class ConfigContainer
{
    using mac_t = wifi_stack::mac_t;
    using minutes32 = espchrono::minutes32;
    using milliseconds32 = espchrono::milliseconds32;
    using DayLightSavingMode = espchrono::DayLightSavingMode;
public:
    // ======== DISPLAY ======== //
    struct
    {
        struct : ConfigWrapper<bool>
        {
            bool allowReset() const override { return true; }
            const char *nvsName() const override { return "displayRotated"; }
            value_t defaultValue() const override { return false; }
            ConfigConstraintReturnType checkValue(value_t value) const override { return {}; }
        } rotated;
    } display;

    // ======== TIME ======== //
    struct
    {
        struct : ConfigWrapper<minutes32>
        {
            bool allowReset() const final { return true; }
            const char *nvsName() const final { return "timeOffset"; }
            value_t defaultValue() const final { return 1h; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return {}; }
        } offset;
        struct : ConfigWrapper<DayLightSavingMode>
        {
            bool allowReset() const final { return true; }
            const char *nvsName() const final { return "daylightSaving"; }
            value_t defaultValue() const final { return DayLightSavingMode::EuropeanSummerTime; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return {}; }
        } dst;
        struct : ConfigWrapper<std::string>
        {
            bool allowReset() const final { return false; }
            const char *nvsName() const final { return "timeServer"; }
            std::string defaultValue() const final { return "europe.pool.ntp.org"; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return StringMaxSize<64>(value); }
        } ntpServer;
        struct : ConfigWrapper<sntp_sync_mode_t>
        {
            bool allowReset() const final { return false; }
            const char *nvsName() const final { return "timeSyncMode"; }
            value_t defaultValue() const final { return SNTP_SYNC_MODE_IMMED; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return {}; }
        } ntpSyncMode;
        struct : ConfigWrapper<milliseconds32>
        {
            bool allowReset() const final { return false; }
            const char *nvsName() const final { return "tSyncInterval"; }
            value_t defaultValue() const final { return milliseconds32{CONFIG_LWIP_SNTP_UPDATE_DELAY}; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return MinTimeSyncInterval(value); }
        } ntpSyncInterval;
        // sunrise lat/lon for vienna
        struct : ConfigWrapper<float>
        {
            bool allowReset() const final { return true; }
            const char *nvsName() const final { return "sunriseLat"; }
            value_t defaultValue() const final { return 48.2082; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return {}; }
        } sunriseLatitude;
        struct : ConfigWrapper<float>
        {
            bool allowReset() const final { return true; }
            const char *nvsName() const final { return "sunriseLong"; }
            value_t defaultValue() const final { return 16.3738; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return {}; }
        } sunriseLongitude;
    } time;

    // ======== NETWORK ======== //
    struct
    {
        struct : ConfigWrapper<std::string>
        {
            bool allowReset() const final { return true; }
            const char* nvsName() const final { return "hostname"; }
            std::string defaultValue() const final { return defaultHostname(); }
            ConfigConstraintReturnType checkValue(value_t value) const final { return StringMaxSize<32>(value); }
        } hostname;

        struct : ConfigWrapper<bool>
        {
            bool allowReset() const override { return true; }
            const char *nvsName() const override { return "staEnabled"; }
            value_t defaultValue() const override { return false; }
            ConfigConstraintReturnType checkValue(value_t value) const override { return {}; }
        } staEnabled;

        struct : ConfigWrapper<bool>
        {
            bool allowReset() const override { return true; }
            const char *nvsName() const override { return "apEnabled"; }
            value_t defaultValue() const override { return false; }
            ConfigConstraintReturnType checkValue(value_t value) const override { return {}; }
        } apEnabled;

        struct : ConfigWrapper<std::string>
        {
            bool allowReset() const final { return true; }
            const char *nvsName() const final { return "apName"; }
            std::string defaultValue() const final { return defaultHostname(); }
            ConfigConstraintReturnType checkValue(value_t value) const final { return StringMinMaxSize<4, 32>(value); }
        } apName;

        struct : ConfigWrapper<std::string>
        {
            bool allowReset() const final { return true; }
            const char *nvsName() const final { return "wifiApKey"; }
            std::string defaultValue() const final { return "Passwort_123"; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return StringOr<StringEmpty, StringMinMaxSize<8, 64>>(value); }
        } apKey;

        struct : ConfigWrapper<uint8_t>
        {
            bool allowReset() const final { return true; }
            const char *nvsName() const final { return "wifiApChannel"; }
            value_t defaultValue() const final { return 1; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return MinMaxValue<uint8_t, 1, 14>(value); }
        } apChannel;

        struct : ConfigWrapper<wifi_stack::ip_address_t>
        {
            bool allowReset() const final { return true; }
            const char *nvsName() const final { return "wifiApIp"; }
            value_t defaultValue() const final { return wifi_stack::ip_address_t{10, 0, 0, 1}; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return {}; }
        } apIp;

        struct : ConfigWrapper<wifi_stack::ip_address_t>
        {
            bool allowReset() const final { return true; }
            const char *nvsName() const final { return "wifiApMask"; }
            value_t defaultValue() const final { return wifi_stack::ip_address_t{255, 255, 255, 0}; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return {}; }
        } apMask;

        struct : ConfigWrapper<wifi_auth_mode_t>
        {
            bool allowReset() const final { return true; }
            const char *nvsName() const final { return "wifiApAuthmode"; }
            value_t defaultValue() const final { return WIFI_AUTH_WPA_WPA2_PSK; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return {}; }
        } apAuthmode;

        struct : ConfigWrapper<bool>
        {
            bool allowReset() const final { return true; }
            const char* nvsName() const final { return "apWhenNoWiFi"; }
            value_t defaultValue() const final { return false; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return {}; }
        } apOnlyWhenNotConnected;

        struct : ConfigWrapper<std::optional<mac_t>>
        {
            bool allowReset() const final { return false; }
            const char *nvsName() const final { return "baseMacAddrOver"; }
            value_t defaultValue() const final { return std::nullopt; }
            ConfigConstraintReturnType checkValue(value_t value) const final { return {}; }
        } baseMacAddressOverride;

        std::array<WiFiConfig, CONFIG_WIFI_STA_CONFIG_COUNT> wifis {
            WiFiConfig{"wifi_ssid0", "wifi_key0", "wifi_usestatic0", "wifi_static_ip0", "wifi_stati_sub0", "wifi_stat_gate0", "wifi_usestadns0", "wifi_stat_dnsA0", "wifi_stat_dnsB0", "wifi_stat_dnsC0"},
            WiFiConfig{"wifi_ssid1", "wifi_key1", "wifi_usestatic1", "wifi_static_ip1", "wifi_stati_sub1", "wifi_stat_gate1", "wifi_usestadns1", "wifi_stat_dnsA1", "wifi_stat_dnsB1", "wifi_stat_dnsC1"},
            WiFiConfig{"wifi_ssid2", "wifi_key2", "wifi_usestatic2", "wifi_static_ip2", "wifi_stati_sub2", "wifi_stat_gate2", "wifi_usestadns2", "wifi_stat_dnsA2", "wifi_stat_dnsB2", "wifi_stat_dnsC2"},
            WiFiConfig{"wifi_ssid3", "wifi_key3", "wifi_usestatic3", "wifi_static_ip3", "wifi_stati_sub3", "wifi_stat_gate3", "wifi_usestadns3", "wifi_stat_dnsA3", "wifi_stat_dnsB3", "wifi_stat_dnsC3"},
            WiFiConfig{"wifi_ssid4", "wifi_key4", "wifi_usestatic4", "wifi_static_ip4", "wifi_stati_sub4", "wifi_stat_gate4", "wifi_usestadns4", "wifi_stat_dnsA4", "wifi_stat_dnsB4", "wifi_stat_dnsC4"},
        };
    } network;

    // clang-format on
    template <typename T> void callForEveryConfig(T &&callable)
    {
#define REGISTER_CONFIG(name)                                                                                          \
    if (callable(name))                                                                                                \
        return;

        // DISPLAY
        REGISTER_CONFIG(display.rotated);

        // TIME
        REGISTER_CONFIG(time.offset);
        REGISTER_CONFIG(time.dst);
        REGISTER_CONFIG(time.ntpServer);
        REGISTER_CONFIG(time.ntpSyncMode);
        REGISTER_CONFIG(time.ntpSyncInterval);
        REGISTER_CONFIG(time.sunriseLatitude);
        REGISTER_CONFIG(time.sunriseLongitude);

        // NETWORK
        REGISTER_CONFIG(network.hostname);
        REGISTER_CONFIG(network.staEnabled);

        REGISTER_CONFIG(network.apEnabled);
        REGISTER_CONFIG(network.apName);
        REGISTER_CONFIG(network.apKey);
        REGISTER_CONFIG(network.apChannel);
        REGISTER_CONFIG(network.apIp);
        REGISTER_CONFIG(network.apMask);
        REGISTER_CONFIG(network.apAuthmode);
        REGISTER_CONFIG(network.apOnlyWhenNotConnected);

        REGISTER_CONFIG(network.baseMacAddressOverride);

        for (auto &cfg : network.wifis)
        {
            REGISTER_CONFIG(cfg.ssid);
            REGISTER_CONFIG(cfg.key);
            REGISTER_CONFIG(cfg.useStaticIp);
            REGISTER_CONFIG(cfg.staticIp);
            REGISTER_CONFIG(cfg.staticSubnet);
            REGISTER_CONFIG(cfg.staticGateway);
            REGISTER_CONFIG(cfg.useStaticDns);
            REGISTER_CONFIG(cfg.staticDns0);
            REGISTER_CONFIG(cfg.staticDns1);
            REGISTER_CONFIG(cfg.staticDns2);
        }

#undef REGISTER_CONFIG
    }
};
