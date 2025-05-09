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

    const auto color = forceColor.value_or(m_isVisible ? espgui::TFT_GREEN : espgui::TFT_BLACK);

    tft.fillRect(m_x, m_y, getWidth(), getHeight(), color);
}

uint16_t RearFoglightIcon::getWidth()
{
    return 20;
}

uint16_t RearFoglightIcon::getHeight()
{
    return 20;
}

} // namespace bicycle::runtimeicons