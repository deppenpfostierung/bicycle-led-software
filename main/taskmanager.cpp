#include "taskmanager.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "input/dpad.h"
#include "screen.h"
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
    SchedulerTask { "wifi",           wifi::begin,   wifi::update,          100ms },
    SchedulerTask { "display_update", noop,          bicycle::screen::loop, 16ms  },
    SchedulerTask { "dpad",           buttons::init, buttons::update,       30ms  },
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