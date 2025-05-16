#include "configurecustombutton.h"

// local includes
#include "actions/pushscreenaction.h"
#include "iter.h"

constexpr const char *const TAG = "ConfigureCustomButtonMenu";

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <actions/popscreenaction.h>

// local includes
#include "guihelpers/bicyclechangevaluedisplay.h"
#include "guihelpers/changevaluedisplay_enums.h"
#include "icons/arrow.h"

namespace bicycle::gui
{

namespace
{

class SetCustomButtonId : public espgui::MenuItem
{
public:
    explicit SetCustomButtonId(ConfigureCustomButtonMenu *parent)
        : m_parent { parent }
    {
    }

    std::string text() const override
    {
        const auto &buttonId = m_parent->buttonCfg->buttonId.value();
        return buttonId == INPUT_BUTTON_NONE ? "Calibrate button to use" : std::format("Calibrated to {}", buttonId);
    }

    void triggered() override
    {

        if (const auto &buttonId = m_parent->buttonCfg->buttonId.value(); buttonId != INPUT_BUTTON_NONE)
        {
            return;
        }

        m_parent->menuMode = ConfigureCustomButtonMenu::MenuMode::CALIBRATE;
    }

private:
    ConfigureCustomButtonMenu *m_parent;
};

class ClearConfigurationAction : public espgui::MenuItem
{
public:
    explicit ClearConfigurationAction(ConfigureCustomButtonMenu *parent)
        : m_parent { parent }
    {
    }

    std::string text() const override
    {
        return "Clear configuration";
    }

    int color() const override
    {
        return espgui::TFT_RED;
    }

    void triggered() override
    {
        if (const auto res = configs.reset_config(m_parent->buttonCfg->buttonId); !res)
        {
            ESP_LOGE(TAG, "Error when resetting buttonId: %s", res.error().c_str());
            return;
        }

        if (const auto res = configs.reset_config(m_parent->buttonCfg->action); !res)
        {
            ESP_LOGE(TAG, "Error when resetting action: %s", res.error().c_str());
            return;
        }

        m_parent->menuMode = ConfigureCustomButtonMenu::MenuMode::DEFAULT;
        m_parent->error_string.reset();
    }

private:
    ConfigureCustomButtonMenu *m_parent;
};

class ErrorTextMenuItem : public espgui::MenuItem
{
public:
    explicit ErrorTextMenuItem(ConfigureCustomButtonMenu *parent)
        : m_parent { parent }
    {
    }

    std::string text() const override
    {
        if (m_parent->menuMode == ConfigureCustomButtonMenu::MenuMode::CALIBRATE)
        {
            return "Press button to calibrate";
        }

        return m_parent->error_string.has_value() ? std::format("&s{}", m_parent->error_string.value()) : "All okay";
    }

    int color() const override
    {
        if (m_parent->menuMode == ConfigureCustomButtonMenu::MenuMode::CALIBRATE)
        {
            return espgui::TFT_YELLOW;
        }

        return m_parent->error_string ? espgui::TFT_RED : espgui::TFT_GREEN;
    }

    void triggered() override
    {
    }

    bool skipScroll() const override
    {
        return true;
    }

private:
    ConfigureCustomButtonMenu *m_parent;
};

constexpr char TEXT_CHANGE_ACTION[] = "Change action";

class CustomButtonActionAccessor : public virtual espgui::AccessorInterface<ButtonAction>
{
public:
    explicit CustomButtonActionAccessor(DpadConfig *buttonCfg)
        : m_buttonCfg { buttonCfg }
    {
    }

    ButtonAction getValue() const override
    {
        return m_buttonCfg->action.value();
    }

    setter_result_t setValue(const ButtonAction value) override
    {
        return configs.write_config(m_buttonCfg->action, value);
    }

private:
    DpadConfig *m_buttonCfg;
};

using ButtonActionChangeValueDisplay = espgui::makeComponentArgs<
    BicycleChangeValueDisplay<ButtonAction>, CustomButtonActionAccessor, espgui::StaticTitle<TEXT_CHANGE_ACTION>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>, espgui::BackActionInterface<espgui::PopScreenAction>>;

} // namespace

ConfigureCustomButtonMenu::ConfigureCustomButtonMenu(DpadConfig *buttonCfg)
    : buttonCfg { buttonCfg }
{
    using namespace espgui;

    constructMenuItem<SetCustomButtonId>(this);
    constructMenuItem<makeComponentArgs<MenuItem,
                                        PushScreenActionArgs<ButtonActionChangeValueDisplay, DpadConfig *>,
                                        StaticText<TEXT_CHANGE_ACTION>,
                                        StaticMenuItemSelectedIcon<&icons::arrow>>>(buttonCfg);
    constructMenuItem<makeComponent<MenuItem, SkipScroll, EmptyText, DummyAction>>();
    constructMenuItem<ErrorTextMenuItem>(this);
    constructMenuItem<ClearConfigurationAction>(this);
}

std::string ConfigureCustomButtonMenu::title() const
{
    return menuMode == MenuMode::DEFAULT ? "Configure Button" : "Press to calibrate";
}

void ConfigureCustomButtonMenu::rawButtonPressed(const uint8_t button)
{
    if (menuMode != MenuMode::CALIBRATE)
    {
        Base::rawButtonPressed(button);
        return;
    }

    // Check if the button is a valid button ID
    bool found { false };

    forEveryButton([&](const auto *config) {
        if (button == config->value())
        {
            found = true;
            return true;
        }
        return false;
    });

    forEveryCustomButton([&](const DpadConfig *config) {
        if (found)
        {
            return true;
        }

        if (button == config->buttonId.value())
        {
            found = true;
            return true;
        }
        return false;
    });

    if (found)
    {
        error_string = std::format("Button {} is already assigned to another action", button);
        menuMode = MenuMode::DEFAULT;
        ESP_LOGW(TAG, "%s", error_string->c_str());
        return;
    }

    if (const auto res = configs.write_config(buttonCfg->buttonId, button); !res)
    {
        error_string = std::format("Error when writing buttonId: {}", res.error().c_str());
        menuMode = MenuMode::DEFAULT;
        ESP_LOGE(TAG, "%s", error_string->c_str());
        return;
    }

    error_string.reset();
    menuMode = MenuMode::DEFAULT;
}

} // namespace bicycle::gui
