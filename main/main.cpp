constexpr const char * const TAG = "main";

// esp-idf includes
#include <esp_log.h>

extern "C" void app_main()
{
  ESP_LOGI(TAG, "app_main() called");
  while (true)
  {
  }
}

