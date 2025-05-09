#include "rearfoglighticon.h"

// 3rdparty lib includes
#include <espchrono.h>

namespace bicycle::runtimeicons
{

void RearFoglightIcon::redraw(espgui::TftInterface &tft, const bool force, const std::optional<uint16_t> forceColor)
{
    if (!m_shouldRender)
        return;

    if (m_lastVisible == m_isVisible && !force)
    {
        return;
    }

    m_lastVisible = m_isVisible;

    const auto color = forceColor.value_or(m_isVisible ? espgui::TFT_RED : espgui::TFT_BLACK);

    const auto radius = getHeight() / 2;

    tft.drawArc(m_x + radius, m_y + radius, radius, radius, 0, 180, color, espgui::TFT_BLACK);
    tft.drawLine(m_x + radius, m_y, m_x + radius, m_y + getHeight(), color);

    tft.drawLine(m_x + radius + 10, m_y, m_x + radius + 10, m_y + getHeight(), color);
    tft.drawLine(m_x + radius + 5, m_y + radius - 5, m_x + radius + 15, m_y + radius - 5, color);
    tft.drawLine(m_x + radius + 5, m_y + radius, m_x + radius + 15, m_y + radius, color);
    tft.drawLine(m_x + radius + 5, m_y + radius + 5, m_x + radius + 15, m_y + radius + 5, color);
}

uint16_t RearFoglightIcon::getWidth()
{
    const auto radius = getHeight() / 2;

    return radius + 15;
}

uint16_t RearFoglightIcon::getHeight()
{
    return 20;
}

} // namespace bicycle::runtimeicons