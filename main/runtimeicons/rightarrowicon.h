#pragma once

// local includes
#include "guihelpers/runtimeicon.h"
#include "statemachine.h"

namespace bicycle::runtimeicons
{

class RightArrowIcon : public gui::RuntimeIcon
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

        const auto &state = stateMachine.getCurrentState();

        m_isVisible =
            state.lights.blinkerState == State::Lights::RIGHT || state.lights.blinkerState == State::Lights::HAZARD;

        if (!state.lights.blinkVisible)
        {
            m_isVisible = false;
        }
    }

    uint16_t getWidth() override;

    uint16_t getHeight() override;

    std::string name() const override
    {
        return "RightArrowIcon";
    }

private:
    bool m_lastVisible { false };
};

} // namespace bicycle::runtimeicons
