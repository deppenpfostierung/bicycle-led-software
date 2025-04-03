#include "buttons.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "configs.h"
#include "screen.h"

namespace bicycle
{

namespace
{
constexpr const char TAG[] = "BUTTONS";
} // namespace

std::optional<espchrono::millis_clock::time_point> buttonLeftHeld;
std::optional<espchrono::millis_clock::time_point> buttonRightHeld;
std::optional<espchrono::millis_clock::time_point> buttonUpHeld;
std::optional<espchrono::millis_clock::time_point> buttonDownHeld;

[[nodiscard]] std::optional<espgui::Button> translateRawButton(const uint8_t button)
{
    // Invalid
    if (button == INPUT_BUTTON_NONE)
        return std::nullopt;

    using espgui::Button;
    if (configs.dpad.mappingLeft.value() == button)
        return Button::Left;
    if (configs.dpad.mappingRight.value() == button)
        return Button::Right;
    if (configs.dpad.mappingUp.value() == button)
        return Button::Up;
    if (configs.dpad.mappingDown.value() == button)
        return Button::Down;
    if (configs.dpad.mappingCustom1.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom1);
    if (configs.dpad.mappingCustom2.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom2);
    if (configs.dpad.mappingCustom3.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom3);
    if (configs.dpad.mappingCustom4.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom4);
    if (configs.dpad.mappingCustom5.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom5);
    if (configs.dpad.mappingCustom6.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom6);
    if (configs.dpad.mappingCustom7.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom7);
    if (configs.dpad.mappingCustom8.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom8);
    if (configs.dpad.mappingCustom9.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom9);
    if (configs.dpad.mappingCustom10.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom10);
    if (configs.dpad.mappingCustom11.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom11);
    if (configs.dpad.mappingCustom12.buttonId.value() == button)
        return static_cast<Button>(BicycleButton::Custom12);

    ESP_LOGW(TAG, "unknown raw button %hhu", button);

    return std::nullopt;
}

void handleButtonLongPress(const espgui::Button button)
{
    ESP_LOGI(TAG, "long press %hhu", button);
    switch (button)
    {
    case espgui::Button::Right:
        screen::reinit_tft();
        break;
    case espgui::Button::Left:
    case espgui::Button::Up:
    case espgui::Button::Down:
        break;
    default:;
    }
}

void handleCustomAction(const ButtonAction action)
{
    if (action == ButtonAction::Unused)
    {
        return;
    }

    ESP_LOGI(TAG, "Handling action %s", toString(action).c_str());
}

void buttonPressedCommon(const espgui::Button button)
{
    const auto now = espchrono::millis_clock::now();

    switch (button)
    {
        using namespace bicycle;
    case espgui::Button::Left:
        buttonLeftHeld = now;
        break;
    case espgui::Button::Right:
        buttonRightHeld = now;
        break;
    case espgui::Button::Up:
        buttonUpHeld = now;
        break;
    case espgui::Button::Down:
        buttonDownHeld = now;
        break;
    }

    const DpadConfig *cfg_ptr = nullptr;

    // TODO: handle custom buttons
    switch (static_cast<BicycleButton>(button))
    {
    case Custom1:
        cfg_ptr = &configs.dpad.mappingCustom1;
        break;
    case Custom2:
        cfg_ptr = &configs.dpad.mappingCustom2;
        break;
    case Custom3:
        cfg_ptr = &configs.dpad.mappingCustom3;
        break;
    case Custom4:
        cfg_ptr = &configs.dpad.mappingCustom4;
        break;
    case Custom5:
        cfg_ptr = &configs.dpad.mappingCustom5;
        break;
    case Custom6:
        cfg_ptr = &configs.dpad.mappingCustom6;
        break;
    case Custom7:
        cfg_ptr = &configs.dpad.mappingCustom7;
        break;
    case Custom8:
        cfg_ptr = &configs.dpad.mappingCustom8;
        break;
    case Custom9:
        cfg_ptr = &configs.dpad.mappingCustom9;
        break;
    case Custom10:
        cfg_ptr = &configs.dpad.mappingCustom10;
        break;
    case Custom11:
        cfg_ptr = &configs.dpad.mappingCustom11;
        break;
    case Custom12:
        cfg_ptr = &configs.dpad.mappingCustom12;
        break;
    default:
        return;
    }

    if (!cfg_ptr)
        return;

    handleCustomAction(cfg_ptr->action.value());
}

void buttonReleasedCommon(const espgui::Button button)
{
    switch (button)
    {
        using namespace bicycle;
        using namespace std::chrono_literals;
    case espgui::Button::Left:
        if (buttonLeftHeld && espchrono::ago(*buttonLeftHeld) > 500ms)
            handleButtonLongPress(button);
        buttonLeftHeld = std::nullopt;
        break;
    case espgui::Button::Right:
        if (buttonRightHeld && espchrono::ago(*buttonRightHeld) > 500ms)
            handleButtonLongPress(button);
        buttonRightHeld = std::nullopt;
        break;
    case espgui::Button::Up:
        if (buttonUpHeld && espchrono::ago(*buttonUpHeld) > 500ms)
            handleButtonLongPress(button);
        buttonUpHeld = std::nullopt;
        break;
    case espgui::Button::Down:
        if (buttonDownHeld && espchrono::ago(*buttonDownHeld) > 500ms)
            handleButtonLongPress(button);
        buttonDownHeld = std::nullopt;
        break;
    }

    // TODO: handle custom buttons if needed
}

} // namespace bicycle