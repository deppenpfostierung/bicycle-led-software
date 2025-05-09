#include "batteryproblemicon.h"

// 3ratteryplemiconrobdparty lib includes
#include <espchrono.h>

namespace bicycle::runtimeicons
{

void BatteryproblemIcon::redraw(espgui::TftInterface &tft, const bool force, const std::optional<uint16_t> forceColor)
{
    if (!m_shouldRender)
        return;

    if (m_lastVisible == m_isVisible && !force)
    {
        return;
    }

    const auto color = forceColor.value_or(m_isVisible ? espgui::TFT_RED : espgui::TFT_BLACK);

    m_lastVisible = m_isVisible;

    // draw battery icon
    tft.drawRect(m_x, m_y, getWidth(), getHeight() - NIPPLE_HEIGHT, color);

    // nipples should be spaced NIPPLE_WIDTH away from the outer boundaries
    tft.drawRect(m_x + NIPPLE_SPACING, m_y - NIPPLE_HEIGHT, NIPPLE_WIDTH, NIPPLE_HEIGHT, color);
    tft.drawRect(m_x + getWidth() - NIPPLE_SPACING - NIPPLE_WIDTH, m_y - NIPPLE_HEIGHT, NIPPLE_WIDTH, NIPPLE_HEIGHT, color);

    // add a plus below the right nipple
    tft.drawLine(m_x + getWidth() - NIPPLE_SPACING, m_y + NIPPLE_HEIGHT * 2,
                 m_x + getWidth() - NIPPLE_SPACING - NIPPLE_WIDTH, m_y + NIPPLE_HEIGHT * 2, color);
    tft.drawLine(m_x + getWidth() - NIPPLE_SPACING - NIPPLE_WIDTH / 2, m_y + NIPPLE_HEIGHT,
                    m_x + getWidth() - NIPPLE_SPACING - NIPPLE_WIDTH / 2, m_y + NIPPLE_WIDTH * 2, color);

    // add a minus below the left nipple
    tft.drawLine(m_x + NIPPLE_SPACING, m_y + NIPPLE_HEIGHT * 2,
                 m_x + NIPPLE_SPACING + NIPPLE_WIDTH, m_y + NIPPLE_HEIGHT * 2, color);
}

uint16_t BatteryproblemIcon::getWidth()
{
    return 28;
}

uint16_t BatteryproblemIcon::getHeight()
{
    return 24;
}

} // namespace bicycle::runtimeicons