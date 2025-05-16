#include "debugmenu.h"

// system includes
#include <format>

// 3rdparty lib includes
#include <actions/dummyaction.h>

// local includes
#include "hardware/adc.h"

namespace bicycle::gui
{

namespace
{

class BatteryVoltageText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return std::format("Bat voltage: {:.3f}V", hardware::measure::battery_voltage.load());
    }
};

class BatteryCurrentText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return std::format("Bat current: {:.3f}A", hardware::measure::battery_current.load());
    }
};

class AuxAdc0Text : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return std::format("aux_0: {:.3f}V", hardware::measure::aux_adc_0.load());
    }
};

class AuxAdc1Text : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return std::format("aux_1: {:.3f}V", hardware::measure::aux_adc_1.load());
    }
};

} // namespace

DebugMenu::DebugMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem, BatteryVoltageText, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BatteryCurrentText, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, AuxAdc0Text, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, AuxAdc1Text, DummyAction>>();
}

std::string DebugMenu::title() const
{
    return "Debug menu";
}

} // namespace bicycle::gui
