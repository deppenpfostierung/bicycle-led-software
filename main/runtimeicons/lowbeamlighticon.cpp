#include "lowbeamlighticon.h"

namespace bicycle::runtimeicons
{

void LowbeamlightIcon::redraw(espgui::TftInterface &tft, const bool force, const std::optional<uint16_t> forceColor)
{
    if (!m_shouldRender)
        return;

    if (m_lastVisible == m_isVisible && !force)
    {
        return;
    }

    m_lastVisible = m_isVisible;

    const auto color = forceColor.value_or(m_isVisible ? espgui::TFT_GREEN : espgui::TFT_BLACK);

    const auto radius = getHeight() / 2;

    const auto segmentHeight = getHeight() / 3;

    tft.drawLine(m_x, m_y + radius - segmentHeight + DOWNWARDS, m_x + LINE_LENGTH, m_y + radius - segmentHeight, color);
    tft.drawLine(m_x, m_y + radius + DOWNWARDS, m_x + LINE_LENGTH, m_y + radius, color);
    tft.drawLine(m_x, m_y + radius + segmentHeight + DOWNWARDS, m_x + LINE_LENGTH, m_y + radius + segmentHeight, color);

    constexpr auto distance = LINE_LENGTH + SPACING;

    tft.drawArc(m_x + distance, m_y + radius, radius, radius, 180, 360, color, espgui::TFT_BLACK);
    tft.drawLine(m_x + distance, m_y, m_x + distance, m_y + getHeight(), color);
}

uint16_t LowbeamlightIcon::getWidth()
{
    const auto radius = getHeight() / 2;

    return radius + SPACING + LINE_LENGTH;
}

uint16_t LowbeamlightIcon::getHeight()
{
    return 20;
}

} // namespace bicycle::runtimeicons
