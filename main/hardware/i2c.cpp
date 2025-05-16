#include "i2c.h"

#include <sdkconfig.h>

// local includes
#include <esp_log.h>

// 3rdparty lib includes
#include <i2cdev.h>

constexpr const char *const TAG = "HW/I2C";

namespace bicycle::hardware
{

std::atomic<bool> _i2c_initialized { false };
const std::atomic<bool> &i2c_initialized { _i2c_initialized };

void init_i2c()
{
    if (i2c_initialized)
        return;

#ifdef CONFIG_BICYCLE_DEBUG_I2C
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = CONFIG_BICYCLE_PIN_I2C_SDA;
    conf.scl_io_num = CONFIG_BICYCLE_PIN_I2C_SCL;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000;
    conf.clk_flags = 0;
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
#endif

    if (const auto res = i2cdev_init(); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to init I2C: %s", esp_err_to_name(res));
        return;
    }

    _i2c_initialized = true;

    ESP_LOGI(TAG, "I2C initialized successfully");
}

void update_i2c()
{
    if (!i2c_initialized.load())
        return;
}

} // namespace bicycle::hardware
