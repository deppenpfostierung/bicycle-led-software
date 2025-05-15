#include "leftarrowicon.h"

namespace bicycle::runtimeicons
{

void LeftArrowIcon::redraw(espgui::TftInterface &tft, const bool force, const std::optional<uint16_t> forceColor)
{
    if (!m_shouldRender)
        return;

    if (m_lastVisible == m_isVisible && !force)
    {
        return;
    }

    m_lastVisible = m_isVisible;

    const auto color = forceColor.value_or(m_isVisible ? espgui::TFT_GREEN : espgui::TFT_BLACK);

    // draw an arrow
    tft.fillRect(m_x, m_y + getHeight() / 2 - 2, getWidth(), 4, color);

    // flip arrow and move to the left
    tft.fillTriangle(m_x,
                     m_y + getHeight() / 2,
                     m_x + getWidth() / 2,
                     m_y,
                     m_x + getWidth() / 2,
                     m_y + getHeight(),
                     color);
}

uint16_t LeftArrowIcon::getWidth()
{
    return 20;
}

uint16_t LeftArrowIcon::getHeight()
{
    return 20;
}

} // namespace bicycle::runtimeicons