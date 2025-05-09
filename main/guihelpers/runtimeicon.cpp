#include "runtimeicon.h"

namespace bicycle::gui
{

void RuntimeIcon::moveTo(espgui::TftInterface &tft, const uint16_t x, const uint16_t y, const uint16_t fillColor,
                         const bool skipRedraw)
{
    if (x == m_x && y == m_y)
        return;

    if (!skipRedraw)
    {
        redraw(tft, true, fillColor);
    }

    m_x = x;
    m_y = y;

    if (!skipRedraw)
    {
        redraw(tft, true);
    }
}

} // namespace bicycle::gui
