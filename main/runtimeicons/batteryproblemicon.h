#pragma once

// local includes
#include "guihelpers/runtimeicon.h"

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

        m_isVisible = true;
    }

    uint16_t getWidth() override;

    uint16_t getHeight() override;

    std::string name() const override
    {
        return "BatteryproblemIcon";
    }

private:
    bool m_lastVisible { false };

    constexpr static auto NIPPLE_HEIGHT = 4;
    constexpr static auto NIPPLE_WIDTH = 6;
    constexpr static auto NIPPLE_SPACING = 3;
};

} // namespace bicycle::runtimeicons
