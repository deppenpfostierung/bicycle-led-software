#include "rearfoglighticon.h"

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

    const auto color = forceColor.value_or(m_isVisible ? espgui::color565(255, 120, 0) : espgui::TFT_BLACK);

    const auto radius = getHeight() / 2;

    const auto segmentHeight = getHeight() / 3;

    tft.drawArc(m_x + radius, m_y + radius, radius, radius, 0, 180, color, espgui::TFT_BLACK);
    tft.drawLine(m_x + radius, m_y, m_x + radius, m_y + getHeight(), color);

    tft.drawLine(m_x + radius + SPACING, m_y, m_x + radius + SPACING, m_y + getHeight(), color);

    tft.drawLine(m_x + radius + LINE_LENGTH,
                 m_y + radius - segmentHeight,
                 m_x + radius + SPACING + LINE_LENGTH,
                 m_y + radius - segmentHeight,
                 color);
    tft.drawLine(m_x + radius + LINE_LENGTH, m_y + radius, m_x + radius + SPACING + LINE_LENGTH, m_y + radius, color);
    tft.drawLine(m_x + radius + LINE_LENGTH,
                 m_y + radius + segmentHeight,
                 m_x + radius + SPACING + LINE_LENGTH,
                 m_y + radius + segmentHeight,
                 color);
}

uint16_t RearFoglightIcon::getWidth()
{
    const auto radius = getHeight() / 2;

    return radius + SPACING + LINE_LENGTH;
}

uint16_t RearFoglightIcon::getHeight()
{
    return 20;
}

} // namespace bicycle::runtimeicons
