#pragma once

// 3rdparty lib includes
#include <configconstraints_base.h>
#include <configconstraints_espchrono.h>
#include <configwrapper.h>
#include <espwifistack.h>

using namespace std::chrono_literals;
using namespace espconfig;

enum class AllowReset
{
    NoReset,
    DoReset,
};
constexpr auto NoReset = AllowReset::NoReset;
constexpr auto DoReset = AllowReset::DoReset;

template <typename T> class ConfigWrapperDynamicKey : public ConfigWrapper<T>
{
    CPP_DISABLE_COPY_MOVE(ConfigWrapperDynamicKey);
    using Base = ConfigWrapper<T>;

public:
    using value_t = typename Base::value_t;
    using ConstraintCallback = typename Base::ConstraintCallback;

    explicit ConfigWrapperDynamicKey(const char *nvsKey)
        : m_nvsKey { nvsKey }
    {
    }

    const char *nvsName() const override
    {
        return m_nvsKey;
    }

private:
    const char *m_nvsKey;
};

class WiFiConfig
{
    using ip_address_t = wifi_stack::ip_address_t;

public:
    WiFiConfig(const char *ssidNvsKey, const char *keyNvsKey, const char *useStaticIpKey, const char *staticIpKey,
               const char *staticSubnetKey, const char *staticGatewayKey, const char *useStaticDnsKey,
               const char *staticDns0Key, const char *staticDns1Key, const char *staticDns2Key)
        : ssid { ssidNvsKey }
        , key { keyNvsKey }
        , useStaticIp { useStaticIpKey }
        , staticIp { staticIpKey }
        , staticSubnet { staticSubnetKey }
        , staticGateway { staticGatewayKey }
        , useStaticDns { useStaticDnsKey }
        , staticDns0 { staticDns0Key }
        , staticDns1 { staticDns1Key }
        , staticDns2 { staticDns2Key }
    {
    }

    struct : ConfigWrapperDynamicKey<std::string>
    {
        using ConfigWrapperDynamicKey<std::string>::ConfigWrapperDynamicKey;

        bool allowReset() const final
        {
            return true;
        }
        std::string defaultValue() const final
        {
            return {};
        }
        ConfigConstraintReturnType checkValue(value_t value) const final
        {
            return StringMaxSize<32>(value);
        }
    } ssid;
    struct : ConfigWrapperDynamicKey<std::string>
    {
        using ConfigWrapperDynamicKey<std::string>::ConfigWrapperDynamicKey;

        bool allowReset() const final
        {
            return true;
        }
        std::string defaultValue() const final
        {
            return {};
        }
        ConfigConstraintReturnType checkValue(value_t value) const final
        {
            return StringOr<StringEmpty, StringMinMaxSize<8, 64>>(value);
        }
    } key;
    struct : ConfigWrapperDynamicKey<bool>
    {
        using ConfigWrapperDynamicKey<bool>::ConfigWrapperDynamicKey;

        bool allowReset() const final
        {
            return true;
        }
        value_t defaultValue() const final
        {
            return false;
        }
        ConfigConstraintReturnType checkValue(value_t value) const final
        {
            return {};
        }
    } useStaticIp;
    struct : ConfigWrapperDynamicKey<ip_address_t>
    {
        using ConfigWrapperDynamicKey<ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const final
        {
            return true;
        }
        value_t defaultValue() const final
        {
            return {};
        }
        ConfigConstraintReturnType checkValue(value_t value) const final
        {
            return {};
        }
    } staticIp;
    struct : ConfigWrapperDynamicKey<ip_address_t>
    {
        using ConfigWrapperDynamicKey<ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const final
        {
            return true;
        }
        value_t defaultValue() const final
        {
            return {};
        }
        ConfigConstraintReturnType checkValue(value_t value) const final
        {
            return {};
        }
    } staticSubnet;
    struct : ConfigWrapperDynamicKey<ip_address_t>
    {
        using ConfigWrapperDynamicKey<ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const final
        {
            return true;
        }
        value_t defaultValue() const final
        {
            return {};
        }
        ConfigConstraintReturnType checkValue(value_t value) const final
        {
            return {};
        }
    } staticGateway;
    struct : ConfigWrapperDynamicKey<bool>
    {
        using ConfigWrapperDynamicKey<bool>::ConfigWrapperDynamicKey;

        bool allowReset() const final
        {
            return true;
        }
        value_t defaultValue() const final
        {
            return false;
        }
        ConfigConstraintReturnType checkValue(value_t value) const final
        {
            return {};
        }
    } useStaticDns;
    struct : ConfigWrapperDynamicKey<ip_address_t>
    {
        using ConfigWrapperDynamicKey<ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const final
        {
            return true;
        }
        value_t defaultValue() const final
        {
            return {};
        }
        ConfigConstraintReturnType checkValue(value_t value) const final
        {
            return {};
        }
    } staticDns0;
    struct : ConfigWrapperDynamicKey<ip_address_t>
    {
        using ConfigWrapperDynamicKey<ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const final
        {
            return true;
        }
        value_t defaultValue() const final
        {
            return {};
        }
        ConfigConstraintReturnType checkValue(value_t value) const final
        {
            return {};
        }
    } staticDns1;
    struct : ConfigWrapperDynamicKey<ip_address_t>
    {
        using ConfigWrapperDynamicKey<ip_address_t>::ConfigWrapperDynamicKey;

        bool allowReset() const final
        {
            return true;
        }
        value_t defaultValue() const final
        {
            return {};
        }
        ConfigConstraintReturnType checkValue(value_t value) const final
        {
            return {};
        }
    } staticDns2;
};
