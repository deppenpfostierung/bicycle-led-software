#pragma once

// local includes
#include "guihelpers/runtimeicon.h"

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

        m_isVisible = espchrono::millis_clock::now().time_since_epoch() % 1s < 500ms;
    }

    uint16_t getWidth() override;

    uint16_t getHeight() override;

    std::string name() const override
    {
        return "RearFoglightIcon";
    }

private:
    bool m_lastVisible { false };
};

} // namespace bicycle::runtimeicons
