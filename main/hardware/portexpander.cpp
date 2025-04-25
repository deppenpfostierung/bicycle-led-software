#include "portexpander.h"

#include <sdkconfig.h>

// esp-idf includes
#include <esp_log.h>
#include <i2cdev.h>

// 3rdparty lib includes
#include "hardware/i2c.h"

#include <pca9685.h>

constexpr const char *const TAG = "HW/PORTEXPANDER";

namespace bicycle::hardware
{

bool portexpander_initialized { false };

namespace
{

i2c_dev_t i2c_portexpander;

esp_err_t internal_init_portexpander()
{
    if (!i2c_initialized)
    {
        ESP_LOGE(TAG, "I2C not initialized");
        return ESP_FAIL;
    }

    if (const auto res = pca9685_init_desc(&i2c_portexpander,
                                           CONFIG_BICYCLE_GPIO_EXPANDER_ADDRESS,
                                           I2C_NUM_0,
                                           static_cast<gpio_num_t>(CONFIG_BICYCLE_PIN_I2C_SDA),
                                           static_cast<gpio_num_t>(CONFIG_BICYCLE_PIN_I2C_SCL));
        res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to init PCA9685: %s", esp_err_to_name(res));
        return res;
    }

    if (const auto res = pca9685_init(&i2c_portexpander); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to init PCA9685: %s", esp_err_to_name(res));
        return res;
    }

    if (const auto res = pca9685_restart(&i2c_portexpander); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to restart PCA9685: %s", esp_err_to_name(res));
        return res;
    }

    if (const auto res = pca9685_set_pwm_frequency(&i2c_portexpander, CONFIG_BICYCLE_GPIO_EXPANDER_PWM_FREQ_HZ);
        res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set PCA9685 frequency: %s", esp_err_to_name(res));
        return res;
    }

    uint16_t configuredFrequency { 0 };

    if (const auto res = pca9685_get_pwm_frequency(&i2c_portexpander, &configuredFrequency); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get PCA9685 frequency: %s", esp_err_to_name(res));
        return res;
    }

    if (configuredFrequency == CONFIG_BICYCLE_GPIO_EXPANDER_PWM_FREQ_HZ)
    {
        ESP_LOGI(TAG, "Successfully set PCA9685 frequency set to %u Hz", configuredFrequency);
    }
    else
    {
        ESP_LOGW(TAG,
                 "PCA9685 frequency set to %u Hz, expected %u Hz",
                 configuredFrequency,
                 CONFIG_BICYCLE_GPIO_EXPANDER_PWM_FREQ_HZ);
    }

    return ESP_OK;
}

} // namespace

void init_portexpander()
{
    if (portexpander_initialized)
        return;

    if (const auto res = internal_init_portexpander(); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to init port expander: %s", esp_err_to_name(res));
        return;
    }

    ESP_LOGI(TAG, "Port expander initialized");

    portexpander_initialized = true;
}

uint16_t val = 0;

void update_portexpander()
{
    if (!portexpander_initialized)
        return;

    if (pca9685_set_pwm_value(&i2c_portexpander, 0, val) != ESP_OK)
        ESP_LOGE(TAG, "Could not set PWM value to ch0");
    if (pca9685_set_pwm_value(&i2c_portexpander, 4, PCA9685_MAX_PWM_VALUE - val) != ESP_OK)
        ESP_LOGE(TAG, "Could not set PWM value to ch3");

    val += 10;

    if (val > PCA9685_MAX_PWM_VALUE)
        val = 0;
}

} // namespace bicycle::hardware