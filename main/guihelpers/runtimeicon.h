#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>
#include <tftcolors.h>
#include <tftinterface.h>

namespace bicycle::gui
{

class RuntimeIcon
{
public:
    RuntimeIcon(const uint16_t x, const uint16_t y)
        : m_x { x }
        , m_y { y }
    {
    }

    virtual ~RuntimeIcon() = default;

    virtual void init(espgui::TftInterface &tft, const bool shouldRender = true)
    {
        m_shouldRender = shouldRender;
    }

    virtual void update()
    {
        using namespace std::chrono_literals;

        m_isVisible = espchrono::millis_clock::now().time_since_epoch() <= 3s;
    }

    virtual void redraw(espgui::TftInterface &tft, bool force = false,
                        std::optional<uint16_t> forceColor = std::nullopt)
    {
        if (!m_shouldRender)
            return;
    }

    virtual void moveTo(espgui::TftInterface &tft, uint16_t x, uint16_t y, uint16_t fillColor = espgui::TFT_BLACK,
                        bool skipRedraw = false);

    void moveToX(espgui::TftInterface &tft, const uint16_t x, const uint16_t fillColor = espgui::TFT_BLACK,
                 const bool skipRedraw = false)
    {
        moveTo(tft, x, m_y, fillColor, skipRedraw);
    }

    void moveToY(espgui::TftInterface &tft, const uint16_t y, const uint16_t fillColor = espgui::TFT_BLACK,
                 const bool skipRedraw = false)
    {
        moveTo(tft, m_x, y, fillColor, skipRedraw);
    }

    virtual uint16_t getHeight() = 0;

    virtual uint16_t getWidth() = 0;

    void setShouldRender(const bool shouldRender)
    {
        m_shouldRender = shouldRender;
    }

    virtual std::string name() const = 0;

    uint16_t getX() const
    {
        return m_x;
    }

    uint16_t getY() const
    {
        return m_y;
    }

    bool isVisible() const
    {
        return m_isVisible;
    }

protected:
    uint16_t m_x;
    uint16_t m_y;

    // if logic wants to display the icon, for example, if something is enabled
    bool m_isVisible { false };

    // if the icon is allowed to render
    bool m_shouldRender { true };
};

} // namespace bicycle::gui