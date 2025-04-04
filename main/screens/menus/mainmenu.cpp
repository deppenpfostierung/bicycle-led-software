#include "mainmenu.h"

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <screenmanager.h>

namespace bicycle::gui
{

namespace
{
constexpr char TEST_TEXT[] = "This is a test text";
} // namespace

MainMenu::MainMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem, StaticText<TEST_TEXT>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEST_TEXT>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEST_TEXT>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEST_TEXT>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEST_TEXT>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEST_TEXT>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEST_TEXT>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEST_TEXT>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEST_TEXT>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEST_TEXT>, DummyAction>>();
}

void MainMenu::back()
{
    espgui::popScreen();
}

std::string MainMenu::title() const
{
    return "Main Menu";
}

} // namespace bicycle::gui