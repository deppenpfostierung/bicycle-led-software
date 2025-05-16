#pragma once

// 3rdparty lib includes
#include <accessorinterface.h>
#include <changevaluedisplay.h>
#include <confirminterface.h>
#include <errorhandlerinterface.h>
#include <menudisplay.h>

// local includes
#include "enums.h"

namespace espgui
{

template <>
class ChangeValueDisplay<ButtonAction> : public espgui::MenuDisplay,
                                         public virtual espgui::AccessorInterface<ButtonAction>,
                                         public virtual espgui::ConfirmInterface,
                                         public virtual espgui::ErrorHandlerInterface
{
    using Base = espgui::MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui