#pragma once

// local includes
#include "guihelpers/runtimeicon.h"
#include "statemachine.h"

namespace bicycle::runtimeicons
{

class LeftArrowIcon : public gui::RuntimeIcon
{
    using Base = RuntimeIcon;
    using Base::Base;

public:
    void redraw(espgui::TftInterface &tft, bool force = false,
                std::optional<uint16_t> forceColor = std::nullopt) override;

    void update() override
    {
        Base::update();

        using namespace std::chrono_literals;

        if (m_isVisible)
            return;

        m_isVisible = stateMachine.getCurrentState().lights.blinkerState == State::Lights::LEFT ||
                      stateMachine.getCurrentState().lights.blinkerState == State::Lights::HAZARD;
    }

    uint16_t getWidth() override;

    uint16_t getHeight() override;

    std::string name() const override
    {
        return "LeftArrowIcon";
    }

private:
    bool m_lastVisible { false };
};

} // namespace bicycle::runtimeicons
