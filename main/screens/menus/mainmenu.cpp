#include "mainmenu.h"

// 3rdparty lib includes
#include <actions/pushscreenaction.h>

// local includes
#include "icons/arrow.h"
#include "icons/debug.h"
#include "icons/debug_grey.h"
#include "icons/settings.h"
#include "icons/settings_grey.h"
#include "screens/menus/debugmenu.h"
#include "screens/menus/settingsmenu.h"

namespace bicycle::gui
{

namespace
{
constexpr char TEXT_SETTINGS[] = "Settings";
constexpr char TEXT_DEBUG[] = "Debug";
} // namespace

MainMenu::MainMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem,
                                    StaticText<TEXT_SETTINGS>,
                                    PushScreenAction<SettingsMenu>,
                                    StaticMenuItemIcon<&icons::settings, &icons::settings_grey>,
                                    StaticMenuItemSelectedIcon<&icons::arrow>>>();
    constructMenuItem<makeComponent<MenuItem,
                                    StaticText<TEXT_DEBUG>,
                                    PushScreenAction<DebugMenu>,
                                    StaticMenuItemIcon<&icons::debug, &icons::debug_grey>,
                                    StaticMenuItemSelectedIcon<&icons::arrow>>>();
}

std::string MainMenu::title() const
{
    return "Main Menu";
}

} // namespace bicycle::gui