#include "statusicons.h"

// system includes
#include "richtexthelper.h"

#include <numeric>

namespace bicycle::gui
{

void StatusIcons::init(espgui::TftInterface &tft)
{
    // first iterate over it to find the max height
    m_calculatedHeight = std::accumulate(m_icons.begin(), m_icons.end(), 0, [](uint16_t maxHeight, const auto &icon) {
        return std::max(maxHeight, icon->getHeight());
    }) + 2 * PADDING;

    for (const auto &icon : m_icons)
    {
        icon->init(tft, false);
        icon->moveTo(tft, m_x, m_y + m_calculatedHeight / 2 - icon->getHeight() / 2, espgui::TFT_BLACK, true);
    }

    drawBox(tft);
}

void StatusIcons::update()
{
    for (const auto &icon : m_icons)
    {
        icon->update();
    }
}

void StatusIcons::redraw(espgui::TftInterface &tft)
{
    drawBox(tft);

    uint16_t x = m_x + PADDING;
    uint8_t visibleIconCount = 0;

    for (const auto &icon : m_icons)
    {
        if (!icon->isVisible())
        {
            icon->redraw(tft, true, espgui::TFT_BLACK);
            icon->setShouldRender(false);
        }
    }

    for (auto it = m_icons.begin(); it != m_icons.end(); ++it)
    {
        if (const auto &icon = *it; icon->isVisible())
        {
            visibleIconCount++;
            icon->moveToX(tft, x);
            x += icon->getWidth() + PADDING;
            icon->redraw(tft);
            icon->setShouldRender(true);
        }
    }

    // debug
    /*
    for (const auto& icon : m_icons)
    {
        tft.fillRectHGradient(icon->getX(), m_y + 2, icon->getWidth(), 8,
                     espgui::TFT_RED, espgui::TFT_GREEN);
    }
    */

    m_lastVisibleIconCount = visibleIconCount;
}

void StatusIcons::drawBox(espgui::TftInterface &tft)
{
    const uint16_t completeWidth =
        std::accumulate(m_icons.begin(), m_icons.end(), 0, [](uint16_t sum, const auto &icon) {
            return sum + icon->getWidth() + PADDING;
        });

    tft.drawRect(m_x, m_y, completeWidth + PADDING, m_calculatedHeight, espgui::TFT_WHITE);
}

} // namespace bicycle::gui