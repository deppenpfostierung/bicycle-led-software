#pragma once

// system includes
#include <array>

// 3rdparty lib includes
#include <tftinterface.h>

// local includes
#include "runtimeicons/brakelighticon.h"
#include "runtimeicons/rearfoglighticon.h"

namespace bicycle::gui
{

class StatusIcons
{
    static constexpr auto PADDING = 10;

public:
    StatusIcons(const uint16_t x, const uint16_t y)
        : m_x { x }
        , m_y { y }
    {
    }

    void init(espgui::TftInterface &tft);

    void redraw(espgui::TftInterface &tft);

    void update();

private:
    void drawBox(espgui::TftInterface &tft);

    // pos
    uint16_t m_x { 0 };
    uint16_t m_y { 0 };

    uint16_t m_calculatedHeight { 0 };
    uint16_t m_calculatedWidth { 0 };

    uint8_t m_lastVisibleIconCount { 0 };

    std::array<std::unique_ptr<RuntimeIcon>, 2> m_icons {
        {
         std::make_unique<runtimeicons::BrakelightIcon>(m_x, m_y),
         std::make_unique<runtimeicons::RearFoglightIcon>(m_x, m_y),
         }
    };
};

} // namespace bicycle::gui