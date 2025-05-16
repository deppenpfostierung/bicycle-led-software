#include "taskmanager.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "hardware/portexpander.h"
#include "input/dpad.h"
#include "screen.h"
#include "serialdebug.h"
#include "statemachine.h"
#include "wifi.h"

using namespace std::chrono_literals;

namespace bicycle::tasks
{
namespace
{
using namespace espcpputils;

constexpr const char *const TAG = "TASKMANAGER";

void noop()
{
}

SchedulerTask schedulerTaskArr[] {
    SchedulerTask { "i2c",            hardware::init_i2c,          hardware::update_i2c,          100ms },
    SchedulerTask { "portexpander",   hardware::init_portexpander, hardware::update_portexpander, 16ms  },
    SchedulerTask { "adc",            hardware::init_adc,          hardware::update_adc,          100ms },
    SchedulerTask { "dpad",           buttons::init,               buttons::update,               30ms  },
    SchedulerTask { "debugconsole",   debug::init,                 debug::update,                 50ms  },
    SchedulerTask { "display_update", noop,                        screen::update,                16ms  },
    SchedulerTask { "wifi",           wifi::begin,                 wifi::update,                  100ms },
    SchedulerTask { "statemachine",   init_statemachine,           update_statemachine,           50ms  },
};
} // namespace

cpputils::ArrayView<SchedulerTask> schedulerTasks { std::begin(schedulerTaskArr), std::end(schedulerTaskArr) };

void sched_pushStats(const bool printTasks)
{
    if (printTasks)
        ESP_LOGI(TAG, "Task stats:");

    for (auto &task : schedulerTasks)
        task.pushStats(printTasks);
}

} // namespace bicycle::tasks
