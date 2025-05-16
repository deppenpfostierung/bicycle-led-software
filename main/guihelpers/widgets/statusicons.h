#pragma once

// system includes
#include <array>
#include <numeric>

// 3rdparty lib includes
#include <tftinterface.h>

// local includes
#include "runtimeicons/batteryproblemicon.h"
#include "runtimeicons/brakelighticon.h"
#include "runtimeicons/highbeamlighticon.h"
#include "runtimeicons/lowbeamlighticon.h"
#include "runtimeicons/rearfoglighticon.h"

namespace bicycle::gui
{

class StatusIcons
{
    static constexpr auto PADDING = 10;

public:
    StatusIcons(const uint16_t x, const uint16_t y, const bool autoCenter = false)
        : m_x { x }
        , m_y { y }
    {
        m_calculatedHeight =
            std::accumulate(m_icons.begin(),
                            m_icons.end(),
                            0,
                            [](uint16_t maxHeight, const auto &icon) { return std::max(maxHeight, icon->getHeight()); })
            + 2 * PADDING;

        m_calculatedWidth =
            std::accumulate(m_icons.begin(),
                            m_icons.end(),
                            0,
                            [](uint16_t sum, const auto &icon) { return sum + icon->getWidth() + PADDING; })
            + PADDING;

        if (autoCenter)
        {
            m_x -= m_calculatedWidth / 2;
        }
    }

    void init(espgui::TftInterface &tft);

    void redraw(espgui::TftInterface &tft);

    void update();

    void stop();

    uint16_t getHeight() const
    {
        return m_calculatedHeight;
    }

    uint16_t getWidth() const
    {
        return m_calculatedWidth;
    }

    uint16_t getX() const
    {
        return m_x;
    }

    uint16_t getY() const
    {
        return m_y;
    }

private:
    void drawBox(espgui::TftInterface &tft);

    // pos
    uint16_t m_x { 0 };
    uint16_t m_y { 0 };

    uint16_t m_calculatedHeight { 0 };
    uint16_t m_calculatedWidth { 0 };

    uint8_t m_lastVisibleIconCount { 0 };

    std::array<std::unique_ptr<RuntimeIcon>, 5> m_icons {
        {
         std::make_unique<runtimeicons::BrakelightIcon>(m_x, m_y),
         std::make_unique<runtimeicons::RearFoglightIcon>(m_x, m_y),
         std::make_unique<runtimeicons::HighbeamlightIcon>(m_x, m_y),
         std::make_unique<runtimeicons::LowbeamlightIcon>(m_x, m_y),
         std::make_unique<runtimeicons::BatteryproblemIcon>(m_x, m_y),
         }
    };
};

} // namespace bicycle::gui
