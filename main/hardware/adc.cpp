#include "adc.h"

#include <sdkconfig.h>

// esp-idf includes
#include <esp_err.h>
#include <esp_log.h>

// system includes
#include <array>

// 3rdparty lib includes
#include <ads111x.h>
#include <taskutils.h>

// local includes
#include "hardware/i2c.h"
#include "helpers.h"

#ifdef CONFIG_BICYCLE_ADC_ADDRESS_GND
#define ADC_ADDRESS ADS111X_ADDR_GND
#elifdef CONFIG_BICYCLE_ADC_ADDRESS_VCC
#define ADC_ADDRESS ADS111X_ADDR_VCC
#elifdef CONFIG_BICYCLE_ADC_ADDRESS_SDA
#define ADC_ADDRESS ADS111X_ADDR_SDA
#elifdef CONFIG_BICYCLE_ADC_ADDRESS_SCL
#define ADC_ADDRESS ADS111X_ADDR_SCL
#endif

#ifndef ADC_ADDRESS
#error "ADC_ADDRESS not defined"
#endif

constexpr const char *const TAG = "HW/ADC";

namespace bicycle::hardware
{

constexpr std::array<ads111x_mux_t, 4> adc_mux_cfgs {
    ADS111X_MUX_0_GND,
    ADS111X_MUX_1_GND,
    ADS111X_MUX_2_GND,
    ADS111X_MUX_3_GND,
};

namespace measure
{

std::atomic<float> _battery_voltage;
const std::atomic<float> &battery_voltage { _battery_voltage };

std::atomic<float> _battery_current;
const std::atomic<float> &battery_current { _battery_current };

std::atomic<float> _aux_adc_0;
const std::atomic<float> &aux_adc_0 { _aux_adc_0 };

std::atomic<float> _aux_adc_1;
const std::atomic<float> &aux_adc_1 { _aux_adc_1 };

} // namespace measure

using namespace measure;

constexpr auto BATTERY_CURRENT_PIN = 0;

constexpr auto AUX_ADC_0_PIN = 1;

constexpr auto BATTERY_VOLTAGE_PIN = 2;

constexpr auto AUX_ADC_1_PIN = 3;

#define BATTERY_VOLTAGE_MULTIPLIER RESISTOR_DIVIDER_MULTIPLIER(8200.f, 2200.f)

#define CC6904_MIN_VOLTAGE 0.33f
#define CC6904_MAX_VOLTAGE 2.97f
#define CC6904_MIN_CURRENT -20.0f
#define CC6904_MAX_CURRENT 20.0f

bool adc_initialized;

namespace
{

std::atomic<std::array<float, 4>> adc_values {};

float adc_gain { 0.0f };

i2c_dev_t i2c_adc;

TaskHandle_t taskHandle { nullptr };

esp_err_t internal_init_adc()
{
    if (!i2c_initialized.load())
    {
        ESP_LOGE(TAG, "I2C not initialized");
        return ESP_FAIL;
    }

    if (adc_initialized)
    {
        ESP_LOGE(TAG, "ADC already initialized");
        return ESP_FAIL;
    }

    adc_gain = ads111x_gain_values[ADS111X_GAIN_4V096];

    if (const auto res = ads111x_init_desc(&i2c_adc,
                                           ADC_ADDRESS,
                                           I2C_NUM_0,
                                           static_cast<gpio_num_t>(CONFIG_BICYCLE_PIN_I2C_SDA),
                                           static_cast<gpio_num_t>(CONFIG_BICYCLE_PIN_I2C_SCL));
        res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to init ADC: %s", esp_err_to_name(res));
        return res;
    }

    if (const auto res = ads111x_set_mode(&i2c_adc, ADS111X_MODE_CONTINUOUS); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set ADC mode: %s", esp_err_to_name(res));
        return res;
    }

    if (const auto res = ads111x_set_data_rate(&i2c_adc, ADS111X_DATA_RATE_128); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set ADC data rate: %s", esp_err_to_name(res));
        return res;
    }

    if (const auto res = ads111x_set_gain(&i2c_adc, ADS111X_GAIN_4V096); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set ADC gain: %s", esp_err_to_name(res));
        return res;
    }

    return ESP_OK;
}

void adc_task(void(*))
{
    if (adc_initialized)
        return;

    if (const auto res = internal_init_adc(); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to init adc: %s", esp_err_to_name(res));
        return;
    }

    ESP_LOGI(TAG, "adc initialized");

    adc_initialized = true;

    std::array<float, 4> internal_adc_values {};

    while (true)
    {
        if (!adc_initialized)
            return;

        std::ranges::fill(internal_adc_values, 0.0f);

        constexpr auto measure = [&](const ads111x_mux_t mux, float &value) -> esp_err_t {
            if (const auto res = ads111x_set_input_mux(&i2c_adc, mux); res != ESP_OK)
            {
                ESP_LOGE(TAG, "Failed to set ADC input mux: %s", esp_err_to_name(res));
                return res;
            }

            int16_t raw_value { 0 };

            constexpr auto settleIter = 10;

            for (uint8_t i = 0; i < settleIter; i++)
            {
                if (const auto res = ads111x_get_value(&i2c_adc, &raw_value); res != ESP_OK)
                {
                    ESP_LOGE(TAG, "Failed to get ADC value: %s", esp_err_to_name(res));
                    return res;
                }

                vTaskDelay(pdMS_TO_TICKS(10));
            }

            value = adc_gain / ADS111X_MAX_VALUE * raw_value;

            return ESP_OK;
        };

        for (size_t i = 0; i < adc_mux_cfgs.size(); i++)
        {
            if (const auto res = measure(adc_mux_cfgs[i], internal_adc_values[i]); res != ESP_OK)
            {
                ESP_LOGE(TAG, "Failed to measure ADC value: %s", esp_err_to_name(res));
                return;
            }
        }

        // push internal adc values to atomic
        adc_values.store(internal_adc_values);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

} // namespace

void init_adc()
{
    if (auto result =
            espcpputils::createTask(adc_task, "adc", 2048, nullptr, 10, &taskHandle, espcpputils::CoreAffinity::Core1);
        result != pdPASS)
    {
        auto msg = std::format("failed creating adc task {}", result);
        ESP_LOGE(TAG, "%.*s", msg.size(), msg.data());
        return;
    }

    ESP_LOGI(TAG, "ADC task created");
}

void update_adc()
{
    if (!adc_initialized)
        return;

    const auto &adc_values_ref = adc_values.load();

    _battery_voltage = adc_values_ref[BATTERY_VOLTAGE_PIN] * BATTERY_VOLTAGE_MULTIPLIER;

    {
        float cc6904_voltage = adc_values_ref[BATTERY_CURRENT_PIN];

        cc6904_voltage = std::clamp(cc6904_voltage, CC6904_MIN_VOLTAGE, CC6904_MAX_VOLTAGE);

        // map voltage to min/max current
        _battery_current =
            map_value(cc6904_voltage, CC6904_MIN_VOLTAGE, CC6904_MAX_VOLTAGE, CC6904_MIN_CURRENT, CC6904_MAX_CURRENT);
    }

    _aux_adc_0 = adc_values_ref[AUX_ADC_0_PIN];

    _aux_adc_1 = adc_values_ref[AUX_ADC_1_PIN];
}

} // namespace bicycle::hardware