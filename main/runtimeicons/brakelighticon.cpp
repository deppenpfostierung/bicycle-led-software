#include "brakelighticon.h"

// 3rdparty lib includes
#include <espchrono.h>

namespace bicycle::runtimeicons
{

void BrakelightIcon::redraw(espgui::TftInterface &tft, const bool force, const std::optional<uint16_t> forceColor)
{
    if (!m_shouldRender)
        return;

    if (m_lastVisible == m_isVisible && !force)
    {
        return;
    }

    const auto color = forceColor.value_or(m_isVisible ? espgui::TFT_RED : espgui::TFT_BLACK);

    m_lastVisible = m_isVisible;

    tft.drawArc(m_x + ARC_RADIUS, m_y + CIRCLE_RADIUS, ARC_RADIUS, ARC_RADIUS, 20, 160, color, espgui::TFT_BLACK);
    tft.drawCircle(m_x + ARC_RADIUS + 2, m_y + CIRCLE_RADIUS, CIRCLE_RADIUS, color);
    tft.drawArc(m_x + ARC_RADIUS + 4, m_y + CIRCLE_RADIUS, ARC_RADIUS, ARC_RADIUS, 200, 340, color, espgui::TFT_BLACK);
}

uint16_t BrakelightIcon::getWidth()
{
    return ARC_RADIUS * 2 + 4;
}

uint16_t BrakelightIcon::getHeight()
{
    return CIRCLE_RADIUS * 2;
}

} // namespace bicycle::runtimeicons