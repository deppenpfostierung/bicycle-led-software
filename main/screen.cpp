#include "screen.h"

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <TFT_eSPI.h>
#include <delayedconstruction.h>
#include <espchrono.h>
#include <screenmanager.h>
#include <tftcolors.h>
#include <tftinterface.h>
#include <widgets/label.h>

// local includes
#include "configs.h"
#include "icons/bootlogo.h"

using namespace std::chrono_literals;

namespace bicycle::screen
{

namespace
{
constexpr const char *const TAG = "SCREEN";

TFT_eSPI tft { 320, 240 };

cpputils::DelayedConstruction<espgui::Label> bootLabel;

espchrono::millis_clock::time_point lastDisplayUpdate;
espchrono::millis_clock::time_point lastDisplayRedraw;
;
} // namespace

void init()
{
    // Initialize the screen here
    tft.init();
    tft.setRotation(configs.display.rotated.value() ? 0 : 2);

    const int centered = (tft.width() - icons::bootlogo.WIDTH) / 2;

    ESP_LOGI(TAG,
             "Screen initialized, w=%u, h=%u, r=%u, centered=%u",
             tft.width(),
             tft.height(),
             tft.getRotation(),
             centered);

    ESP_LOGI(TAG, "Fill with white");

    tft.fillScreen(espgui::TFT_BLACK);

    ESP_LOGI(TAG, "Push image");
    constexpr auto border = 2;
    tft.fillRect(centered - border,
                 10 - border,
                 icons::bootlogo.WIDTH + border * 2,
                 icons::bootlogo.HEIGHT + border * 2,
                 espgui::TFT_WHITE);
    tft.pushImage(centered, 10, icons::bootlogo.WIDTH, icons::bootlogo.HEIGHT, icons::bootlogo.buffer);

    ESP_LOGI(TAG, "Setup label");
    bootLabel.construct(5, tft.height() - 40);
    bootLabel->start(tft);
    setBootMessage("Starting up...");
}

// TODO: Try to investigate why this does not work
void reinit_tft()
{
    tft.init();
    if (espgui::currentDisplay)
        espgui::currentDisplay->initScreen(tft);
}

void update()
{
    if (tft.getRotation() != (configs.display.rotated.value() ? 0 : 2))
    {
        tft.setRotation(configs.display.rotated.value() ? 0 : 2);

        if (espgui::currentDisplay)
            espgui::currentDisplay->initScreen(tft);
    }

    if (espchrono::ago(lastDisplayUpdate) >= 1000ms / 50)
    {
        lastDisplayUpdate = espchrono::millis_clock::now();

        if (espgui::currentDisplay)
            espgui::currentDisplay->update();

        if (espgui::changeScreenCallback)
        {
            espgui::changeScreenCallback(tft);
            ESP_LOGD(TAG, "clearing changeScreenCallback");
            espgui::changeScreenCallback = {};
        }
    }

    if (espchrono::ago(lastDisplayRedraw) >= 1000ms / 60)
    {
        lastDisplayRedraw = espchrono::millis_clock::now();

        if (espgui::currentDisplay)
            espgui::currentDisplay->redraw(tft);
    }
}

void setBootMessage(const std::string_view message)
{
    ESP_LOGI(TAG, "Boot message: %.*s", static_cast<int>(message.size()), message.data());
    bootLabel->redraw(tft, message, espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
}

} // namespace bicycle::screen
