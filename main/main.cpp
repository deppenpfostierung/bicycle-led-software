constexpr const char *const TAG = "main";
constexpr const char *const MEMORY_TAG = "MEMORYDEBUG";

// esp-idf includes
#include <esp_log.h>

// esp-idf optional includes
#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
#include <esp_task_wdt.h>
#endif

// 3rdparty lib includes
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// local includes
#include "configs.h"
#include "global_lock.h"
#include "input/dpad.h"
#include "screen.h"
#include "screens/configurebasicbuttondisplay.h"
#include "screens/startdisplay.h"
#include "serialdebug.h"
#include "taskmanager.h"

extern "C" void [[noreturn]] app_main()
{
    using namespace bicycle;
    using namespace screen;

    esp_log_level_set("SCREENMANAGER", ESP_LOG_DEBUG);

#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
    {
        const auto taskHandle = xTaskGetCurrentTaskHandle();
        if (!taskHandle)
        {
            ESP_LOGE(TAG, "could not get handle to current main task!");
        }
        else if (const auto result = esp_task_wdt_add(taskHandle); result != ESP_OK)
        {
            ESP_LOGE(TAG, "could not add main task to watchdog: %s", esp_err_to_name(result));
        }
    }
#endif

    if (const auto result = configs.init("config"); result != ESP_OK)
    {
        ESP_LOGE(TAG, "configs.init() failed: %s", esp_err_to_name(result));
        assert(result == ESP_OK);
    }

    global::global_lock.construct();

    screen::init();

    for (auto &task : tasks::schedulerTasks)
    {
        ESP_LOGI(TAG, "Starting task %s", task.name());
        setBootMessage(task.name());
        task.setup();
    }

#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
    if (const auto result = esp_task_wdt_reset(); result != ESP_OK)
        ESP_LOGE(TAG, "esp_task_wdt_reset() failed with %s", esp_err_to_name(result));
#endif

    setBootMessage("Bootup complete");

    if (buttons::isValidConfig())
    {
        espgui::switchScreen<gui::StartDisplay>();
    }
    else
    {
        espgui::switchScreen<gui::ConfigureBasicButtonDisplay>();
    }

    espchrono::millis_clock::time_point lastTaskPush = espchrono::millis_clock::now();

    while (true)
    {
        for (auto &task : tasks::schedulerTasks)
        {
            task.loop();

#if defined(CONFIG_ESP_TASK_WDT_PANIC) || defined(CONFIG_ESP_TASK_WDT)
            if (const auto result = esp_task_wdt_reset(); result != ESP_OK)
                ESP_LOGE(TAG, "esp_task_wdt_reset() failed with %s", esp_err_to_name(result));
#endif
        }

        if (espchrono::ago(lastTaskPush) > 1s)
        {
            lastTaskPush = espchrono::millis_clock::now();
            tasks::sched_pushStats(false);
        }

        if (const auto free_8bit_memory = heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
            free_8bit_memory < 25000)
        {
            ESP_LOGW(MEMORY_TAG,
                     "heap8bit=%zd (largest block: %zd) heap32=%zd",
                     free_8bit_memory,
                     heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT),
                     heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_32BIT));
        }
        else
        {
            if (debug::memoryDebugMode != debug::MemoryDebugMode::Off
                && espchrono::ago(debug::lastMemoryDebugMessage)
                       >= (debug::memoryDebugMode == debug::MemoryDebugMode::Fast ? 100ms : 1000ms))
            {
                debug::lastMemoryDebugMessage = espchrono::millis_clock::now();
                ESP_LOGI(MEMORY_TAG,
                         "heap8bit=%zd (largest block: %zd) heap32=%zd",
                         free_8bit_memory,
                         heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT),
                         heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_32BIT));
            }
        }

        vTaskDelay(1);
    }
}
