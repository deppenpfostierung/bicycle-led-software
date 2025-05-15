#pragma once

// local includes
#include "guihelpers/runtimeicon.h"
#include "statemachine.h"

namespace bicycle::runtimeicons
{

class BrakelightIcon : public gui::RuntimeIcon
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

        m_isVisible = stateMachine.getCurrentState().lights.brakeLight;
    }

    uint16_t getWidth() override;

    uint16_t getHeight() override;

    std::string name() const override
    {
        return "BrakelightIcon";
    }

private:
    constexpr static auto CIRCLE_RADIUS = 8;
    constexpr static auto ARC_RADIUS = 10;

    bool m_lastVisible { false };
};

} // namespace bicycle::runtimeicons
