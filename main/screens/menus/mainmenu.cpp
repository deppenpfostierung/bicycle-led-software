#include "mainmenu.h"

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <screenmanager.h>

// local includes
#include "icons/arrow.h"
#include "icons/settings.h"
#include "icons/settings_grey.h"

namespace bicycle::gui
{

namespace
{
constexpr char TEXT_TEST[] = "Test";
constexpr char TEXT_SETTINGS[] = "Settings";
} // namespace

MainMenu::MainMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETTINGS>, DummyAction, StaticMenuItemIcon<&icons::settings, &icons::settings_grey>, StaticMenuItemSelectedIcon<&icons::arrow>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
}

std::string MainMenu::title() const
{
    return "Main Menu";
}

} // namespace bicycle::gui