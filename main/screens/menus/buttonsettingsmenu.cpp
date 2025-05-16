#include "buttonsettingsmenu.h"

// system includes
#include <format>

// 3rdparty lib includes
#include <actions/pushscreenaction.h>

// local includes
#include "icons/arrow.h"
#include "iter.h"
#include "screens/menus/configurecustombutton.h"

namespace bicycle::gui
{

namespace
{

} // namespace

ButtonSettingsMenu::ButtonSettingsMenu()
{
    using namespace espgui;

    uint8_t counter = 1;

    forEveryCustomButton([this, &counter](DpadConfig *buttonCfg) -> bool {
        auto &item = constructMenuItem<makeComponentArgs<MenuItem,
                                                         PushScreenActionArgs<ConfigureCustomButtonMenu, DpadConfig *>,
                                                         ChangeableText,
                                                         StaticMenuItemSelectedIcon<&icons::arrow>>>(buttonCfg);
        item.setTitle(std::format("Custom Button {}", counter));

        counter += 1;

        return false;
    });
}

std::string ButtonSettingsMenu::title() const
{
    return "D-Pad Settings";
}

} // namespace bicycle::gui
