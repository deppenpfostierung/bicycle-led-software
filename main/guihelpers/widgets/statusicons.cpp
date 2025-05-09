#include "statusicons.h"

namespace bicycle::gui
{

void StatusIcons::init(espgui::TftInterface &tft)
{
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

    tft.drawRoundRect(m_x, m_y, m_calculatedWidth, m_calculatedHeight, 4, espgui::TFT_GREY);
}

} // namespace bicycle::gui