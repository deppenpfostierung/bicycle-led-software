#include "settingsmenu.h"

// 3rdparty lib includes
#include <actions/pushscreenaction.h>

// local includes
#include "icons/actions.h"
#include "icons/actions_grey.h"
#include "icons/arrow.h"
#include "screens/menus/buttonsettingsmenu.h"

namespace bicycle::gui
{

namespace
{
constexpr char TEXT_DPAD_SETTINGS[] = "D-Pad Settings";
} // namespace

SettingsMenu::SettingsMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem,
                                    StaticText<TEXT_DPAD_SETTINGS>,
                                    PushScreenAction<ButtonSettingsMenu>,
                                    StaticMenuItemIcon<&icons::actions, &icons::actions_grey>,
                                    StaticMenuItemSelectedIcon<&icons::arrow>>>();
}

std::string SettingsMenu::title() const
{
    return "Settings";
}

} // namespace bicycle::gui
