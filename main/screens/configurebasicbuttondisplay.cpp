#include "configurebasicbuttondisplay.h"

// esp-idf includes
#include <esp_err.h>
#include <esp_log.h>

// 3rdparty lib includes
#include <tftcolors.h>

// local includes
#include "configs.h"
#include "screens/startdisplay.h"

constexpr const char *const TAG = "ConfigureBasicButtonDisplay";

namespace bicycle::gui
{

void ConfigureBasicButtonDisplay::start()
{
    Base::start();
}

void ConfigureBasicButtonDisplay::initScreen(espgui::TftInterface &tft)
{
    Base::initScreen(tft);

    for (auto &m_button : m_buttons)
    {
        m_button.start(tft);
    }
}

void ConfigureBasicButtonDisplay::redraw(espgui::TftInterface &tft)
{
    Base::redraw(tft);

    for (auto &m_button : m_buttons)
    {
        m_button.redraw(tft, m_done ? false : m_selectedButton == m_button.type(), m_done ? espgui::TFT_GREEN : -1);
    }
}

std::string ConfigureBasicButtonDisplay::title() const
{
    return m_done ? "Press RIGHT to finish" : "Configure basic buttons";
}

void ConfigureBasicButtonDisplay::saveButton(const uint8_t button)
{
    if (m_selectedButton != ButtonType::BUTTON_MAX)
    {
        // check if any button has .selectedButton() == button
        const auto btn =
            std::ranges::find_if(m_buttons, [button](const auto &b) { return b.selectedButton() == button; });

        // if found, ESP_LOGW and return
        if (btn != m_buttons.end())
        {
            ESP_LOGW(TAG, "Button %d is already assigned to %d", button, static_cast<uint8_t>(btn->type()));
            return;
        }

        ConfigStatusReturnType result;

        switch (m_selectedButton)
        {
        case ButtonType::UP:
            result = configs.write_config(configs.dpad.mappingUp, button);
            break;
        case ButtonType::DOWN:
            result = configs.write_config(configs.dpad.mappingDown, button);
            break;
        case ButtonType::LEFT:
            result = configs.write_config(configs.dpad.mappingLeft, button);
            break;
        case ButtonType::RIGHT:
            result = configs.write_config(configs.dpad.mappingRight, button);
            break;
        default:
            ESP_LOGW(TAG, "Button %d is not a valid button", static_cast<uint8_t>(m_selectedButton));
            break;
        }

        if (result)
        {
            ESP_LOGI(TAG, "Button %d saved as %d", button, static_cast<uint8_t>(m_selectedButton));
        }
        else
        {
            ESP_LOGE(TAG, "Failed to save button %d: %s", button, result.error().c_str());
        }

        m_selectedButton = static_cast<ButtonType>(static_cast<uint8_t>(m_selectedButton) + 1);

        if (m_selectedButton == ButtonType::BUTTON_MAX)
        {
            m_done = true;
        }
    }
    else
    {
        m_done = true;
    }
}

void ConfigureBasicButtonDisplay::rawButtonPressed(const uint8_t button)
{
    Base::rawButtonPressed(button);

    if (m_done)
    {
        return;
    }

    saveButton(button);
}

void ConfigureBasicButtonDisplay::buttonPressed(const espgui::Button button)
{
    if (button == espgui::Right && m_done)
    {
        espgui::switchScreen<StartDisplay>();
    }
}

void ConfigureBasicButtonDisplay::DisplayButton::start(espgui::TftInterface &tft)
{
    const auto x_center = tft.width() / 2;
    const auto y_center = (tft.height() + TITLE_HEIGHT) / 2;

    // calculate the button position
    constexpr auto distance_to_center = 40;

    const auto angle_offset = static_cast<float>(m_type) * (2.0f * M_PI / static_cast<float>(ButtonType::BUTTON_MAX));
    m_x = x_center + distance_to_center * std::cos(angle_offset);
    m_y = y_center + distance_to_center * std::sin(angle_offset);

    // draw button
    tft.drawCircle(m_x, m_y, 20, espgui::TFT_WHITE);
}

void ConfigureBasicButtonDisplay::DisplayButton::redraw(espgui::TftInterface &tft, const bool selected,
                                                        const int16_t color_override)
{
    if (m_lastState == selected && color_override == -1)
    {
        return;
    }

    m_lastState = selected;

    tft.fillCircle(m_x,
                   m_y,
                   16,
                   color_override != -1 ? color_override
                   : selected           ? espgui::TFT_YELLOW
                                        : espgui::TFT_WHITE);
}

} // namespace bicycle::gui
