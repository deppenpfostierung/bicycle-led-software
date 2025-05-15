#pragma once

// local includes
#include "guihelpers/runtimeicon.h"
#include "statemachine.h"

namespace bicycle::runtimeicons
{

class RearFoglightIcon : public gui::RuntimeIcon
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

        m_isVisible = stateMachine.getCurrentState().lights.rearFogLight;
    }

    uint16_t getWidth() override;

    uint16_t getHeight() override;

    std::string name() const override
    {
        return "RearFoglightIcon";
    }

private:
    bool m_lastVisible { false };

    constexpr static auto SPACING = 8;
    constexpr static auto LINE_LENGTH = 4;
};

} // namespace bicycle::runtimeicons
