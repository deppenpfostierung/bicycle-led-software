#pragma once

// system includes
#include <array>

// 3rdparty lib includes
#include <tftinterface.h>

// local includes
#include "guihelpers/displaywithtitle.h"

namespace bicycle::gui
{

class ConfigureBasicButtonDisplay : public BicycleDisplayWithTitle
{
    using Base = BicycleDisplayWithTitle;

public:
    void start() override;

    void initScreen(espgui::TftInterface &tft) override;

    void redraw(espgui::TftInterface &tft) override;

    std::string title() const override;

    void rawButtonPressed(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;

private:
    enum class ButtonType : uint8_t
    {
        RIGHT,
        DOWN,
        LEFT,
        UP,
        BUTTON_MAX,
    };

    class DisplayButton
    {
    public:
        explicit DisplayButton(const ButtonType type)
            : m_type { type }
        {
        }

        void start(espgui::TftInterface &tft);

        void redraw(espgui::TftInterface &tft, bool selected, int16_t color_override = -1);

        ButtonType type() const
        {
            return m_type;
        }

        void selectButton(const uint8_t button)
        {
            m_selectedButton = button;
        }

        uint8_t selectedButton() const
        {
            return m_selectedButton;
        }

    private:
        bool m_lastState { false };

        uint8_t m_selectedButton { 255 };

        const ButtonType m_type;

        int16_t m_x { 0 };
        int16_t m_y { 0 };
    };

    void saveButton(uint8_t button);

    std::array<DisplayButton, 4> m_buttons {
        DisplayButton { ButtonType::UP },
        DisplayButton { ButtonType::DOWN },
        DisplayButton { ButtonType::LEFT },
        DisplayButton { ButtonType::RIGHT },
    };

    ButtonType m_selectedButton { static_cast<ButtonType>(0) };

    bool m_done { false };
};

} // namespace bicycle::gui
