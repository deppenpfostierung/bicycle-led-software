#include "mainmenu.h"

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <actions/pushscreenaction.h>

// local includes
#include "icons/arrow.h"
#include "icons/settings.h"
#include "icons/settings_grey.h"
#include "screens/menus/debugmenu.h"

namespace bicycle::gui
{

namespace
{
constexpr char TEXT_TEST[] = "Test";
constexpr char TEXT_SETTINGS[] = "Settings";
constexpr char TEXT_DEBUG[] = "Debug";
} // namespace

MainMenu::MainMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem,
                                    StaticText<TEXT_SETTINGS>,
                                    DummyAction,
                                    StaticMenuItemIcon<&icons::settings, &icons::settings_grey>,
                                    StaticMenuItemSelectedIcon<&icons::arrow>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEBUG>, PushScreenAction<DebugMenu>>>();
}

std::string MainMenu::title() const
{
    return "Main Menu";
}

} // namespace bicycle::gui