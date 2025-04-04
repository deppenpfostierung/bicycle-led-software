#include "mainmenu.h"

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <screenmanager.h>

namespace bicycle::gui
{

namespace
{
constexpr char TEXT_TEST[] = "This is a test text";
} // namespace

MainMenu::MainMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEST>, DummyAction>>();
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