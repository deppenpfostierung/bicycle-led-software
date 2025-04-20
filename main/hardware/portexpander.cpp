#include "portexpander.h"

#include <sdkconfig.h>

// esp-idf includes
#include <esp_log.h>
#include <i2cdev.h>

// 3rdparty lib includes
#include <pca9685.h>

constexpr const char *const TAG = "PORTEXPANDER";

namespace bicycle::hardware
{

bool initialized { false };

namespace
{

i2c_dev_t i2cPortExpander;

esp_err_t internal_init_portexpander()
{
    if (const auto res = pca9685_init_desc(&i2cPortExpander,
                                           0x70,
                                           I2C_NUM_0,
                                           static_cast<gpio_num_t>(CONFIG_BICYCLE_PIN_I2C_SDA),
                                           static_cast<gpio_num_t>(CONFIG_BICYCLE_PIN_I2C_SCL));
        res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to init PCA9685: %s", esp_err_to_name(res));
        return res;
    }

    if (const auto res = pca9685_init(&i2cPortExpander); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to init PCA9685: %s", esp_err_to_name(res));
        return res;
    }

    if (const auto res = pca9685_restart(&i2cPortExpander); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to restart PCA9685: %s", esp_err_to_name(res));
        return res;
    }

    if (const auto res = pca9685_set_pwm_frequency(&i2cPortExpander, CONFIG_BICYCLE_GPIO_EXPANDER_PWM_FREQ_HZ);
        res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set PCA9685 frequency: %s", esp_err_to_name(res));
        return res;
    }

    uint16_t configuredFrequency{0};

    if (const auto res = pca9685_get_pwm_frequency(&i2cPortExpander, &configuredFrequency); res != ESP_OK)
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
        ESP_LOGW(TAG, "PCA9685 frequency set to %u Hz, expected %u Hz", configuredFrequency,
                 CONFIG_BICYCLE_GPIO_EXPANDER_PWM_FREQ_HZ);
    }

    return ESP_OK;
}

} // namespace

void init_portexpander()
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = CONFIG_BICYCLE_PIN_I2C_SDA;
    conf.scl_io_num = CONFIG_BICYCLE_PIN_I2C_SCL;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000;
    i2c_param_config(I2C_NUM_0, &conf);

    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

    {
        esp_err_t res;
        printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
        printf("00:         ");
        for (uint8_t i = 3; i < 0x78; i++)
        {
            i2c_cmd_handle_t cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, (i << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
            i2c_master_stop(cmd);

            res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10 / portTICK_PERIOD_MS);
            if (i % 16 == 0)
                printf("\n%.2x:", i);
            if (res == 0)
                printf(" %.2x", i);
            else
                printf(" --");
            i2c_cmd_link_delete(cmd);
        }
        printf("\n\n");
    }

    // uninstall driver again
    i2c_driver_delete(I2C_NUM_0);

    if (initialized)
        return;

    if (const auto res = internal_init_portexpander(); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to init port expander: %s", esp_err_to_name(res));
        return;
    }

    ESP_LOGI(TAG, "Port expander initialized");

    initialized = true;
}

uint16_t val = 0;

void update_portexpander()
{
    if (!initialized)
        return;

    if (!(val % 100))
        ESP_LOGI(TAG, "CH0 = %-4d | CH3 = %-4d", val, PCA9685_MAX_PWM_VALUE - val);

    if (pca9685_set_pwm_value(&i2cPortExpander, 0, val) != ESP_OK)
        ESP_LOGE(TAG, "Could not set PWM value to ch0");
    if (pca9685_set_pwm_value(&i2cPortExpander, 4, PCA9685_MAX_PWM_VALUE - val) != ESP_OK)
        ESP_LOGE(TAG, "Could not set PWM value to ch3");

    val += 10;

    if (val > PCA9685_MAX_PWM_VALUE)
        val = 0;
}

} // namespace bicycle::hardware