#pragma once

// local includes
#include "guihelpers/runtimeicon.h"
#include "statemachine.h"

namespace bicycle::runtimeicons
{

class BatteryproblemIcon : public gui::RuntimeIcon
{
    using Base = RuntimeIcon;
    using Base::Base;

public:
    void redraw(espgui::TftInterface &tft, bool force, std::optional<uint16_t> forceColor) override;

    void update() override
    {
        Base::update();

        using namespace std::chrono_literals;

        if (m_isVisible)
            return;

        const auto &state = stateMachine.getCurrentState();

        m_isVisible = state.battery.batteryState != State::Battery::BATTERY_OK;

        m_color = state.battery.batteryState == State::Battery::BATTERY_LOW ? espgui::TFT_GOLD : espgui::TFT_RED;
    }

    uint16_t getWidth() override;

    uint16_t getHeight() override;

    std::string name() const override
    {
        return "BatteryproblemIcon";
    }

private:
    bool m_lastVisible { false };

    uint16_t m_color { espgui::TFT_RED };
    uint16_t m_lastColor { 0 };

    constexpr static auto NIPPLE_HEIGHT = 4;
    constexpr static auto NIPPLE_WIDTH = 6;
    constexpr static auto NIPPLE_SPACING = 3;
};

} // namespace bicycle::runtimeicons
