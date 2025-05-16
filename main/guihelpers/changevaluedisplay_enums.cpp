#include "changevaluedisplay_enums.h"

// 3rdparty lib includes
#include <actions/setvalueaction.h>

// local includes
#include "guihelpers/changevaluedisplayradioicon.h"
#include "icons/arrow.h"

namespace espgui
{

ChangeValueDisplay<ButtonAction>::ChangeValueDisplay()
{
    using namespace espgui;

    iterateButtonAction([this](ButtonAction action, const std::string &enumKey) {
        auto &item =
            constructMenuItem<makeComponentArgs2xN<MenuItem,
                                                   ChangeValueDisplayRadioIcon<ButtonAction, ChangeValueDisplay>,
                                                   SetValueAction<ButtonAction>,
                                                   ChangeableText,
                                                   StaticMenuItemSelectedIcon<&icons::arrow>>>(action,
                                                                                               this,
                                                                                               action,
                                                                                               *this,
                                                                                               *this,
                                                                                               *this);

        // item.setTitle(enumKey);
        std::string titleCopy = enumKey;
        std::ranges::replace(titleCopy, '_', ' ');

        item.setTitle(titleCopy);
    });
}

void ChangeValueDisplay<ButtonAction>::start()
{
    Base::start();

    const auto value = getValue();

    // get index of value in the enum
    setSelectedIndex(std::to_underlying(value));
}
} // namespace espgui